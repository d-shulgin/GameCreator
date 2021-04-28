#ifndef FONT_TEXTURE_SIZE_H
#define FONT_TEXTURE_SIZE_H

#include "parser/xml_meta_data.h"

class FontTextureSize : public XMLObject
{
public:
    static QString class_name() { return( QString("FontTextureSize") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify  ); }

public:
    explicit FontTextureSize( int = 0, int = 0 );
    virtual ~FontTextureSize();

public:
    FontTextureSize( const FontTextureSize& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify  = cpy._modify;
        _width = cpy._width;
        _height = cpy._height;
    }
    FontTextureSize& operator = ( const FontTextureSize& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify  = cpy._modify;
            _width = cpy._width;
            _height = cpy._height;
        }
        return( *this );
    }
    bool operator == ( const FontTextureSize& size ) const
    {
        return( width() == size.width() && height() == size.height() );
    }
    bool operator != ( const FontTextureSize& size ) const
    {
        return( width() != size.width() || height() != size.height() );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "width",  &_width  );
        bind_field( "height", &_height );
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
        return( new FontTextureSize() );
    }
    virtual XMLObject* clone() const
    {
        FontTextureSize* object = new FontTextureSize();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: width
    int _width;

public:
    int width() const;

private: /// @section: height
    int _height;

public:
    int height() const;
};

#endif // FONT_TEXTURE_SIZE_H
