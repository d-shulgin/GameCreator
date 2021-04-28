#ifndef PICTURE_H
#define PICTURE_H

#include <GL/gl.h>
#include "../../parser/xml_meta_data.h"

class Texture;
class TextureCoord : public XMLObject
{
public:
    static QString class_name() { return( QString("TextureCoord") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    enum eType { unit_top_up
                 , unit_top_down };

    explicit TextureCoord( float x = 0.0f, float y = 0.0f
            , float w = 1.0f, float h = 1.0f, eType = unit_top_up );
    virtual ~TextureCoord();

public:
    TextureCoord( const TextureCoord& cpy )
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
    TextureCoord& operator = ( const TextureCoord& cpy )
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
        bind_field( "left",   &_left );
        bind_field( "top",    &_top );
        bind_field( "right",  &_right );
        bind_field( "bottom", &_bottom);
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
        return( new TextureCoord() );
    }
    virtual XMLObject* clone() const
    {
        TextureCoord* object = new TextureCoord();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: coords;
    float _left;
    float _right;
    float _top;
    float _bottom;

public:
    float left() const { return( _left ); }
    float right() const { return( _right ); }
    float top() const { return( _top ); }
    float bottom() const { return( _bottom ); }

    TextureCoord& top_up();
    TextureCoord& top_down();
};
class Picture      : public XMLObject
{
public:
    static QString class_name() { return( QString("Picture") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    explicit Picture( const QString& namae = QString(), Texture* parent = 0 );
    explicit Picture( const QString&, int, int, int, int, Texture* parent = 0 );
    virtual ~Picture();

public:
    Picture( const Picture& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _parent = cpy._parent;
        _name = cpy._name;
        _left = cpy._left;
        _top = cpy._top;
        _width = cpy._width;
        _height = cpy._height;
    }
    Picture& operator = ( const Picture& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _parent = cpy._parent;
            _name = cpy._name;
            _left = cpy._left;
            _top = cpy._top;
            _width = cpy._width;
            _height = cpy._height;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "name",   &_name );
        bind_field( "left",   &_left );
        bind_field( "top",    &_top );
        bind_field( "width",  &_width );
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
        return( new Picture() );
    }
    virtual XMLObject* clone() const
    {
        Picture* object = new Picture();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;
    Texture* _parent;

public:
    void setParent( Texture* p ) { _parent = p; }

private: /// @section: name
    QString _name;

public:
    const QString& name() const
    {
        return( _name );
    }
    void setName( const QString& name )
    {
        QString origin = this -> name();
        _name = name;
        _modify = _modify || (origin != this -> name());
        return;
    }

private: /// @section: left/top
    int _left;
    int _top;

public:
    int left() const
    {
        return( _left );
    }
    void setLeft( int left )
    {
        int origin = this -> left();
        _left = left;
        _modify = _modify || (origin != this -> left());
        return;
    }

    int top() const
    {
        return( _top );
    }
    void setTop( int top )
    {
        int origin = this -> top();
        _top = top;
        _modify = _modify || (origin != this -> top());
        return;
    }

private: /// @section: width/height
    int _width;
    int _height;

public:
    int width() const
    {
        return( _width );
    }
    void setWidth( int width )
    {
        int origin = this -> width();
        _width = width;
        _modify = _modify || (origin != this -> width());
        return;
    }

    int height() const
    {
        return( _height );
    }
    void setHeight( int height )
    {
        int origin = this -> height();
        _height = height;
        _modify = _modify || (origin != this -> height());
        return;
    }

public: /// @section: texture coord
    TextureCoord coord() const;
    GLuint texture() const;
};

#endif // PICTURE_H
