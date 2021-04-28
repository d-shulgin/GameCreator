#include "material.h"

Material::Material( const QString& namae )
    : XMLObject()
    , _modify( false )
    , _name( namae )
    // /////////// |
{
    bind_fields();
    _ambientColor  = Vector3( 1.0f, 1.0f, 1.0f );
    _diffuseColor  = Vector3( 0.0f, 0.0f, 0.0f );
    _specularColor = Vector3( 0.0f, 0.0f, 0.0f );
    _specularExponent = 60.0f;
    _dissolve = 1.0f;
    _halo = false;
}
/// @section: namae ///////////////////////////// |
const QString& Material::name() const          // |
{
    return( _name );
}
void Material::setName( const QString& namae ) // |
{
    QString origin = name();
    _name = namae;
    _modify = _modify || (origin != name());
    return;
}
/// @section: ambient color (Ka) ///////////////////////////////// |
const Vector3& Material::ambientColor() const                   // |
{
    return( _ambientColor );
}
void Material::setAmbientColor( const Vector3& ambientColor )   // |
{
    Vector3 origin = this -> ambientColor();
    _ambientColor = ambientColor;
    _modify = _modify || (origin != this -> ambientColor());
    return;
}
/// @section: diffuse color (Kd) ///////////////////////////////// |
const Vector3& Material::diffuseColor() const                   // |
{
    return( _diffuseColor );
}
void Material::setDiffuseColor( const Vector3& diffuseColor )   // |
{
    Vector3 origin = this -> diffuseColor();
    _diffuseColor = diffuseColor;
    _modify = _modify || (origin != this->diffuseColor());
    return;
}
/// @section: specular color (Ks) //////////////////////////////// |
const Vector3& Material::specularColor() const                  // |
{
    return( _specularColor );
}
void Material::setSpecularColor( const Vector3& specularColor ) // |
{
    Vector3 origin = this -> specularColor();
    _specularColor = specularColor;
    _modify = _modify || (origin != this -> specularColor());
    return;
}
/// @section: specular exponent (Ns) /////////////// |
float Material::specularExponent() const          // |
{
    return( _specularExponent );
}
void Material::setSpecularExponent( float shine ) // |
{
    float origin = this -> specularExponent();
    _specularExponent = shine;
    _modify = _modify || (origin != this -> specularExponent());
    return;
}
/// @section: dissolve (d factor) ///////////// |
float Material::dissolve() const             // |
{
    return _dissolve;
}
void Material::setDissolve( float dissolve ) // |
{
    float origin = this -> dissolve();
    _dissolve = dissolve;
    _modify = _modify || (origin != this -> dissolve());
    return;
}
/// @section: halo dissolve (d -halo factor) // |
bool Material::halo() const         // |
{
    return _halo;
}
void Material::setHalo( bool halo ) // |
{
    bool origin = this -> halo();
    _halo = halo;
    _modify = _modify || (origin != this -> halo());
    return;
}
/// @section: map alpha (map_d) /////////////////////////// |
const QString& Material::dissolveMap() const             // |
{
    return( _dissolveMap );
}
void Material::setDissolveMap( const QString& alphaMap ) // |
{
    QString origin = this -> dissolveMap();
    _dissolveMap = alphaMap;
    _modify = _modify || (origin != this -> dissolveMap());
    return;
}
/// @section: ambient map color (map_Ka) ///////////////////////////// |
const QString& Material::ambientMapColor() const                    // |
{
    return( _ambientMapColor );
}
void Material::setAmbientMapColor( const QString& ambientMapColor ) // |
{
    QString origin = this -> ambientMapColor();
    _ambientMapColor = ambientMapColor;
    _modify = _modify || (origin != this -> ambientMapColor());
    return;
}
/// @section: diffuse map color (map_Kd) ///////////////////////////// |
const QString& Material::diffuseMapColor() const                    // |
{
    return( _diffuseMapColor );
}
void Material::setDiffuseMapColor( const QString& diffuseMapColor ) // |
{
    QString origin = this -> diffuseMapColor();
    _diffuseMapColor = diffuseMapColor;
    _modify = _modify || (origin != this -> diffuseMapColor());
    return;
}
/// @section: specular map color (map_Ks) ////////////////////////////// |
const QString& Material::specularMapColor() const                     // |
{
    return( _specularMapColor );
}
void Material::setSpecularMapColor( const QString& specularMapColor ) // |
{
    QString origin = this -> specularMapColor();
    _specularMapColor = specularMapColor;
    _modify = _modify || (origin != this -> specularMapColor());
    return;
}
/// @section: normal map (bump) ////////////////////////// |
const QString& Material::normalMap() const              // |
{
    return( _normalMap );
}
void Material::setNormalMap( const QString& normalMap ) // |
{
    QString origin = this -> normalMap();
    _normalMap = normalMap;
    _modify = _modify || (origin != this->normalMap());
    return;
}

Material::~Material()
{
}


