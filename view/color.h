#ifndef COLOR_H
#define COLOR_H

#include <QColor>
#include "../parser/xml_meta_data.h"

class Color : public XMLObject
{
public:
    static QString class_name() { return( QString("Color") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify  ); }

public:
    explicit Color( float = 0.0f, float = 0.0f, float = 0.0f, float = 1.0f );
    explicit Color( const QColor& );
    virtual ~Color();

public:
    Color( const Color& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _red = cpy._red;
        _green = cpy._green;
        _blue = cpy._blue;
        _alpha = cpy._alpha;
    }
    Color& operator = ( const Color& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _red = cpy._red;
            _green = cpy._green;
            _blue = cpy._blue;
            _alpha = cpy._alpha;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "red",   &_red   );
        bind_field( "green", &_green );
        bind_field( "blue",  &_blue  );
        bind_field( "alpha", &_alpha );
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
        return( new Color() );
    }
    virtual XMLObject* clone() const
    {
        Color* object = new Color();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: color attribute
    float _red, _green, _blue, _alpha;

public:
    float red() const { return( _red ); }
    float green() const { return( _green ); }
    float blue() const { return( _blue ); }
    float alpha() const { return( _alpha ); }
};

#endif // COLOR_H
