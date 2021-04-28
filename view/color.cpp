#include "color.h"

Color::Color( float r, float g, float b, float a )
    : XMLObject()
    , _modify( false )
    , _red( r )
    , _green( g )
    , _blue( b )
    , _alpha( a )
{
    bind_fields();
}
Color::Color( const QColor& color )
    : XMLObject()
    , _red( static_cast<float>(color.red())/255.0f )
    , _green( static_cast<float>(color.green())/255.0f )
    , _blue( static_cast<float>(color.blue())/255.0f )
    , _alpha( static_cast<float>(color.alpha())/255.0f )
{
    bind_fields();
}
Color::~Color()
{
}
