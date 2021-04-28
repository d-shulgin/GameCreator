#include "picture.h"
#include "texture.h"

TextureCoord::TextureCoord( float x, float y
                            , float w, float h
                            , eType type )
    : XMLObject()
    , _modify( false )
    , _left( x )
    , _right( x + w )
    , _top( 0.0f )
    , _bottom( 0.0f )
{
    switch( type )
    {
    case unit_top_up:
        _top = y;
        _bottom = y + h;
        break;
    case unit_top_down:
        _top = y + h;
        _bottom = y;
        break;
    default:
        break;
    }
    bind_fields();
}
TextureCoord& TextureCoord::top_up()
{
    if( top() > bottom() )
    {
        float swap = _top;
        _top = _bottom;
        _bottom = swap;
    }
    return( *this );
}
TextureCoord& TextureCoord::top_down()
{
    if( top() < bottom() )
    {
        float swap = _top;
        _top = _bottom;
        _bottom = swap;
    }
    return( *this );
}
TextureCoord::~TextureCoord()
{
}


Picture::Picture( const QString& namae
                  , Texture* parent )
    : XMLObject()
    , _modify( false )
    , _parent( parent )
    , _name( namae )
    , _left( 0 )
    , _top( 0 )
    , _width( 0 )
    , _height( 0 )
{
    bind_fields();
}
Picture::Picture( const QString& namae
                  , int left
                  , int top
                  , int width
                  , int height
                  , Texture* parent )
    : XMLObject()
    , _modify( false )
    , _parent( parent )
    , _name( namae )
    , _left( left )
    , _top( top )
    , _width( width )
    , _height( height )
{
    bind_fields();
}
TextureCoord Picture::coord() const
{
    if( 0 == _parent )
        return( TextureCoord() );
    float l = static_cast<float>(left())/static_cast<float>(_parent->width());
    float t = static_cast<float>(top())/static_cast<float>(_parent->height());
    float w = static_cast<float>(width())/static_cast<float>(_parent->width());
    float h = static_cast<float>(height())/static_cast<float>(_parent->height());
    return( TextureCoord(l, t, w, h, TextureCoord::unit_top_up) );
}
GLuint Picture::texture() const
{
    if( 0 == _parent )
        return( 0 );
    return( _parent -> id() );
}
Picture::~Picture()
{
}

