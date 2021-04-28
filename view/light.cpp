#include "light.h"
#include <math.h>

Light::Light()
    : RenderItem()
    , _modify( false )
    , _power( 1.0f )
    , _ambientColor ( Vector3(1.0f, 1.0f, 1.0f) )
    , _diffuseColor ( Vector3(1.0f, 1.0f, 1.0f) )
    , _specularColor( Vector3(1.0f, 1.0f, 1.0f) )
    , _active( true )
    // ///////////// |
{
    bind_fields();
}
/// @section: power of light ///////// |
float Light::power() const          // |
{
    return _power;
}
void Light::setPower( float power ) // |
{
    _modify = _modify || (power != this -> power());
    _power = power;
    return;
}
/// @section: ambient color ///////////////////////////////// |
const Vector3& Light::ambientColor() const                 // |
{
    return _ambientColor;
}
void Light::setAmbientColor( const Vector3& ambientColor ) // |
{
    _modify = _modify || (ambientColor != this -> ambientColor());
    _ambientColor = ambientColor;
    return;
}
/// @section: diffuse color ///////////////////////////////// |
const Vector3& Light::diffuseColor() const                 // |
{
    return _diffuseColor;
}
void Light::setDiffuseColor( const Vector3& diffuseColor ) // |
{
    _modify = _modify || (diffuseColor != this -> diffuseColor());
    _diffuseColor = diffuseColor;
    return;
}
/// @section: specular color ////////////////////////////////// |
const Vector3& Light::specularColor() const                  // |
{
    return _specularColor;
}
void Light::setSpecularColor( const Vector3& specularColor ) // |
{
    _modify = _modify || (specularColor != this -> specularColor());
    _specularColor = specularColor;
    return;
}
/// @section: control ///////////////// |
bool Light::active() const           // |
{
    return( _active );
}
void Light::setActive( bool active ) // |
{
    _modify = _modify || (active != this -> active());
    _active = active;
    return;
}
/// @section: shadow ////////////////////////////////////////////// |
Shadow* Light::shadow()                                          // |
{
    if( _shadow.count() > 0 )
    {
        XMLObject* object = _shadow[0];
        if( 0 != object )
        {
            if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Shadow::class_name()) )
                return( static_cast<Shadow*>(object) );
        }
    }
    return( 0 );
}
const Shadow*Light::shadow_const() const                         // |
{
    if( _shadow.count() > 0 )
    {
        const XMLObject* object = _shadow.itemAt(0);
        if( 0 != object )
        {
            if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Shadow::class_name()) )
                return( static_cast<const Shadow*>(object) );
        }
    }
    return( 0 );
}
void Light::drawShadow( QGLFunctions* functions                  // |
                        , const Shadow::Callback* handle ) const // |
{
    if( _shadow.count() > 0 )
    {
        const XMLObject* object = _shadow.itemAt(0);
        if( 0 != object )
        {
            if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(Shadow::class_name()) )
            {
                const Shadow* o_shadow = static_cast<const Shadow*>(object);
                o_shadow -> draw( functions, handle );
            }
        }
    }
    return;
}
/// @section: initialize /////////////////////////// |
void Light::initialize( QGLFunctions* functions ) // |
{
    Shadow* o_shadow = shadow();
    if( 0 != o_shadow )
        o_shadow -> initialize( functions );
    return;
}
/// @section: bind /////////////////////////////////// |
void Light::bind( size_t index                      // |
                  , ProgramShader* shader_program   // |
                  , QGLFunctions* functions ) const // |
{
    if( 0 != functions && 0 != shader_program && shader_program -> is_linked() )
    {
        if( isSupported(shader_program -> name()) )
        {
            programsMgr().uniform().light().initPower( index, functions
                                                       , shader_program
                                                       , power() );
            programsMgr().uniform().light().initAmbientColor( index, functions
                                                              , shader_program
                                                              , ambientColor() );
            programsMgr().uniform().light().initDiffuseColor( index, functions
                                                              , shader_program
                                                              , diffuseColor() );
            programsMgr().uniform().light().initSpecularColor( index, functions
                                                               , shader_program
                                                               , specularColor() );
            const Shadow* shadow = this -> shadow_const();
            if( 0 != shadow && shadow -> active() && 0 != shadow -> depthMap() )
            {
                GLenum unit = programsMgr().ref_textureUnits().lock( "ShadowMap" );
                functions -> glActiveTexture( unit );
                glBindTexture( GL_TEXTURE_2D, shadow -> depthMap() );
                programsMgr().uniform().light().initShadowMap( index, functions
                                                               , shader_program
                                                               , unit );
                programsMgr().uniform().shadow().initEnable( index, functions
                                                             , shader_program
                                                             , true );
                shadow -> bind( index, shader_program, functions );
            }
        }
    }
    return;
}
Light::~Light()
{
}


LightDirection::LightDirection()
    : Light()
    , _modify( false )
    , _direction( Vector3(0.0f, 0.0f, -1.0f) )
//    , _shadowDistance( 1000.0f )
{
    bind_fields();
}
/// @section: direction //////////////////////////////////////// |
const Vector3& LightDirection::direction() const              // |
{
    return _direction;
}
void LightDirection::setDirection( const Vector3& direction ) // |
{
    _modify = _modify || (direction != this -> direction());
    _direction = direction;
    ShadowDirection* shadow = this -> shadow();
    if( 0 != shadow )
        shadow -> setDirection( direction );
    return;
}
/// @section: shadow ////////////// |
ShadowDirection* LightDirection::shadow()
{
    if( _shadow.count() > 0 )
    {
        XMLObject* object = _shadow[0];
        if( 0 != object )
        {
            if( object -> xml_class_name().split(".", QString::SkipEmptyParts).contains(ShadowDirection::class_name()) )
                return( static_cast<ShadowDirection*>(object) );
        }
    }
    return( 0 );
}
void LightDirection::drawShadow( QGLFunctions* functions                  // |
                                 , const Shadow::Callback* handle ) const // |
{
    Light::drawShadow( functions, handle );
    return;
}
/// @section: shadow /////////////////////////////////////////////// |
//float LightDirection::shadowDistance() const                      // |
//{
//    return( _shadowDistance );
//}
//const QString& LightDirection::shadowMainObject() const           // |
//{
//    return( _shadowMainObject );
//}
//void LightDirection::setShadow( const QString& namaeMainObject    // |
//                                , float distance )                // |
//{
//    if( !namaeMainObject.isEmpty() )
//    {
//        _modify = _modify || (namaeMainObject != this->shadowMainObject())
//                || (distance != this->shadowDistance());
//        _shadowMainObject = namaeMainObject;
//        _shadowDistance = distance;
//        Light::setShadow( true );
//    }
//    return;
//}
//void LightDirection::drawShadow( QGLFunctions* functions          // |
//                                 , const Callback* handle ) const // |
//{
//    Light::drawShadow( functions, handle );
//    return;
//}
/// @section: bind //////////////////////////////////////////// |
void LightDirection::bind( size_t index                      // |
                           , ProgramShader* shader_program   // |
                           , QGLFunctions* functions ) const // |
{
    Light::bind( index, shader_program, functions );
    if( 0 != functions && 0 != shader_program && shader_program -> is_linked() )
    {
        if( isSupported(shader_program -> name()) )
        {
            programsMgr().uniform().light().initType( index, functions
                                                      , shader_program
                                                      , Light::eDirection );
            programsMgr().uniform().light().initDirection( index, functions
                                                           , shader_program
                                                           , direction() );
        }
    }
    return;
}
LightDirection::~LightDirection()
{
}


LightPoint::LightPoint()
    : Light()
    , _modify( false )
    , _position( Vector3(0.0f, 0.0f, 0.0f) )
{
    bind_fields();
}
/// @section: position /////////////////////////////////// |
const Vector3& LightPoint::position() const             // |
{
    return( _position );
}
void LightPoint::setPosition( const Vector3& position ) // |
{
    _modify = _modify || (position != this -> position());
    _position = position;
    return;
}
/// @section: bind //////////////////////////////////////// |
void LightPoint::bind( size_t index                      // |
                       , ProgramShader* shader_program   // |
                       , QGLFunctions* functions ) const // |
{
    Light::bind( index, shader_program, functions );
    if( 0 != functions && 0 != shader_program && shader_program -> is_linked() )
    {
        if( isSupported(shader_program -> name()) )
        {
            programsMgr().uniform().light().initType( index, functions
                                                      , shader_program
                                                      , Light::ePoint );
            programsMgr().uniform().light().initPosition( index, functions
                                                          , shader_program
                                                          , position() );
        }
    }
    return;
}
LightPoint::~LightPoint()
{
}


LightSpot::LightSpot()
    : Light()
    , _modify( false )
    , _position( Vector3(0.0f, 0.0f, 0.0f) )
    , _direction( Vector3(0.0f, 0.0f, -1.0f) )
    , _angle( Angle(60.0f, Angle::degrees_unit) )
    , _borderArea( 0.10f )
{
    bind_fields();
}
/// @section: position ////////////////////////////////// |
const Vector3& LightSpot::position() const             // |
{
    return( _position );
}
void LightSpot::setPosition( const Vector3& position ) // |
{
    _modify = _modify || (position != this -> position());
    _position = position;
    return;
}
/// @section: direction /////////////////////////////////// |
const Vector3& LightSpot::direction() const              // |
{
    return _direction;
}
void LightSpot::setDirection( const Vector3& direction ) // |
{
    _modify = _modify || (direction != this -> direction());
    _direction = direction;
    return;
}
/// @section: angle (0..90) ///////////////////// |
const Angle& LightSpot::angle() const          // |
{
    return( _angle );
}
void LightSpot::setAngle( const Angle& angle ) // |
{
    if( angle.as_degrees() <= 90.0 )
    {
        _modify = _modify || (angle != this -> angle());
        _angle = angle;
    }
    return;
}
/// @section: border area (0..1) /////////////////// |
float LightSpot::borderArea() const               // |
{
    return( _borderArea );
}
void LightSpot::setBorderArea( float borderArea ) // |
{
    _modify = _modify || (borderArea != this -> borderArea());
    _borderArea = borderArea;
    return;
}
/// @section: bind /////////////////////////////////////// |
void LightSpot::bind( size_t index                      // |
                      , ProgramShader* shader_program   // |
                      , QGLFunctions* functions ) const // |
{
    Light::bind( index, shader_program, functions );
    if( 0 != functions && 0 != shader_program && shader_program -> is_linked() )
    {
        if( isSupported(shader_program->name()) )
        {
            programsMgr().uniform().light().initType( index, functions
                                                      , shader_program
                                                      , Light::eSpot );
            programsMgr().uniform().light().initPosition( index, functions
                                                          , shader_program
                                                          , position() );
            programsMgr().uniform().light().initDirection( index, functions
                                                           , shader_program
                                                           , direction() );
            programsMgr().uniform().light().initAngle( index, functions
                                                       , shader_program
                                                       , angle() );
            programsMgr().uniform().light().initBorderArea( index, functions
                                                            , shader_program
                                                            , borderArea() );
        }
    }
    return;
}
LightSpot::~LightSpot()
{
}
