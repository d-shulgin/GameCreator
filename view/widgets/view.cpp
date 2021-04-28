#include "view.h"

View::View( const QString& namae )
    : RenderItem()
    , _modify( false )
    , _name( namae )
    , _visibility( true )
    , _shadowEnable( false )
    // /////////////////// |
{
    bind_fields();
}
/// @section: program ///////////////////////////////////// |
void View::bind_program( QGLFunctions* functions ) const // |
{
    programsMgr().bind( functions, program() );
    return;
}
void View::bind_program( QGLFunctions* functions         // |
                         , const QString& namae ) const  // |
{
    if( !namae.isEmpty() )
        programsMgr().bind( functions, namae );
    return;
}
/// @section: model matrix ///////////////////////////////// |
void View::bind_modelMtx( QGLFunctions* functions ) const // |
{
    ProgramShader* program_shader = programsMgr().getProgram();
    if( 0 != program_shader )
    {
        QMatrix4x4 mtx_model = global_matrix() * transform().matrix();
        programsMgr().uniform().initModelMtx( functions
                                              , program_shader
                                              , mtx_model );
    }
    return;
}
/// @section: shadow Percentage Closer Filtering ////////////////// |
void View::bind_shadowFiltering( QGLFunctions* functions ) const // |
{
    ProgramShader* program_shader = programsMgr().getProgram();
    if( 0 != program_shader )
    {
        programsMgr().uniform().initShadowFiltering( functions
                                                     , program_shader
                                                     , shadowFilter().value() );
    }
    return;
}
/// @section: drawable ////////////////////////////////// |
void View::draw( QGLFunctions* functions ) const       // |
{
    if( !visibility() )
        return;
    if( 0 == functions )
        return;
    bind_program( functions );
    bind_modelMtx( functions );
    bind_shadowFiltering( functions );
    return;
}
void View::drawShadow( QGLFunctions* functions ) const // |
{
    if( 0 == functions )
        return;
    if( !visibility() )
        return;
    if( !shadowEnable() )
        return;
    bind_modelMtx( functions );
    return;
}
View::~View()
{
}
