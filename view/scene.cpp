#include "scene.h"

Scene::Scene()
    : XMLObject()
    , _modify( false )
    , _width( 0 )
    , _height( 0 )
{
    bind_fields();
}
/// @section: layers /////////////////////////////////// |
Layer* Scene::layer( size_t index )                   // |
{
    if( index < layers().count() )
    {
        if( ref_layers()[index] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Layer::class_name()) )
            return( static_cast<Layer*>(ref_layers()[index]) );
    }
    return( 0 );
}
const Layer* Scene::layer_const( size_t index ) const // |
{
    if( index < layers().count() )
    {
        if( cref_layers().itemAt(index) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Layer::class_name()) )
            return( static_cast<const Layer*>(cref_layers().itemAt(index)) );
    }
    return( 0 );
}
/// @section: drawable /////////////////////////////////// |
void Scene::prepareDraw()                               // |
{
    QMatrix4x4 mtx_global;
    mtx_global.setToIdentity();
    for( size_t i = 0; i < layers().count(); ++i )
    {
        layer(i) -> setGlobalMtx( mtx_global );
    }
    if( 0 != dbg_layer() )
        dbg_layer() -> setGlobalMtx( mtx_global );
    return;
}
void Scene::draw( QGLFunctions* functions ) const       // |
{
    drawShadow( functions );

    glViewport( 0, 0, width(), height() );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    for( size_t i = 0; i < layers().count(); ++i )
        layer_const(i) -> draw( functions );
    if( 0 != dbg_layer_const() )
        dbg_layer_const() -> draw( functions );
    return;
}
void Scene::drawShadow( QGLFunctions* functions ) const // |
{
//    std::cout << "[Scene::drawShadow...]" << std::endl;
    for( size_t i = 0; i < layers().count(); ++i )
        layer_const(i) -> drawShadow( functions );
//    std::cout << "[Scene::drawShadow...] << finish >>" << std::endl;
    return;
}
/// @section: resizeable //////////// |
void Scene::resize( int w, int h ) // |
{
    _width  = w;
    _height = h;
    for( size_t i = 0; i < layers().count(); ++i )
        layer(i) -> resize( w, h );
    return;
}
/// @section: initialize /////////////////////////// |
void Scene::initialize( QGLFunctions* functions ) // |
{
    for( size_t i = 0; i < layers().count(); ++i )
        layer(i) -> initialize( functions );
    return;
}
/// @section: debug ////////////////////////// |
Layer* Scene::dbg_layer()                   // |
{
    if( _dbg_layer.count() > 0 )
    {
        if( _dbg_layer[0] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Layer::class_name()) )
            return( static_cast<Layer*>(_dbg_layer[0]) );
    }
    return( 0 );
}
const Layer* Scene::dbg_layer_const() const // |
{
    if( _dbg_layer.count() > 0 )
    {
        if( _dbg_layer.itemAt(0) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Layer::class_name()) )
            return( static_cast<const Layer*>(_dbg_layer.itemAt(0)) );
    }
    return( 0 );
}
Scene::~Scene()
{
}

