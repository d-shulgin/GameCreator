#ifndef ANGLE_H
#define ANGLE_H

#include <math.h>
#include "../parser/xml_meta_data.h"

class Angle : public XMLObject
{
public:
    static QString class_name() { return( QString("Angle") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify  ); }

public:
    enum eType { radians_unit
                 , degrees_unit };

    Angle();
    explicit Angle( float, eType = radians_unit );
    virtual ~Angle();

public:
    Angle( const Angle& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify  = cpy._modify;
        _radians = cpy._radians;
    }
    Angle& operator = ( const Angle& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _radians = cpy._radians;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "radians", &_radians );
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
        return( new Angle() );
    }
    virtual XMLObject* clone() const
    {
        Angle* object = new Angle();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: angle
    float _radians;

public:
    float as_radians() const { return( _radians ); }
    float as_degrees() const { return( 180.0f*_radians/M_PI ); }
    void setAsRadians( float v )
    {
        float origin = as_radians();
        _radians = v;
        _modify = _modify || (origin != as_radians());
        return;
    }
    void setAsDegrees( float v )
    {
        float origin = as_radians();
        _radians = v*M_PI/180.0f;
        _modify = _modify || (origin != as_radians());
        return;
    }

public: /// @section: operators
    bool operator == ( const Angle& a ) const
    {
        return( as_radians() == a.as_radians() );
    }
    bool operator != ( const Angle& a ) const
    {
        return( as_radians() != a.as_radians() );
    }
};

#endif // ANGLE_H
