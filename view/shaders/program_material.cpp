#include "program_material.h"

ProgramMaterial::ProgramMaterial()
    : XMLObject()
    , _modify( false )
    , _ambientColor  ( "u_material.ambientColor"    )
    , _ambientMap    ( "u_material.ambientMap"      )
    , _useAmbientMap ( "u_material.useAmbientMap"   )
    , _diffuseColor  ( "u_material.diffuseColor"    )
    , _diffuseMap    ( "u_material.diffuseMap"      )
    , _useDiffuseMap ( "u_material.useDiffuseMap"   )
    , _specularColor ( "u_material.specularColor"   )
    , _specularExp   ( "u_material.specExp"         )
    , _specularMap   ( "u_material.specularMap"     )
    , _useSpecularMap( "u_material.useSpecularMap"  )
    , _dissolve      ( "u_material.dissolve"        )
    , _halo          ( "u_material.halo"            )
    , _dissolveMap   ( "u_material.dissolveMap"     )
    , _useDissolveMap( "u_material.useDissolveMap"  )
    , _normalMap     ( "u_material.normalMap"       )
    , _useNormalMap  ( "u_material.useNormalMap"    )
    // //////////////////////////////////////////// |
{
    bind_fields();
}
/// @section: uniform... material.ambientColor //////////////////////// |
const QString& ProgramMaterial::ambientColor() const                 // |
{
    return( _ambientColor );
}
void ProgramMaterial::setAmbientColor( const QString& ambientColor ) // |
{
    _modify = _modify || (ambientColor != this -> ambientColor());
    _ambientColor = ambientColor;
    return;
}
/// @section: uniform... material.ambientMap //////////////////////////// |
const QString& ProgramMaterial::ambientMap() const                     // |
{
    return( _ambientMap );
}
void ProgramMaterial::setAmbientMap( const QString& ambientMap )       // |
{
    _modify = _modify || (ambientMap != this -> ambientMap());
    _ambientMap = ambientMap;
    return;
}
const QString& ProgramMaterial::useAmbientMap() const                  // |
{
    return( _useAmbientMap );
}
void ProgramMaterial::setUseAmbientMap( const QString& useAmbientMap ) // |
{
    _modify = _modify || (useAmbientMap != this -> useAmbientMap());
    _useAmbientMap = useAmbientMap;
    return;
}
/// @section: uniform... material.diffuseColor //////////////////////// |
const QString& ProgramMaterial::diffuseColor() const                 // |
{
    return( _diffuseColor );
}
void ProgramMaterial::setDiffuseColor( const QString& diffuseColor ) // |
{
    _modify = _modify || (diffuseColor != this -> diffuseColor());
    _diffuseColor = diffuseColor;
    return;
}
/// @section: uniform... material.diffuseMap //////////////////////////// |
const QString& ProgramMaterial::diffuseMap() const                     // |
{
    return( _diffuseMap );
}
void ProgramMaterial::setDiffuseMap( const QString& diffuseMap )       // |
{
    _modify = _modify || (diffuseMap != this -> diffuseMap());
    _diffuseMap = diffuseMap;
    return;
}
const QString& ProgramMaterial::useDiffuseMap() const                  // |
{
    return( _useDiffuseMap );
}
void ProgramMaterial::setUseDiffuseMap( const QString& useDiffuseMap ) // |
{
    _modify = _modify || (useDiffuseMap != this -> useDiffuseMap());
    _useDiffuseMap = useDiffuseMap;
    return;
}
/// @section: uniform... material.specularColor ///////////////////////// |
const QString& ProgramMaterial::specularColor() const                  // |
{
    return( _specularColor );
}
void ProgramMaterial::setSpecularColor( const QString& specularColor ) // |
{
    _modify = _modify || (specularColor != this -> specularColor());
    _specularColor = specularColor;
    return;
}
/// @section: uniform... material.specExp /////////////////////////// |
const QString& ProgramMaterial::specularExp() const                // |
{
    return( _specularExp );
}
void ProgramMaterial::setSpecularExp( const QString& specularExp ) // |
{
    _modify = _modify || (specularExp != this -> specularExp());
    _specularExp = specularExp;
    return;
}
/// @section: uniform... material.specularMap ///////////////////////////// |
const QString& ProgramMaterial::specularMap() const                      // |
{
    return( _specularMap );
}
void ProgramMaterial::setSpecularMap( const QString& specularMap )       // |
{
    _modify = _modify || (specularMap != this -> specularMap());
    _specularMap = specularMap;
    return;
}
const QString& ProgramMaterial::useSpecularMap() const                   // |
{
    return( _useSpecularMap );
}
void ProgramMaterial::setUseSpecularMap( const QString& useSpecularMap ) // |
{
    _modify = _modify || (useSpecularMap != this -> useSpecularMap());
    _useSpecularMap = useSpecularMap;
    return;
}
/// @section: uniform... material.dissolve //////////////////// |
const QString& ProgramMaterial::dissolve() const             // |
{
    return( _dissolve );
}
void ProgramMaterial::setDissolve( const QString& dissolve ) // |
{
    _modify = _modify || (dissolve != this -> dissolve());
    _dissolve = dissolve;
    return;
}
/// @section: uniform... material.halo //////////////// |
const QString& ProgramMaterial::halo() const         // |
{
    return( _halo );
}
void ProgramMaterial::setHalo( const QString& halo ) // |
{
    _modify = _modify || (halo != this -> halo());
    _halo = halo;
    return;
}
/// @section: uniform... material.dissolveMap ///////////////////////////// |
const QString& ProgramMaterial::dissolveMap() const                      // |
{
    return( _dissolveMap );
}
void ProgramMaterial::setDissolveMap( const QString& dissolveMap )       // |
{
    _modify = _modify || (dissolveMap != this -> dissolveMap());
    _dissolveMap = dissolveMap;
    return;
}
const QString& ProgramMaterial::useDissolveMap() const                   // |
{
    return( _useDissolveMap );
}
void ProgramMaterial::setUseDissolveMap( const QString& useDissolveMap ) // |
{
    _modify = _modify || (useDissolveMap != this -> useDissolveMap());
    _useDissolveMap = useDissolveMap;
    return;
}
/// @section: uniform... material.normalMap /////////////////////////// |
const QString& ProgramMaterial::normalMap() const                    // |
{
    return( _normalMap );
}
void ProgramMaterial::setNormalMap( const QString& normalMap )       // |
{
    _modify = _modify || (normalMap != this -> normalMap());
    _normalMap = normalMap;
    return;
}
const QString& ProgramMaterial::useNormalMap() const                 // |
{
    return( _useNormalMap );
}
void ProgramMaterial::setUseNormalMap( const QString& useNormalMap ) // |
{
    _modify = _modify || (useNormalMap != this -> useNormalMap());
    _useNormalMap = useNormalMap;
    return;
}
/// @section: initialize ///////////////////////////////////////////////// |
void ProgramMaterial::initAmbientColor( QGLFunctions* functions         // |
                                        , ProgramShader* program        // |
                                        , const Vector3& color ) const  // |
{
    if( 0 != functions && 0 != program && !ambientColor().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, ambientColor() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, color.vec() );
    }
    return;
}
void ProgramMaterial::initAmbientMap( QGLFunctions* functions           // |
                                      , ProgramShader* program          // |
                                      , int value ) const               // |
{
    if( 0 != functions && 0 != program )
    {
        if( value >= 0 )
        {
            if( !ambientMap().isEmpty() )
            {
                int loc_AmbienMap = program -> uniformLoc( functions, ambientMap() );
                if( -1 != loc_AmbienMap )
                    program -> setUniformValue( functions, loc_AmbienMap, value - GL_TEXTURE0 );
                if( !useAmbientMap().isEmpty() )
                {
                    int loc_useAmbienMap = program -> uniformLoc( functions, useAmbientMap() );
                    if( -1 != loc_useAmbienMap )
                        program -> setUniformValue( functions, loc_useAmbienMap, true );
                }
                return;
            }
        }
        if( !useAmbientMap().isEmpty() )
        {
            int loc_useAmbientMap = program -> uniformLoc( functions, useAmbientMap() );
            if( -1 != loc_useAmbientMap )
                program -> setUniformValue( functions, loc_useAmbientMap, false );
        }
    }
    return;
}
void ProgramMaterial::initDiffuseColor( QGLFunctions* functions         // |
                                        , ProgramShader* program        // |
                                        , const Vector3& color ) const  // |
{
    if( 0 != functions && 0 != program && !diffuseColor().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, diffuseColor() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, color.vec() );
    }
    return;
}
void ProgramMaterial::initDiffuseMap( QGLFunctions* functions           // |
                                      , ProgramShader* program          // |
                                      , int value ) const               // |
{
    if( 0 != functions && 0 != program )
    {
        if( value >= 0 )
        {
            if( !diffuseMap().isEmpty() )
            {
                int loc_DiffuseMap = program -> uniformLoc( functions, diffuseMap() );
                if( -1 != loc_DiffuseMap )
                    program -> setUniformValue( functions, loc_DiffuseMap, value - GL_TEXTURE0 );
                if( !useDiffuseMap().isEmpty() )
                {
                    int loc_useDiffuseMap = program -> uniformLoc( functions, useDiffuseMap() );
                    if( -1 != loc_useDiffuseMap )
                        program -> setUniformValue( functions, loc_useDiffuseMap, true );
                }
                return;
            }
        }
        if( !useDiffuseMap().isEmpty() )
        {
            int loc_useDiffuseMap = program -> uniformLoc( functions, useDiffuseMap() );
            if( -1 != loc_useDiffuseMap )
                program -> setUniformValue( functions, loc_useDiffuseMap, false );
        }
    }
    return;
}
void ProgramMaterial::initSpecularColor( QGLFunctions* functions        // |
                                         , ProgramShader* program       // |
                                         , const Vector3& color ) const // |
{
    if( 0 != functions && 0 != program && !specularColor().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, specularColor() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, color.vec() );
    }
    return;
}
void ProgramMaterial::initSpecularExp( QGLFunctions* functions          // |
                                       , ProgramShader* program         // |
                                       , float value ) const            // |
{
    if( 0 != functions && 0 != program && !specularExp().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, specularExp() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramMaterial::initSpecularMap( QGLFunctions* functions          // |
                                       , ProgramShader* program         // |
                                       , int value ) const              // |
{
    if( 0 != functions && 0 != program )
    {
        if( value >= 0 )
        {
            if( !specularMap().isEmpty() )
            {
                int loc_SpecularMap = program -> uniformLoc( functions, specularMap() );
                if( -1 != loc_SpecularMap )
                    program -> setUniformValue( functions, loc_SpecularMap, value - GL_TEXTURE0 );
                if( !useSpecularMap().isEmpty() )
                {
                    int loc_useSpecularMap = program -> uniformLoc( functions, useSpecularMap() );
                    if( -1 != loc_useSpecularMap )
                        program -> setUniformValue( functions, loc_useSpecularMap, true );
                }
                return;
            }
        }
        if( !useSpecularMap().isEmpty() )
        {
            int loc_useSpecularMap = program -> uniformLoc( functions, useSpecularMap() );
            if( -1 != loc_useSpecularMap )
                program -> setUniformValue( functions, loc_useSpecularMap, false );
        }
    }
    return;
}
void ProgramMaterial::initDissolve( QGLFunctions* functions             // |
                                    , ProgramShader* program            // |
                                    , float value ) const               // |
{
    if( 0 != functions && 0 != program && !dissolve().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, dissolve() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramMaterial::initHalo( QGLFunctions* functions                 // |
                                , ProgramShader* program                // |
                                , bool value ) const                    // |
{
    if( 0 != functions && 0 != program && !halo().isEmpty() )
    {
        int loc = program -> uniformLoc( functions, halo() );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramMaterial::initDissolveMap( QGLFunctions* functions          // |
                                       , ProgramShader* program         // |
                                       , int value ) const              // |
{
    if( 0 != functions && 0 != program )
    {
        if( value >= 0 )
        {
            if( !dissolveMap().isEmpty() )
            {
                int loc_DissolveMap = program -> uniformLoc( functions, dissolveMap() );
                if( -1 != loc_DissolveMap )
                    program -> setUniformValue( functions, loc_DissolveMap, value - GL_TEXTURE0 );
                if( !useDissolveMap().isEmpty() )
                {
                    int loc_useDissolveMap = program -> uniformLoc( functions, useDissolveMap() );
                    if( -1 != loc_useDissolveMap )
                        program -> setUniformValue( functions, loc_useDissolveMap, true );
                }
                return;
            }
        }
        if( !useDissolveMap().isEmpty() )
        {
            int loc_useDissolveMap = program -> uniformLoc( functions, useDissolveMap() );
            if( -1 != loc_useDissolveMap )
                program -> setUniformValue( functions, loc_useDissolveMap, false );
        }
    }
    return;
}
void ProgramMaterial::initNormalMap( QGLFunctions* functions            // |
                                     , ProgramShader* program           // |
                                     , int value ) const                // |
{
    if( 0 != functions && 0 != program )
    {
        if( value >= 0 )
        {
            if( !normalMap().isEmpty() )
            {
                int loc_NormalMap = program -> uniformLoc( functions, normalMap() );
                if( -1 != loc_NormalMap )
                    program -> setUniformValue( functions, loc_NormalMap, value - GL_TEXTURE0 );
                if( !useNormalMap().isEmpty() )
                {
                    int loc_useNormalMap = program -> uniformLoc( functions, useNormalMap() );
                    if( -1 != loc_useNormalMap )
                        program -> setUniformValue( functions, loc_useNormalMap, true );
                }
                return;
            }
        }
        if( !useNormalMap().isEmpty() )
        {
            int loc_useNormalMap = program -> uniformLoc( functions, useNormalMap() );
            if( -1 != loc_useNormalMap )
                program -> setUniformValue( functions, loc_useNormalMap, false );
        }
    }
    return;
}
ProgramMaterial::~ProgramMaterial()
{
}
