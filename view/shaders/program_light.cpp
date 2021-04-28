#include "program_light.h"

ProgramLight::ProgramLight()
    : XMLObject()
    , _modify( false )
    , _type         ( "u_light.type"          )
    , _power        ( "u_light.power"         )
    , _ambientColor ( "u_light.ambientColor"  )
    , _diffuseColor ( "u_light.diffuseColor"  )
    , _specularColor( "u_light.specularColor" )
    , _position     ( "u_light.position"      )
    , _direction    ( "u_light.direction"     )
    , _angle        ( "u_light.angle"         )
    , _borderArea   ( "u_light.borderArea"    )
    , _shadowMap    ( "u_light.shadowMap"     )
    , _useShadowMap ( "u_light.useShadowMap"  )
    // ////////////////////////////////////// |
{
    bind_fields();
}
/// @section: uniform... type ////////////////////// |
const QString& ProgramLight::type() const         // |
{
    return( _type );
}
void ProgramLight::setType( const QString& type ) // |
{
    _modify = _modify || (type != this -> type());
    _type = type;
    return;
}
/// @section: uniform... power /////////////////////// |
const QString& ProgramLight::power() const          // |
{
    return( _power );
}
void ProgramLight::setPower( const QString& power ) // |
{
    _modify = _modify || (power != this -> power());
    _power = power;
    return;
}
/// @section: uniform... ambient color ///////////////////////////// |
const QString& ProgramLight::ambientColor() const                 // |
{
    return( _ambientColor );
}
void ProgramLight::setAmbientColor( const QString& ambientColor ) // |
{
    _modify = _modify || (ambientColor != this -> ambientColor());
    _ambientColor = ambientColor;
    return;
}
/// @section: uniform... diffuse color ///////////////////////////// |
const QString& ProgramLight::diffuseColor() const                 // |
{
    return( _diffuseColor );
}
void ProgramLight::setDiffuseColor( const QString& diffuseColor ) // |
{
    _modify = _modify || (diffuseColor != this -> diffuseColor());
    _diffuseColor = diffuseColor;
    return;
}
/// @section: uniform... specular color ////////////////////////////// |
const QString& ProgramLight::specularColor() const                  // |
{
    return( _specularColor );
}
void ProgramLight::setSpecularColor( const QString& specularColor ) // |
{
    _modify = _modify || (specularColor != this -> specularColor());
    _specularColor = specularColor;
    return;
}
/// @section: uniform... position ////////////////////////// |
const QString& ProgramLight::position() const             // |
{
    return( _position );
}
void ProgramLight::setPosition( const QString& position ) // |
{
    _modify = _modify || (position != this -> position());
    _position = position;
    return;
}
/// @section: uniform... direction /////////////////////////// |
const QString& ProgramLight::direction() const              // |
{
    return( _direction );
}
void ProgramLight::setDirection( const QString& direction ) // |
{
    _modify = _modify || (direction != this -> direction());
    _direction = direction;
    return;
}
/// @section: uniform... angle /////////////////////// |
const QString& ProgramLight::angle() const          // |
{
    return( _angle );
}
void ProgramLight::setAngle( const QString& angle ) // |
{
    _modify = _modify || (angle != this -> angle());
    _angle = angle;
    return;
}
/// @section: uniform... border area /////////////////////////// |
const QString& ProgramLight::borderArea() const               // |
{
    return( _borderArea );
}
void ProgramLight::setBorderArea( const QString& borderArea ) // |
{
    _modify = _modify || (borderArea != this -> borderArea());
    _borderArea = borderArea;
    return;
}
/// @section: uniform... shadowMap ///////////////////////////////// |
const QString& ProgramLight::shadowMap() const                    // |
{
    return( _shadowMap );
}
void ProgramLight::setShadowMap( const QString& shadowMap )       // |
{
    _modify = _modify || (shadowMap != this -> shadowMap());
    _shadowMap = shadowMap;
    return;
}
const QString& ProgramLight::useShadowMap() const                 // |
{
    return( _useShadowMap );
}
void ProgramLight::setUseShadowMap( const QString& useShadowMap ) // |
{
    _modify = _modify || (useShadowMap != this -> useShadowMap());
    _useShadowMap = useShadowMap;
    return;
}
/// @section: initialize ////////////////////////////////////////////// |
QString ProgramLight::locName( size_t index                          // |
                               , const QString& namae ) const        // |
{
    if( !namae.isEmpty() )
    {
        QStringList items = namae.split( ".", QString::SkipEmptyParts );
        if( items.count() == 2 )
        {
            return( QString("%1[%2].%3").arg(items[0]).arg(index).arg(items[1]) );
        }
    }
    return( QString() );
}
void ProgramLight::initType( size_t index                            // |
                             , QGLFunctions* functions               // |
                             , ProgramShader* program                // |
                             , int value ) const                     // |
{
    QString locName = this -> locName( index, type() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramLight::initPower( size_t index                           // |
                              , QGLFunctions* functions              // |
                              , ProgramShader* program               // |
                              , float value ) const                  // |
{
    QString locName = this -> locName( index, power() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramLight::initAmbientColor( size_t index                    // |
                                     , QGLFunctions* functions       // |
                                     , ProgramShader* program        // |
                                     , const Vector3& color ) const  // |
{
    QString locName = this -> locName( index, ambientColor() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, color.vec() );
    }
    return;
}
void ProgramLight::initDiffuseColor( size_t index                    // |
                                     , QGLFunctions* functions       // |
                                     , ProgramShader* program        // |
                                     , const Vector3& color ) const  // |
{
    QString locName = this -> locName( index, diffuseColor() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, color.vec() );
    }
    return;
}
void ProgramLight::initSpecularColor( size_t index                   // |
                                      , QGLFunctions* functions      // |
                                      , ProgramShader* program       // |
                                      , const Vector3& color ) const // |
{
    QString locName = this -> locName( index, specularColor() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, color.vec() );
    }
    return;
}
void ProgramLight::initPosition( size_t index                        // |
                                 , QGLFunctions* functions           // |
                                 , ProgramShader* program            // |
                                 , const Vector3& value ) const      // |
{
    QString locName = this -> locName( index, position() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value.vec() );
    }
    return;
}
void ProgramLight::initDirection( size_t index                       // |
                                  , QGLFunctions* functions          // |
                                  , ProgramShader* program           // |
                                  , const Vector3& value ) const     // |
{
    QString locName = this -> locName( index, direction() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value.vec() );
    }
    return;
}
void ProgramLight::initAngle( size_t index                           // |
                              , QGLFunctions* functions              // |
                              , ProgramShader* program               // |
                              , const Angle& angle ) const           // |
{
    QString locName = this -> locName( index, this -> angle() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, angle.as_radians() );
    }
    return;
}
void ProgramLight::initBorderArea( size_t index                      // |
                                   , QGLFunctions* functions         // |
                                   , ProgramShader* program          // |
                                   , float value ) const             // |
{
    QString locName = this -> locName( index, this -> borderArea() );
    if( 0 != functions && 0 != program && !locName.isEmpty() )
    {
        int loc = program -> uniformLoc( functions, locName );
        if( -1 != loc )
            program -> setUniformValue( functions, loc, value );
    }
    return;
}
void ProgramLight::initShadowMap( size_t index                       // |
                                  , QGLFunctions* functions          // |
                                  , ProgramShader* program           // |
                                  , int value ) const                // |
{
    if( 0 != functions && 0 != program )
    {
        if( value >= 0 )
        {
            QString locName = this -> locName( index, this -> shadowMap() );
            if( !locName.isEmpty() )
            {
                int loc = program -> uniformLoc( functions, locName );
                if( -1 != loc  )
                    program -> setUniformValue( functions, loc, value - GL_TEXTURE0 );

                locName = this -> locName( index, this -> useShadowMap() );
                if( !locName.isEmpty() )
                {
                    int loc_use = program -> uniformLoc( functions, locName );
                    if( -1 != loc_use )
                        program -> setUniformValue( functions, loc_use, true );
                }
                return;
            }
        }
        QString locName = this -> locName( index, this -> useShadowMap() );
        if( !locName.isEmpty() )
        {
            int loc_use = program -> uniformLoc( functions, locName );
            if( -1 != loc_use )
                program -> setUniformValue( functions, loc_use, false );
        }
    }
    return;
}
ProgramLight::~ProgramLight()
{
}
