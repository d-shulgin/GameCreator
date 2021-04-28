#include "layer_gui.h"

LayerGUI::LayerGUI()
    : Layer()
    , _modify( false )
{
    bind_fields();
}
void LayerGUI::draw( QGLFunctions* functions ) const
{
    glDisable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_FRONT );
    glFrontFace( GL_CCW );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    Layer::draw( functions );
    return;
}
LayerGUI::~LayerGUI()
{
}

