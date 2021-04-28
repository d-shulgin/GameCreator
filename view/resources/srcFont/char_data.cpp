#include "char_data.h"

CharData::CharData()
    : XMLObject()
    , _modify( false )
    , _width( 0.0f )
    , _height( 0.0f )
    , _bearingX( 0.0f )
    , _bearingY( 0.0f )
    , _advance( 0.0f )
    // //////////// |
{
    bind_fields();
}
CharData::CharData(const QString& code
                    , const QFontMetricsF& metric
                    , const CharTextureArea& area )
    : XMLObject()
    , _modify( false )
    , _code( code )
    , _width( 0.0f )
    , _height( 0.0f )
    , _bearingX( 0.0f )
    , _bearingY( 0.0f )
    , _advance( 0.0f )
    , _texture_area( area )
    // //////////// |
{
    QRectF rect = metric.boundingRect(code.at(0));
    _width    = rect.width();
    _height   = rect.height();
    _bearingY = rect.top();
    _bearingX = metric.leftBearing(code.at(0));
    _advance  = metric.width( code.at(0) );
    bind_fields();
}
/// @section: utf8 code //////////////////////// |
const QString& CharData::code() const         // |
{
    return( _code );
}
void CharData::setCode( const QString& code ) // |
{
    _modify = _modify || (code != this -> code());
    _code = code;
    return;
}
/// @section: width /////////////// |
float CharData::width() const    // |
{
    return( _width );
}
/// @section: height ////////////// |
float CharData::height() const   // |
{
    return( _height );
}
/// @section: bearing-X /////////// |
float CharData::bearingX() const // |
{
    return( _bearingX );
}
/// @section: bearing-Y /////////// |
float CharData::bearingY() const // |
{
    return( _bearingY );
}
/// @section: advance ///////////// |
float CharData::advance() const  // |
{
    return( _advance );
}
/// @section: texture area //////////////////////// |
const CharTextureArea& CharData::texture() const // |
{
    return( _texture_area );
}
CharData::~CharData()
{
}


CharTextureArea::CharTextureArea( float left
                                  , float right
                                  , float top
                                  , float bottom )
    : XMLObject()
    , _modify( false )
    , _left( left )
    , _right( right )
    , _top( top )
    , _bottom( bottom )
{
    bind_fields();
}
CharTextureArea::CharTextureArea( const QRectF& rect )
    : XMLObject()
    , _modify( false )
    , _left( rect.left() )
    , _right( rect.right() )
    , _top( rect.top() )
    , _bottom( rect.bottom() )
{
    bind_fields();
}
/// @section: left... //////////////////////// |
float CharTextureArea::left() const         // |
{
    return _left;
}
void CharTextureArea::setLeft( float left ) // |
{
    _modify = _modify || (left != this -> left());
    _left = left;
    return;
}
/// @section: right... ///////////////////////// |
float CharTextureArea::right() const          // |
{
    return _right;
}
void CharTextureArea::setRight( float right ) // |
{
    _modify = _modify || (right != this -> right());
    _right = right;
    return;
}
/// @section: top... /////////////////////// |
float CharTextureArea::top() const        // |
{
    return _top;
}
void CharTextureArea::setTop( float top ) // |
{
    _modify = _modify || (top != this -> top());
    _top = top;
    return;
}
/// @section: bottom... ////////////////////////// |
float CharTextureArea::bottom() const           // |
{
    return _bottom;
}
void CharTextureArea::setBottom( float bottom ) // |
{
    _modify = _modify || (bottom != this -> bottom());
    _bottom = bottom;
    return;
}
CharTextureArea::~CharTextureArea()
{
}
