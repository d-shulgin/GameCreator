#include "font_lib.h"

FontLib::FontLib()
    : XMLObject()
    , _modify( false )
{
    bind_fields();
}
/// @section: fonts...
void FontLib::load( const QString& namae
                    , const QString& path )
{
    const Font* font = getFont( namae );
    if( 0 == font )
    {
        _fonts << static_cast< XMLObject* >( new Font(namae, path) );
        _modify = true;
    }
    return;
}
void FontLib::upload( QGLFunctions* functions )
{
    if( 0 != functions )
    {
        for( size_t i = 0; i < fonts().count(); ++i )
        {
            Font* o_font = font(i);
            if( 0 != o_font )
                o_font -> load( functions );
        }
    }
    return;
}
void FontLib::release( QGLFunctions* functions )
{
    if( 0 != functions )
    {
        for( size_t i = 0; i < fonts().count(); ++i )
        {
            Font* o_font = font(i);
            if( 0 != o_font )
                o_font -> release( functions );
        }
        ref_fonts().reset();
    }
    return;
}
Font* FontLib::font( size_t index )            // |
{
    if( index < fonts().count() )
    {
        XMLObject* object = ref_fonts()[index];
        if( 0 != object
                && object->xml_class_name()
                .split(".", QString::SkipEmptyParts)
                .contains(Font::class_name()) )
            return( static_cast<Font*>(object) );
    }
    return( 0 );
}
const Font* FontLib::font_const( size_t index ) const // |
{
    if( index < fonts().count() )
    {
        const XMLObject* object = cref_fonts().itemAt( index );
        if( 0 != object
                && object->xml_class_name()
                .split(".", QString::SkipEmptyParts)
                .contains(Font::class_name()) )
            return( static_cast<const Font*>(object) );
    }
    return( 0 );
}
const Font* FontLib::getFont( const QString& namae ) const // |
{
    for( size_t i = 0; i < fonts().count(); ++i )
    {
        const Font* o_font = font_const(i);
        if( 0 != o_font && o_font -> name() == namae )
            return( o_font );
    }
    return( 0 );
}
FontLib::~FontLib()
{
}

