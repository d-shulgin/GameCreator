#include "texture.h"
#include <QImage>

//#include "../../render.h"

Texture::Texture( /*Render* render, */const QString& path
                  , bool mirrowed )
    : XMLObject()
    , _modify( false )
    , _id( 0 )
    , _filepath( path )
    , _mirrowed( mirrowed )
//    , _render( render )
    , _width( 0 )
    , _height( 0 )
    // /////////////////////////////////////////////////////// |
{
    loadTexture( /*_render */);
    bind_fields();
}
Texture::Texture(/*Render* render, */const QString& path
                 , Texture::Filter::id min_filter
                 , Texture::Filter::id mag_filter
                 , Texture::WrapMode::id wrap_s
                 , Texture::WrapMode::id wrap_t
                 , bool mirrowed )
    : XMLObject()
    , _modify( false )
    , _id( 0 )
    , _filepath( path )
    , _mirrowed( mirrowed )
//    , _render( render )
    , _width( 0 )
    , _height( 0 )
    , _wrap_s( EnumAs<WrapMode>(WrapMode(wrap_s)) )
    , _wrap_t( EnumAs<WrapMode>(WrapMode(wrap_t)) )
    , _min_filter( EnumAs<Filter>(Filter(min_filter)) )
    , _mag_filter( EnumAs<Filter>(Filter(mag_filter)) )
{
    loadTexture( /*_render */);
    bind_fields();
}
void Texture::loadTexture(/*Render* render */)
{
//    _render = render;
    if( id() == 0 && !filepath().isEmpty() /*&& 0 != render*/ )
    {
        QImage image = QImage(filepath()).convertToFormat(QImage::Format_RGBA8888);
        if( mirrowed() )
            image = image.mirrored();
        _width = image.width();
        _height = image.height();
        if( !image.isNull() )
        {
            glEnable( GL_TEXTURE_2D );
            glGenTextures(1, &_id);
//            _id = render -> bindTexture( image, GL_TEXTURE_2D, GL_RGBA );
            if( id() != 0 )
            {
                glBindTexture( GL_TEXTURE_2D, _id );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter().value()) );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter().value()) );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapS().value()) );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapT().value()) );
                glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA
                              , static_cast<GLsizei>(width())
                              , static_cast<GLsizei>(height())
                              , 0, GL_RGBA/*GL_BGRA*/, GL_UNSIGNED_BYTE, image.bits() );
                glBindTexture( GL_TEXTURE_2D, 0 );
            }
        }

        std::cout << "texture: " << filepath().toStdString() << "; w:" << _width << "; h:" << _height << "; id:" << _id << std::endl;
    }
    return;
}
Picture* Texture::picture( size_t index )                   // |
{
    if( index < pictures().count() )
    {
        if( ref_pictures()[index] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Picture::class_name()) )
            return( static_cast<Picture*>(ref_pictures()[index]) );
    }
    return( 0 );
}
const Picture* Texture::picture_const( size_t index ) const // |
{
    if( index < pictures().count() )
    {
        if( cref_pictures().itemAt(index) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Picture::class_name()) )
            return( static_cast<const Picture*>(cref_pictures().itemAt(index)) );
    }
    return( 0 );
}
Picture* Texture::getPicture( size_t index )                // |
{
    return( picture(index) );
}
Picture* Texture::getPicture( const QString& namae )        // |
{
    for( size_t i = 0; i < pictures().count(); ++i )
    {
        Picture* pic = picture(i);
        if( 0 != pic && pic->name() == namae )
            return( pic );
    }
    return( 0 );
}
Texture::~Texture()
{
}




