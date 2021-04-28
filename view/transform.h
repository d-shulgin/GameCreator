#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include "../parser/xml_meta_data.h"
#include "vector3.h"
#include "angle.h"

class Position  : public Vector3
{
public:
    static QString class_name() { return( QString("Position") ); }
    virtual QString xml_class_name() const
    {
        if( Vector3::xml_class_name().isEmpty() )
            return( class_name() );
        return( Vector3::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( _modify || Vector3::isModify() ); }

public:
    Position()
        : Vector3()
        , _modify( false )
    {
        bind_fields();
    }
    explicit Position( float x, float y, float z )
        : Vector3( x, y, z )
        , _modify( false )
    {
        bind_fields();
    }
    explicit Position( const QVector3D& v )
        : Vector3( v )
        , _modify( false )
    {
        bind_fields();
    }
    virtual ~Position(){}

public:
    Position( const Position& cpy )
        : Vector3( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
    }
    Position& operator = ( const Position& cpy )
    {
        if( this != &cpy )
        {
            Vector3::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Vector3::bind_fields();
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
        return( new Position() );
    }
    virtual XMLObject* clone() const
    {
        Position* object = new Position();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

public: /// @section: operators
    bool operator == ( const Position& t ) const
    {
        return( Vector3::operator ==(Vector3(t.x(), t.y(), t.z())) );
    }
    bool operator != ( const Position& t ) const
    {
        return( !Position::operator ==(t) );
    }

};
class Rotate    : public XMLObject
{
public:
    static QString class_name() { return( QString("Rotate") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify  ); }

public:
    Rotate()
        : XMLObject()
        , _modify( false )
        , _x( 0.0f )
        , _y( 0.0f )
        , _z( 0.0f )
        , _w( 1.0f )
    {
        bind_fields();
    }
    explicit Rotate( const Angle& angle
                     , const Vector3& axis )
        : XMLObject()
        , _modify( false )
    {
        QQuaternion q = QQuaternion::fromAxisAndAngle( axis.vec(), angle.as_degrees() );
        _x = q.toVector4D().x();
        _y = q.toVector4D().y();
        _z = q.toVector4D().z();
        _w = q.toVector4D().w();
        bind_fields();
    }
    explicit Rotate( const Angle& angle
                     , const QVector3D& axis )
        : XMLObject()
        , _modify( false )
    {
        QQuaternion q = QQuaternion::fromAxisAndAngle( axis, angle.as_degrees() );
        _x = q.toVector4D().x();
        _y = q.toVector4D().y();
        _z = q.toVector4D().z();
        _w = q.toVector4D().w();
        bind_fields();
    }
    explicit Rotate( const QQuaternion& q )
        : XMLObject()
        , _modify( false )
        , _x( q.toVector4D().x() )
        , _y( q.toVector4D().y() )
        , _z( q.toVector4D().z() )
        , _w( q.toVector4D().w() )
    {
    }
    virtual ~Rotate()
    {}

public:
    Rotate( const Rotate& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _x = cpy._x;
        _y = cpy._y;
        _z = cpy._z;
        _w = cpy._w;
    }
    Rotate& operator = ( const Rotate& cpy )
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
            _w = cpy._w;
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
        bind_field( "w", &_w );
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
        return( new Rotate() );
    }
    virtual XMLObject* clone() const
    {
        Rotate* object = new Rotate();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: quaternion
    float _x, _y, _z, _w;

public:
    Vector3 axis() const
    {
        Vector3 result;
        toAngleAxis( 0, &result );
        return( result );
    }
    Angle angle() const
    {
        float result;
        toAngleAxis( &result, 0 );
        return( Angle(result, Angle::radians_unit) );
    }
    void toAngleAxis( float* angle, Vector3* axis ) const
    {
        float v = (float)sqrt( _x*_x + _y*_y + _z*_z );
        if( v > 0.0000001 )
        {
            float div = 1.0f/v;
            if( 0 != axis )
                (*axis) = Vector3( _x*div, _y*div, _z*div );
            if( 0 != angle )
            {
                if( _w < 0 )
                    (*angle) = 2.0f * (float)atan2(-v, -_w); // -Pi; 0
                else
                    (*angle) = 2.0f * (float)atan2(v, _w); // 0; Pi
            }
        }
        else
        {
            if( 0 != angle )
                (*angle) = 0.0f;
            if( 0 != axis )
                (*axis)= Vector3();
        }
        return;
    }
    QQuaternion quat() const
    {
        return( QQuaternion(_w, _x, _y, _z) );
    }

public: /// @section: operators
    bool operator == ( const Rotate& r ) const
    {
        return( _x == r._x && _y == r._y && _z == r._z && _w == r._w );
    }
    bool operator != ( const Rotate& r ) const
    {
        return( !Rotate::operator ==(r) );
    }
};
class Scale     : public Vector3
{
public:
    static QString class_name() { return( QString("Scale") ); }
    virtual QString xml_class_name() const
    {
        if( Vector3::xml_class_name().isEmpty() )
            return( class_name() );
        return( Vector3::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( _modify || Vector3::isModify() ); }
public:
    Scale()
        : Vector3( 1.0f, 1.0f, 1.0f )
    {
        bind_fields();
    }
    explicit Scale( float sx, float sy, float sz )
        : Vector3( sx, sy, sz )
    {
        bind_fields();
    }
    explicit Scale( const QVector3D& v )
        : Vector3( v )
    {
        bind_fields();
    }
    explicit Scale( float scale, const QVector3D& normal )
        : Vector3( normal*scale )
    {
        bind_fields();
    }
    virtual ~Scale(){}

public:
    Scale( const Scale& cpy )
        : Vector3( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
    }
    Scale& operator = ( const Scale& cpy )
    {
        if( this != &cpy )
        {
            Vector3::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Vector3::bind_fields();
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
        return( new Scale() );
    }
    virtual XMLObject* clone() const
    {
        Scale* object = new Scale();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

public: /// @section: operators
    bool operator == ( const Scale& s ) const
    {
        return( Vector3::operator ==(Vector3(s.x(), s.y(), s.z())) );
    }
    bool operator != ( const Scale& s ) const
    {
        return( !Scale::operator ==(s) );
    }
};
class Transform : public XMLObject
{
public:
    static QString class_name() { return( QString("Transform") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify
                                            || scale().isModify() ); }

public:
    Transform();
    virtual ~Transform();

public:
    Transform( const Transform& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _position = cpy._position;
        _rotate = cpy._rotate;
        _scale = cpy._scale;
    }
    Transform& operator = ( const Transform& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _position = cpy._position;
            _rotate = cpy._rotate;
            _scale = cpy._scale;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "transalte", &_position );
        bind_field( "rotate", &_rotate );
        bind_field( "scale", &_scale );
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
        return( new Transform() );
    }
    virtual XMLObject* clone() const
    {
        Transform* object = new Transform();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: position
    Position _position;

public:
    const Position& position() const;
    void setPosition( const Position& position );

private: /// @section: rotate
    Rotate _rotate;

public:
    const Rotate& rotate() const;
    void setRotate( const Rotate& rotate );

private: /// @section: scale
    Scale _scale;

public:
    const Scale& scale() const;
    void setScale(const Scale &scale);

public:
    QMatrix4x4 matrix() const
    {
        QMatrix4x4 mtx;
        mtx.setToIdentity();
        mtx.translate( position().vec() );
        mtx.rotate( rotate().quat() );
        mtx.scale( scale().vec() );
        return( mtx );
    }

public: /// @section: operators
    bool operator == ( const Transform& t ) const
    {
        return( position() == t.position()
                && rotate() == t.rotate()
                && scale() == t.scale() );
    }
    bool operator != ( const Transform& t ) const
    {
        return( !Transform::operator ==(t) );
    }
};

#endif // TRANSFORM_H
