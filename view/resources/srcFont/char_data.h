#ifndef CHAR_DATA_H
#define CHAR_DATA_H

#include <QFontMetricsF>
#include "parser/xml_meta_data.h"

class CharTextureArea : public XMLObject
{
public:
    static QString class_name() { return( QString("CharTextureArea") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify  ); }

public:
    explicit CharTextureArea( float = 0.0f, float = 0.0f, float = 0.0f, float = 0.0f );
    explicit CharTextureArea( const QRectF& );
    virtual ~CharTextureArea();

public:
    CharTextureArea( const CharTextureArea& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _left = cpy._left;
        _right = cpy._right;
        _top = cpy._top;
        _bottom = cpy._bottom;
    }
    CharTextureArea& operator = ( const CharTextureArea& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _left = cpy._left;
            _right = cpy._right;
            _top = cpy._top;
            _bottom = cpy._bottom;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "left",     &_left   );
        bind_field( "right",    &_right  );
        bind_field( "top",      &_top    );
        bind_field( "bottom",   &_bottom );
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
        return( new CharTextureArea() );
    }
    virtual XMLObject* clone() const
    {
        CharTextureArea* object = new CharTextureArea();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: left...
    float _left;

public:
    float left() const;
    void setLeft( float left );

private: /// @section: right...
    float _right;

public:
    float right() const;
    void setRight( float right );

private: /// @section: top...
    float _top;

public:
    float top() const;
    void setTop( float top );

private: /// @section: bottom...
    float _bottom;

public:
    float bottom() const;
    void setBottom( float bottom );
};
class CharData : public XMLObject
{
public:
    static QString class_name() { return( QString("CharData") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify  ); }

public:
    CharData();
    explicit CharData( const QString&, const QFontMetricsF&, const CharTextureArea& );
    virtual ~CharData();

public:
    CharData( const CharData& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify   = cpy._modify;
        _code     = cpy._code;
        _width    = cpy._width;
        _height   = cpy._height;
        _bearingX = cpy._bearingX;
        _bearingY = cpy._bearingY;
        _advance  = cpy._advance;
        _texture_area = cpy._texture_area;
    }
    CharData& operator = ( const CharData& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify   = cpy._modify;
            _code     = cpy._code;
            _width    = cpy._width;
            _height   = cpy._height;
            _bearingX = cpy._bearingX;
            _bearingY = cpy._bearingY;
            _advance  = cpy._advance;
            _texture_area = cpy._texture_area;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "code",     &_code );
        bind_field( "width",    &_width  );
        bind_field( "height",   &_height );
        bind_field( "bearingX", &_bearingX );
        bind_field( "bearingY", &_bearingY );
        bind_field( "advance",  &_advance  );
        bind_field( "texture_area",  &_texture_area );
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
        return( new CharData() );
    }
    virtual XMLObject* clone() const
    {
        CharData* object = new CharData();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: utf8 code
    QString _code;

public:
    const QString& code() const;
    void setCode( const QString& code );

private: /// @section: width
    float _width;

public:
    float width() const;

private: /// @section: height
    float _height;

public:
    float height() const;

private: /// @section: bearing-X
    float _bearingX;

public:
    float bearingX() const;

private: /// @section: bearing-Y
    float _bearingY;

public:
    float bearingY() const;

private: /// @section: advance
    float _advance;

public:
    float advance() const;

private: /// @section: texture area
    CharTextureArea _texture_area;

public:
    const CharTextureArea& texture() const;
};

#endif // CHAR_DATA_H
