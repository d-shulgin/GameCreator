#include "font_data.h"

FontData::FontData()
    : XMLObject()
    , _modify( false )
    , _leading( 0.0f )
    , _ascent ( 0.0f )
    , _descent( 0.0f )
{
    bind_fields();
}
void FontData::Load( QDomElement& object ) // |
{
    clear();
    XMLObject::Load( object );
    return;
}
/// @section: namae... ///////////////////////// |
const QString& FontData::name() const         // |
{
    return( _name );
}
void FontData::setName( const QString& name ) // |
{
    _modify = _modify || (name != this -> name());
    _name = name;
    return;
}
/// @section: texture size ///////////////////////////////////////////// |
const FontTextureSize& FontData::texture_size() const                 // |
{
    return( _texture_size );
}
void FontData::setTexture_size( const FontTextureSize& texture_size ) // |
{
    _modify = _modify || (texture_size != this -> texture_size());
    _texture_size = texture_size;
    return;
}
/// @section: leading... ///////// |
float FontData::leading() const // |
{
    return( _leading );
}
/// @section: ascent ///////////// |
float FontData::ascent() const  // |
{
    return( _ascent );
}
/// @section: descent //////////// |
float FontData::descent() const // |
{
    return( _descent );
}
/// @section: symbols ///////////////////////////////////////////// |
void FontData::clear()                                           // |
{
    _symbols.reset();
    return;
}
const CharData* FontData::symbol( size_t index ) const           // |
{
    if( index < symbols().count() )
    {
        const XMLObject* object = cref_symbols().itemAt( index );
        if( 0 != object
                && object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(CharData::class_name()) )
            return( static_cast<const CharData*>(object) );
    }
    return( 0 );
}
const CharData* FontData::getSymbol( const QString& code ) const // |
{
    for( size_t i = 0; i < symbols().count(); ++i )
    {
        const CharData* o_symbol = symbol(i);
        if( 0 != o_symbol && o_symbol -> code() == code )
            return( o_symbol );
    }
    return( 0 );
}
FontData::~FontData()
{
}
