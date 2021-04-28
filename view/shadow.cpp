#include "shadow.h"

Shadow::Shadow( const QString& program )
    : RenderItem()
    , _modify( false )
    , _program( program )
    , _active( true )
    , _depthFBO( 0 )
    , _depthMap( 0 )
    , _gl_func( 0 )
{
    bind_fields();
}
Shadow::Shadow( const QString& program
                , Quality::id id )
    : RenderItem()
    , _modify( false )
    , _program( program )
    , _active( true )
    , _depthFBO( 0 )
    , _depthMap( 0 )
    , _gl_func( 0 )
    , _quality( EnumAs<Quality>(Quality(id)) )
{
    bind_fields();
}
/// @section: program ////////////////////////////// |
const QString& Shadow::program() const            // |
{
    return( _program );
}
void Shadow::setProgram( const QString& program ) // |
{
    _modify = _modify || (program != this -> program());
    _program = program;
    return;
}
/// @section: activate status ////////// |
bool Shadow::active() const           // |
{
    return( _active );
}
void Shadow::setActive( bool active ) // |
{
    _modify = _modify || (active != this -> active());
    _active = active;
    return;
}
/// @section: program callback //////////////////////////////////////////////// |
void Shadow::event_ProgramActivated( ProgramShader* program                  // |
                                     , QGLFunctions* functions ) const       // |
{
    bind_projectionMtx( program, functions );
    bind_viewMtx( program, functions );
    return;
}
void Shadow::event_ProgramDeactivated( ProgramShader* /*program*/            // |
                                       , QGLFunctions* /*functions*/ ) const // |
{
}
QString Shadow::event_DefaultProgram() const                                 // |
{
    return( program() );
}
/// @section: drawable /////////////////////////////////////// |
void Shadow::draw( QGLFunctions* functions                  // |
                   , const Shadow::Callback* handle ) const // |
{
    //std::cout << "[Shadow::draw...]" << std::endl;
    if( active() )
    {
        bindDepthFBO( functions );
        if( !program().isEmpty() )
        {
            programsMgr().setCallback( this );
            programsMgr().bind( functions, program() );
        }
        if( 0 != handle )
            handle -> event_DrawShadow( functions );
        programsMgr().unbind( programsMgr().getProgram(), functions );
        unbindDepthFBO( functions );
    }
    //std::cout << "[Shadow::draw...] << finish >>" << std::endl;
    return;
}
/// @section: initialize //////////////////////////// |
void Shadow::initialize( QGLFunctions* functions ) // |
{
    _gl_func = functions;
    createDepthFBO( functions );
    return;
}
/// @section: frame buffer //////////////////////////////////// |
void Shadow::createDepthFBO( QGLFunctions* functions )       // |
{
    if( 0 == functions )
        return;
    if( 0 == _depthMap )
    {
        glGenTextures( 1, &_depthMap );
        if( 0 != _depthMap )
        {
            glBindTexture( GL_TEXTURE_2D, _depthMap );
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA
                          , quality().value()
                          , quality().value(), 0, GL_RGBA, GL_FLOAT, 0 );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
        }
    }
    if( 0 == _depthFBO )
    {
        functions -> glGenFramebuffers( 1, &_depthFBO );
        if( 0 != _depthFBO )
        {
            functions -> glBindFramebuffer( GL_FRAMEBUFFER, _depthFBO );
            if( 0 != _depthMap )
            {
                functions -> glFramebufferTexture2D( GL_FRAMEBUFFER
                                                     , GL_COLOR_ATTACHMENT0
                                                     , GL_TEXTURE_2D, _depthMap, 0 );
            }
            functions -> glBindFramebuffer( GL_FRAMEBUFFER, 0 );
        }
    }
    return;
}
void Shadow::bindDepthFBO( QGLFunctions* functions ) const   // |
{
    if( 0 != functions && 0 != _depthFBO )
    {
        glViewport(0, 0, quality().value(), quality().value() );
        functions -> glBindFramebuffer( GL_FRAMEBUFFER, _depthFBO );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }
    return;
}
void Shadow::unbindDepthFBO( QGLFunctions* functions ) const // |
{
    if( 0 != functions )
        functions -> glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    return;
}
Shadow::~Shadow()
{
}



ShadowDirection::ShadowDirection( const QString& program )
    : Shadow( program )
    , _modify( false )
    , _direction( Vector3(0.0f, 0.0f, -1.0f) )
    , _target( Vector3(0.0f, 0.0f, 0.0f) )
    , _distance( 100.0f )
{
    bind_fields();
    _projection.setToIdentity();
    _projection.ortho( -70.0, +70.0, -70.0, +70.0, -200.0, 200.0 );
    create_view();
}
ShadowDirection::ShadowDirection( const QString& program
                                  , Quality::id id )
    : Shadow( program, id )
    , _modify( false )
    , _direction( Vector3(0.0f, 0.0f, -1.0f) )
    , _target( Vector3(0.0f, 0.0f, 0.0f) )
    , _distance( 100.0f )
{
    bind_fields();
    _projection.setToIdentity();
    _projection.ortho( -70.0, +70.0, -70.0, +70.0, -200.0, 200.0 );
    create_view();
}
/// @section: bind data ////////////////////////////////////////////////////// |
void ShadowDirection::bind_projectionMtx( ProgramShader* program            // |
                                          , QGLFunctions* functions ) const // |
{
    if( 0 != functions && 0 != program && program -> is_linked() )
    {
        programsMgr().uniform().initProjectionMtx( functions, program, projection() );
    }
    return;
}
void ShadowDirection::bind_viewMtx( ProgramShader* program                  // |
                                    , QGLFunctions* functions ) const       // |
{
    if( 0 != functions && 0 != program && program -> is_linked() )
    {
        programsMgr().uniform().initViewMtx( functions, program, view() );
    }
    return;
}
void ShadowDirection::bind( size_t index                                    // |
                            , ProgramShader* program                        // |
                            , QGLFunctions* functions ) const               // |
{
    if( 0 != functions && 0 != program && program -> is_linked() )
    {
        programsMgr().uniform().shadow().initProjectionMtx( index, functions
                                                            , program
                                                            , projection() );
        programsMgr().uniform().shadow().initViewMtx( index, functions
                                                      , program
                                                      , view() );
    }
    return;
}
/// @section: direction ///////////////////////////////////////// |
const Vector3& ShadowDirection::direction() const              // |
{
    return( _direction );
}
void ShadowDirection::setDirection( const Vector3& direction ) // |
{
    _direction = direction;
    create_view();
    return;
}
/// @section: target ////////////////////////////////////// |
const Vector3& ShadowDirection::target() const           // |
{
    return( _target );
}
void ShadowDirection::setTarget( const Vector3& target ) // |
{
    _target = target;
    create_view();
    return;
}
/// @section: distance /////////////////////////////// |
float ShadowDirection::distance() const             // |
{
    return( _distance );
}
void ShadowDirection::setDistance( float distance ) // |
{
    _distance = distance;
    create_view();
    return;
}
ShadowDirection::~ShadowDirection()
{
}
