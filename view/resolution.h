#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "../parser/xml_meta_data.h"

class Resolution : public XMLObject
{
public:
    static QString class_name() { return( QString("Resolution") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    explicit Resolution( unsigned int = 1, unsigned int = 1 );
    virtual ~Resolution();

public:
    Resolution( const Resolution& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _width  = cpy._width;
        _height = cpy._height;
    }
    Resolution& operator = ( const Resolution& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _width  = cpy._width;
            _height = cpy._height;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "width", &_width );
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
        return( new Resolution() );
    }
    virtual XMLObject* clone() const
    {
        Resolution* object = new Resolution();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: width
    unsigned int _width;

public:
    unsigned int width() const { return( _width ); }
    void setWidth( unsigned int w )
    {
        unsigned int origin = width();
        _width = w;
        _modify = _modify || (origin != width());
        return;
    }

private: /// @section: height
    unsigned int _height;

public:
    unsigned int height() const { return( _height ); }
    void setHeight( unsigned int h )
    {
        unsigned int origin = height();
        _height = h;
        _modify = _modify || (origin != height());
        return;
    }

public: /// @section: aspect ratio
    float aspect_ratio() const
    {
        return( static_cast<float>(width()) / static_cast<float>(height()) );
    }
    float width_ratio( const Resolution& r ) const
    {
        return( static_cast<float>(r.width()) / (static_cast<float>(r.height())*aspect_ratio()) );
    }
    float height_ratio( const Resolution& r ) const
    {
        return( static_cast<float>(r.height()) / (static_cast<float>(r.width())/aspect_ratio()) );
    }
    bool equal_ratio( const Resolution& r ) const
    {
        return( width()*r.height() == r.width()*height() );
    }

public: /// @section: operators
    bool operator == ( const Resolution& r ) const
    {
        return( width() == r.width() && height() == r.height() );
    }
    bool operator != ( const Resolution& r ) const
    {
        return( !Resolution::operator ==(r) );
    }
};

#endif // RESOLUTION_H
