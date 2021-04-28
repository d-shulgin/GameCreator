#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>
#include <QVector3D>
#include <QVector4D>
#include "../parser/xml_meta_data.h"

class Vector3 : public XMLObject
{
public:
    static QString class_name() { return( QString("Vector3") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify  ); }

public:
    explicit Vector3( float = 0.0f, float = 0.0f, float = 0.0f );
    explicit Vector3( const QVector3D& );
    virtual ~Vector3();

public:
    Vector3( const Vector3& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _x = cpy._x;
        _y = cpy._y;
        _z = cpy._z;
    }
    Vector3& operator = ( const Vector3& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _x = cpy._x;
            _y = cpy._y;
            _z = cpy._z;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "x", &_x );
        bind_field( "y", &_y );
        bind_field( "z", &_z );
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
        return( new Vector3() );
    }
    virtual XMLObject* clone() const
    {
        Vector3* object = new Vector3();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: coords
    float _x, _y, _z;

public:
    float x() const;
    void setX(float x);
    float y() const;
    void setY(float y);
    float z() const;
    void setZ(float z);
    QVector3D vec() const { return( QVector3D(x(), y(), z()) ); }
    QVector4D vec4() const { return( QVector4D(x(), y(), z(), 1.0f) ); }
    void setVec( const QVector3D& v )
    {
        QVector3D origin = vec();
        _x = v.x();
        _y = v.y();
        _z = v.z();
        _modify = _modify || (origin != vec());
        return;
    }

public:
    float lenght() const
    {
        return( sqrtf(x()*x() + y()*y() + z()*z()) );
    }
    void normalize()
    {
        float len = lenght();
        _x = _x/len;
        _y = _y/len;
        _z = _z/len;
        return;
    }
    Vector3 normalized() const
    {
        float len = lenght();
        return( Vector3(x()/len, y()/len, z()/len) );
    }
    static Vector3 cross( const Vector3& v1, const Vector3& v2 )
    {
        float x = v1.y()*v2.z() - v1.z()*v2.y();
        float y = v1.z()*v2.x() - v1.x()*v2.z();
        float z = v1.x()*v2.y() - v1.y()*v2.x();
        return( Vector3(x, y, z) );
    }

public: /// @section: operators
    bool operator == ( const Vector3& v ) const
    {
        return( x() == v.x() && y() == v.y() && z() == v.z() );
    }
    bool operator != ( const Vector3& v ) const
    {
        return( !Vector3::operator ==( v ) );
    }
    Vector3& operator += ( const Vector3& v )
    {
        _x += v.x();
        _y += v.y();
        _z += v.z();
        return( *this );
    }
    Vector3 operator + ( const Vector3& v ) const
    {
        return( Vector3(x()+v.x(), y()+v.y(), z()+v.z()) );
    }
    Vector3 operator - ( const Vector3& v ) const
    {
        return( Vector3(x() - v.x(), y() - v.y(), z() - v.z()) );
    }
    Vector3 operator * ( float v ) const
    {
        return( Vector3(x()*v, y()*v, z()*v) );
    }
};

#endif // VECTOR3_H
