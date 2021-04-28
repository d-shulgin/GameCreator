#include "font_texture_size.h"

FontTextureSize::FontTextureSize( int w, int h )
    : XMLObject()
    , _modify( false )
    , _width( w )
    , _height( h )
{
    bind_fields();
}
int FontTextureSize::width() const
{
    return( _width );
}
int FontTextureSize::height() const
{
    return _height;
}
FontTextureSize::~FontTextureSize()
{
}
