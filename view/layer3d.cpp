#include "layer3d.h"

Layer3D::Layer3D()
    : Layer()
    , _modify( false )
{
    bind_fields();
}
void Layer3D::draw( QGLFunctions* functions ) const
{
    glEnable( GL_DEPTH_TEST );
    //glEnable( GL_CULL_FACE );
    glDisable( GL_CULL_FACE );
    glCullFace( GL_FRONT );
    glFrontFace( GL_CCW );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    Layer::draw( functions );
    return;
}
void Layer3D::drawShadow( QGLFunctions* functions ) const
{
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_FRONT );
    glFrontFace( GL_CCW );
    glEnable( GL_BLEND );
    glBlendFunc( GL_ONE, GL_ZERO );

    Layer::drawShadow( functions );
    return;
}
Layer3D::~Layer3D()
{
}
