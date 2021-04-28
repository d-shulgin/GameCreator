#ifndef FONT_LIB_H
#define FONT_LIB_H

#include "../../parser/xml_meta_data.h"
#include "font.h"

class FontLib : public XMLObject
{
public:
    static QString class_name() { return( QString("FontLib") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify || isAnyElementModify() ); }

public:
    FontLib();
    virtual ~FontLib();

public:
    FontLib( const FontLib& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
    }
    FontLib& operator = ( const FontLib& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
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
        return( new FontLib() );
    }
    virtual XMLObject* clone() const
    {
        FontLib* object = new FontLib();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected:
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < fonts().count() && !modify; ++i )
            modify = cref_fonts().itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: fonts...
    XMLCollection _fonts;

protected:
    XMLCollection& ref_fonts() { return( _fonts ); }
    const XMLCollection& cref_fonts() const { return( _fonts ); }

public:
    void load( const QString&, const QString& );
    void upload( QGLFunctions* );
    void release( QGLFunctions* );
    const XMLCollectionU& fonts() const { return( _fonts ); }
    Font* font( size_t );
    const Font* font_const( size_t ) const;
    const Font* getFont( const QString& ) const;
};

#endif // FONT_LIB_H
