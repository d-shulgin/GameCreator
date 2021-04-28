#ifndef FONT_DATA_H
#define FONT_DATA_H

#include "../../../parser/xml_meta_data.h"
#include "font_texture_size.h"
#include "char_data.h"

class FontData : public XMLObject
{
public:
    static QString class_name() { return( QString("FontData") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify  ); }

public:
    FontData();
    virtual ~FontData();

    virtual void Load( QDomElement& );

public:
    FontData( const FontData& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify       = cpy._modify;
        _name         = cpy._name;
        _texture_size = cpy._texture_size;
        _leading      = cpy._leading;
        _ascent       = cpy._ascent;
        _descent      = cpy._descent;
        _symbols      = cpy._symbols;
    }
    FontData& operator = ( const FontData& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify       = cpy._modify;
            _name         = cpy._name;
            _texture_size = cpy._texture_size;
            _leading      = cpy._leading;
            _ascent       = cpy._ascent;
            _descent      = cpy._descent;
            _symbols      = cpy._symbols;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "name",         &_name );
        bind_field( "texture_size", &_texture_size );
        bind_field( "leading",      &_leading );
        bind_field( "ascent",       &_ascent );
        bind_field( "descent",      &_descent );
        bind_field( "symbols",      &_symbols );
        return;
    }

protected:
    virtual void event_Saved()
    {
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        if( success )
        {
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new FontData() );
    }
    virtual XMLObject* clone() const
    {
        FontData* object = new FontData();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: namae...
    QString _name;

public:
    const QString& name() const;
    void setName(const QString& name);

private: /// @section: texture size
    FontTextureSize _texture_size;

public:
    const FontTextureSize& texture_size() const;
    void setTexture_size(const FontTextureSize& texture_size);

private: /// @section: leading...
    float _leading;

public:
    float leading() const;

private: /// @section: ascent
    float _ascent;

public:
    float ascent() const;

private: /// @section: descent
    float _descent;

public:
    float descent() const;

public: /// @section: height
    float height() const { return( ascent() + descent() ); }

private: /// @section: symbols
    XMLCollection _symbols;

protected:
    XMLCollection& ref_symbols() { return( _symbols ); }
    const XMLCollection& cref_symbols() const { return( _symbols ); }

public:
    void clear();
    const XMLCollectionU& symbols() const { return( _symbols ); }
    const CharData* symbol( size_t ) const;
    const CharData* getSymbol( const QString& ) const;
};

#endif // FONT_DATA_H
