#include "layer.h"

Layer::Layer()
    : RenderItem()
    , _modify( false )
    , _current_camera_id( 0 )
    // //////////////////// |
{
    bind_fields();
}
/// @section: program... global model matrix ///////// |
void Layer::setGlobalMtx( const QMatrix4x4& mtx )   // |
{
    for( size_t i = 0; i < views().count(); ++i )
    {
        View* v = view(i);
        if( 0 != v )
            v -> setGlobalMtx( mtx );
    }
    return;
}
/// @section: camera //////////////////////////////////////// |
Camera* Layer::camera( size_t index )                      // |
{
    if( index < cameras().count() )
    {
        if( ref_cameras()[index] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Camera::class_name()) )
            return( static_cast<Camera*>(ref_cameras()[index]) );
    }
    return( 0 );
}
const Camera* Layer::camera_const( size_t index ) const    // |
{
    if( index < cameras().count() )
    {
        if( cref_cameras().itemAt(index) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Camera::class_name()) )
            return( static_cast<const Camera*>(cref_cameras().itemAt(index)) );
    }
    return( 0 );
}
void Layer::bind_camera( ProgramShader* shader_program     // |
                         , QGLFunctions* functions ) const // |
{
    if( 0 != shader_program && shader_program -> is_linked() )
    {
        for( size_t i = 0; i < cameras().count(); ++i )
        {
            const Camera* camera = camera_const(i);
            if( 0 != camera && camera -> bind(shader_program, functions) )
                return;
        }
    }
    return;
}
/// @section: light //////////////////////////////////////// |
Light* Layer::light( size_t index )                       // |
{
    if( index < lights().count() )
    {
        XMLObject* object = ref_lights()[index];
        if( 0 != object )
        {
            if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Light::class_name()) )
                return( static_cast<Light*>(object) );
        }
    }
    return( 0 );
}
const Light* Layer::light_const( size_t index ) const     // |
{
    if( index < lights().count() )
    {
        const XMLObject* object = cref_lights().itemAt(index);
        if( 0 != object )
        {
            if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Light::class_name()) )
                return( static_cast<const Light*>(object) );
        }
    }
    return( 0 );
}
void Layer::bind_lights( ProgramShader* shader_program    // |
                        , QGLFunctions* functions ) const // |
{
    if( 0 != shader_program && shader_program -> is_linked() )
    {
        if( isSupported(shader_program -> name()) )
        {
            size_t active_lights = 0;
            for( size_t i = 0; i < lights().count(); ++i )
            {
                const Light* o_light = light_const(i);
                if( 0 != o_light && o_light -> active() )
                {
                    active_lights ++;
                    if( active_lights <= MAX_LIGHTS )
                        o_light -> bind( i, shader_program, functions );
                    else
                        active_lights = MAX_LIGHTS;
                }
            }
            programsMgr().uniform().initLightsAmount( functions
                                                      , shader_program
                                                      , active_lights );
        }
    }
    return;
}
/// @section: view /////////////////////////////////// |
View *Layer::view( size_t index )                   // |
{
    if( index < views().count() )
    {
        if( ref_views()[index] -> xml_class_name().split(".", QString::SkipEmptyParts).contains(View::class_name()) )
            return( static_cast<View*>(ref_views()[index]) );
    }
    return( 0 );
}
const View *Layer::view_const( size_t index ) const // |
{
    if( index < views().count() )
    {
        if( cref_views().itemAt(index) -> xml_class_name().split(".", QString::SkipEmptyParts).contains(View::class_name()) )
            return( static_cast<const View*>(cref_views().itemAt(index)) );
    }
    return( 0 );
}
View* Layer::getView( size_t index )                // |
{
    return( view(index) );
}
View* Layer::getView( const QString& namae )        // |
{
    View* found = 0;
    QString result;
    for( size_t i = 0; i < views().count(); ++i )
    {
        result = view_const(i) -> name();
        if( result == namae )
            return( view(i) );
        else if( result.isEmpty() || namae.left(result.length()) == result )
        {
            Group* group = XMLObject::ptr_cast< Group >( ref_views()[i] );
            if( 0 != group )
                found = group -> getChild( namae, result );
        }
        if( 0 != found )
            return( found );
    }
    return( 0 );
}
/// @section: drawable interface ///////////////////////// |
void Layer::draw( QGLFunctions* functions ) const       // |
{
    programsMgr().setCallback( this );
    // bind default program of layer |
    {
        programsMgr().bind( functions, default_program() );
    }
    for( size_t i = 0; i < views().count(); ++i )
    {
        view_const(i) -> draw( functions );
    }
    programsMgr().unbind( programsMgr().getProgram(), functions );
    return;
}
void Layer::drawShadow( QGLFunctions* functions ) const // |
{
//    std::cout << "[Layer::drawShadow...]" << std::endl;
    for( size_t i = 0; i < lights().count(); ++i )
    {
        const Light* o_light = light_const(i);
        if( 0 != o_light && o_light -> active() /*&& o_light -> shadowEnabled()*/ )
        {
            o_light -> drawShadow( functions, this );
        }
    }
//    std::cout << "[Layer::drawShadow...] << finish >>" << std::endl;
    return;
}
/// @section: resizeable interface /////////// |
void Layer::resize( int width, int height ) // |
{
    for( size_t i = 0; i < cameras().count(); ++i )
    {
        camera(i) -> resize( width, height );
    }
    return;
}
/// @section: initialize /////////////////////////// |
void Layer::initialize( QGLFunctions* functions ) // |
{
    for( size_t i = 0; i < lights().count(); ++i )
    {
        Light* o_light = light(i);
        if( 0 != o_light )
            o_light -> initialize( functions );
    }
    return;
}
/// @section: program callback ////////////////////////////////////////////// |
void Layer::event_ProgramActivated( ProgramShader* program                 // |
                                    , QGLFunctions* functions ) const      // |
{
    bind_camera( program, functions );
    bind_lights( program, functions );
    return;
}
void Layer::event_ProgramDeactivated( ProgramShader* /*program*/           // |
                                     , QGLFunctions* /*functions*/ ) const // |
{
    return;
}
QString Layer::event_DefaultProgram() const                                // |
{
    return( default_program() );
}
/// @section: light callback /////////////////////////////////// |
void Layer::event_DrawShadow( QGLFunctions* functions ) const // |
{
//    std::cout << "[Layer::event_DrawShadow...]" << std::endl;
    for( size_t i = 0; i < views().count(); ++ i )
        view_const(i) -> drawShadow( functions );
    return;
}
Layer::~Layer()
{
}
