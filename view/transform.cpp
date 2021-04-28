#include "transform.h"

Transform::Transform()
    : XMLObject()
    , _modify( false )
    // /////////////////////////////////////////////// |
{
    bind_fields();
}
const Position& Transform::position() const         // |
{
    return( _position );
}
void Transform::setPosition( const Position& p )    // |
{
    Position origin = position();
    _position = p;
    _modify = _modify || (origin != position());
    return;
}
const Rotate& Transform::rotate() const             // |
{
    return _rotate;
}
void Transform::setRotate( const Rotate& r )        // |
{
    Rotate origin = rotate();
    _rotate = r;
    _modify = _modify || (origin != rotate());
    return;
}
const Scale& Transform::scale() const               // |
{
    return _scale;
}
void Transform::setScale( const Scale& s )          // |
{
    Scale origin = scale();
    _scale = s;
    _modify = _modify || (origin != scale());
    return;
}
Transform::~Transform()
{
}
