#include "program_uniform.h"

ProgramUniform::ProgramUniform()
    : XMLObject()
    , _modify( false )
    , _projectionMtx  ( "u_projectionMtx" )
    , _viewMtx        ( "u_viewMtx"       )
    , _modelMtx       ( "u_modelMtx"      )
    , _cameraPos      ( "u_cameraPos"     )
    , _textureUnit    ( "u_textureUnit"   )
    , _lightsAmount   ( "u_lightAmount"   )
    , _shadowFiltering( "u_useShadowFiltering" )
    , _fontUnit       ( "u_fontUnit" )
    , _fontOffset     ( "u_fontOffset" )
    // //////////////////////////////// |
{
    bind_fields();
}
/// @section: uniform... projection matrix ///////////////////////////// |
const QString& ProgramUniform::projectionMtx() const                  // |
{
    return( _projectionMtx );
}
void ProgramUniform::setProjectionMtx( const QString& projectionMtx ) // |
{
    _modify = _modify || (projectionMtx != this -> projectionMtx());
    _projectionMtx = projectionMtx;
    return;
}
/// @section: uniform... view matrix /////////////////////// |
const QString& ProgramUniform::viewMtx() const            // |
{
    return( _viewMtx );
}
void ProgramUniform::setViewMtx( const QString& viewMtx ) // |
{
    _modify = _modify || (viewMtx != this -> viewMtx());
    _viewMtx = viewMtx;
    return;
}
/// @section: uniform... model matrix //////////////////////// |
const QString& ProgramUniform::modelMtx() const             // |
{
    return( _modelMtx );
}
void ProgramUniform::setModelMtx( const QString& modelMtx ) // |
{
    _modify = _modify || (modelMtx != this -> modelMtx());
    _modelMtx = modelMtx;
    return;
}
/// @section: uniform... camera position /////////////////////// |
const QString& ProgramUniform::cameraPos() const              // |
{
    return( _cameraPos );
}
void ProgramUniform::setCameraPos( const QString& cameraPos ) // |
{
    _modify = _modify || (cameraPos != this -> cameraPos());
    _cameraPos = cameraPos;
    return;
}
/// @section: uniform... texture /////////////////////////////////// |
const QString& ProgramUniform::textureUnit() const                // |
{
    return( _textureUnit );
}
void ProgramUniform::setTextureUnit( const QString& textureUnit ) // |
{
    _modify = _modify || (textureUnit != this -> textureUnit());
    _textureUnit = textureUnit;
    return;
}
/// @section: uniform... lights amount /////////////////////////////// |
const QString& ProgramUniform::lightsAmount() const                 // |
{
    return( _lightsAmount );
}
void ProgramUniform::setLightsAmount( const QString& lightsAmount ) // |
{
    _modify = _modify || (lightsAmount != this -> lightsAmount());
    _lightsAmount = lightsAmount;
    return;
}
/// @section: uniform... shadow filtering ////////////////////////////////// |
const QString& ProgramUniform::shadowFiltering() const                    // |
{
    return( _shadowFiltering );
}
void ProgramUniform::setShadowFiltering( const QString& shadowFiltering ) // |
{
    _modify = _modify || (shadowFiltering != this -> shadowFiltering());
    _shadowFiltering = shadowFiltering;
    return;
}
/// @section: uniform... font //////////////////////////////////// |
const QString& ProgramUniform::fontUnit() const                 // |
{
    return( _fontUnit );
}
const QString&ProgramUniform::fontOffset() const                // |
{
    return( _fontOffset );
}
void ProgramUniform::setFontUnit( const QString& fontUnit )     // |
{
    _modify = _modify || (fontUnit != this -> fontUnit());
    _fontUnit = fontUnit;
    return;
}
void ProgramUniform::setFontOffset( const QString& fontOffset ) // |
{
    _modify = _modify || (fontOffset != this->fontOffset());
    _fontOffset = fontOffset;
    return;
}
/// @section: initialize /////////////////////////////////////////////////// |
void ProgramUniform::initProjectionMtx( QGLFunctions* functions           // |
                                        , ProgramShader* program          // |
                                        , const QMatrix4x4& value ) const // |
{
    if( 0 != functions && 0 != program && !projectionMtx().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, projectionMtx() );
        if( -1 != loc )
        {
            program -> setUniformValue( functions, loc, value );
        }
    }
    return;
}
void ProgramUniform::initViewMtx( QGLFunctions* functions                 // |
                                  , ProgramShader* program                // |
                                  , const QMatrix4x4& value ) const       // |
{
    if( 0 != functions && 0 != program && !viewMtx().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, viewMtx() );
        if( -1 != loc )
        {
            program -> setUniformValue( functions, loc, value );
        }
    }
    return;
}
void ProgramUniform::initModelMtx( QGLFunctions* functions                // |
                                   , ProgramShader* program               // |
                                   , const QMatrix4x4& value ) const      // |
{
    if( 0 != functions && 0 != program && !modelMtx().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, modelMtx() );
        if( -1 != loc )
        {
            program -> setUniformValue( functions, loc, value );
        }
    }
    return;
}
void ProgramUniform::initCameraPos( QGLFunctions* functions               // |
                                    , ProgramShader* program              // |
                                    , const QVector4D& value ) const      // |
{
    if( 0 != functions && 0 != program && !cameraPos().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, cameraPos() );
        if( -1 != loc )
        {
            program -> setUniformValue( functions, loc, value );
        }
    }
    return;
}
void ProgramUniform::initTextureUnit( QGLFunctions* functions             // |
                                      , ProgramShader* program            // |
                                      , int value ) const                 // |
{
    if( 0 != functions && 0 != program && !textureUnit().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, textureUnit() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value - GL_TEXTURE0 );
    }
    return;
}
void ProgramUniform::initLightsAmount( QGLFunctions* functions            // |
                                       , ProgramShader* program           // |
                                       , size_t value ) const             // |
{
    if( 0 != functions && 0 != program && !lightsAmount().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, lightsAmount() );
        if( -1 != loc )
        {
            program -> setUniformValue( functions, loc, value );
        }
    }
    return;
}
void ProgramUniform::initShadowFiltering( QGLFunctions* functions         // |
                                          , ProgramShader* program        // |
                                          , int value ) const             // |
{
    if( 0 != functions && 0 != program && !shadowFiltering().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, shadowFiltering() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramUniform::initFontUnit( QGLFunctions* functions                // |
                                      , ProgramShader* program            // |
                                      , int value ) const                 // |
{
    if( 0 != functions && 0 != program && !fontUnit().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, fontUnit() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value >= GL_TEXTURE0 ? value - GL_TEXTURE0 : 0 );
    }
    return;
}
void ProgramUniform::initFontOffset( QGLFunctions* functions              // |
                                     , ProgramShader* program             // |
                                     , const QVector2D& offset ) const    // |
{
    if( 0 != functions && 0 != program && !fontOffset().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, fontOffset() );
        if( -1 != loc )
        {
            program -> setUniformValue( functions, loc, offset );
        }
    }
    return;
}
ProgramUniform::~ProgramUniform()
{

}
