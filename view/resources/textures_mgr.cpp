#include "textures_mgr.h"

//#include "../../render.h"

TexturesMgr::TexturesMgr( /*Render* render*/ )
    : XMLObject()
    , _modify( false )
//    , _render( render )
    // /////////////////////////////////////////////////////////// |
{
    bind_fields();
}
void TexturesMgr::load(const QString& namae                     // |
                              , const QString& filepath )       // |
{
    addTexture( new Texture( /*render(), */filepath) );
    Texture* t = texture( textures().count() - 1 );
    t -> addPicture( new Picture(namae, 0, 0, t->width(), t->height()) );
    return;
}
Texture* TexturesMgr::texture( size_t index )                   // |
{
    if( index < textures().count() )
    {
        if( ref_textures()[index] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Texture::class_name()) )
            return( static_cast<Texture*>(ref_textures()[index]) );
    }
    return( 0 );
}
const Texture* TexturesMgr::texture_const( size_t index ) const // |
{
    if( index < textures().count() )
    {
        if( cref_textures().itemAt(index) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Texture::class_name()) )
            return( static_cast<const Texture*>(cref_textures().itemAt(index)) );
    }
    return( 0 );
}
Picture* TexturesMgr::getPicture( const QString& namae )        // |
{
    for( size_t i = 0; i < textures().count(); ++i )
    {
        Picture* picture = texture(i) -> getPicture( namae );
        if( 0 != picture )
            return( picture );
    }
    return( 0 );
}
Texture* TexturesMgr::getTexture( const QString& filepath )     // |
{
    for( size_t i = 0; i < textures().count(); ++i )
    {
        if( texture(i) -> filepath() == filepath )
            return( texture(i) );
    }
    return( 0 );
}
TexturesMgr::~TexturesMgr()
{
    for( size_t i = 0; i < textures().count(); ++i )
        texture(i) -> release();
}



