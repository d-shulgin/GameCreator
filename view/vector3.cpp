#include "vector3.h"

Vector3::Vector3( float x
                  , float y
                  , float z )
    : XMLObject()
    , _modify( false )
    , _x( x )
    , _y( y )
    , _z( z )
{
    bind_fields();
}
Vector3::Vector3( const QVector3D &v )
    : XMLObject()
    , _modify( false )
    , _x( v.x() )
    , _y( v.y() )
    , _z( v.z() )
    // /////////////////////////// |
{
    bind_fields();
}
float Vector3::x() const        // |
{
    return( _x );
}
void Vector3::setX( float x )   // |
{
    float origin = this -> x();
    _x = x;
    _modify = _modify || (origin != this -> x());
    return;
}
float Vector3::y() const        // |
{
    return( _y );
}
void Vector3::setY( float y )   // |
{
    float origin = this -> y();
    _y = y;
    _modify = _modify || (origin != this -> y());
    return;
}
float Vector3::z() const        // |
{
    return( _z );
}
void Vector3::setZ( float z )   // |
{
    float origin = this -> z();
    _z = z;
    _modify = _modify || (origin != this -> z());
    return;
}
Vector3::~Vector3()
{
}
