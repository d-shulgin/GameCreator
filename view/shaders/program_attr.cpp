#include "program_attr.h"

ProgramAttr::ProgramAttr()
    : XMLObject()
    , _modify( false )
    , _position  ( "a_position"   )
    , _normal    ( "a_normal"     )
    , _texturePos( "a_texturePos" )
    , _color     ( "a_color"      )
    , _tangent   ( "a_tangent"    )
    , _bitangent ( "a_bitangent"  )
    // ////////////////////////// |
{
    bind_fields();
}
/// @section: attribute... position /////////////////////// |
const QString& ProgramAttr::position() const             // |
{
    return( _position );
}
void ProgramAttr::setPosition( const QString& position ) // |
{
    _modify = _modify || (position != this -> position());
    _position = position;
    return;
}
/// @section: attribute... normal ///////////////////// |
const QString& ProgramAttr::normal() const           // |
{
    return( _normal );
}
void ProgramAttr::setNormal( const QString& normal ) // |
{
    _modify = _modify || (normal != this -> normal());
    _normal = normal;
    return;
}
/// @section: attribute... UVcoords of texture //////////////// |
const QString& ProgramAttr::texturePos() const               // |
{
    return( _texturePos );
}
void ProgramAttr::setTexturePos( const QString& texturePos ) // |
{
    _modify = _modify || (texturePos != this -> texturePos());
    _texturePos = texturePos;
    return;
}
/// @section: attribute... color //////////////////// |
const QString& ProgramAttr::color() const          // |
{
    return( _color );
}
void ProgramAttr::setColor( const QString& color ) // |
{
    _modify = _modify || (color != this -> color());
    _color = color;
    return;
}
/// @section: attribute... tangent ////////////////////// |
const QString& ProgramAttr::tangent() const            // |
{
    return( _tangent );
}
void ProgramAttr::setTangent( const QString& tangent ) // |
{
    _modify = _modify || (tangent != this -> tangent());
    _tangent = tangent;
    return;
}
/// @section: attribute... bitangent //////////////////////// |
const QString& ProgramAttr::bitangent() const              // |
{
    return( _bitangent );
}
void ProgramAttr::setBitangent( const QString& bitangent ) // |
{
    _modify = _modify || (bitangent != this -> bitangent());
    _bitangent = bitangent;
    return;
}
ProgramAttr::~ProgramAttr()
{
}

