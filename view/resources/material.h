#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../parser/xml_meta_data.h"
#include "../vector3.h"

class Material : public XMLObject
{
public:
    static QString class_name() { return( QString("Material") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    explicit Material( const QString& = QString() );
    virtual ~Material();

public:
    Material( const Material& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _name = cpy._name;
        _ambientColor  = cpy._ambientColor;
        _diffuseColor  = cpy._diffuseColor;
        _specularColor = cpy._specularColor;
        _specularExponent = cpy._specularExponent;
        _dissolve = cpy._dissolve;
        _halo = cpy._halo;
        _dissolveMap = cpy._dissolveMap;
        _ambientMapColor = cpy._ambientMapColor;
        _diffuseMapColor = cpy._diffuseMapColor;
        _specularMapColor = cpy._specularMapColor;
        _normalMap = cpy._normalMap;
    }
    Material& operator = ( const Material& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _name = cpy._name;
            _ambientColor  = cpy._ambientColor;
            _diffuseColor  = cpy._diffuseColor;
            _specularColor = cpy._specularColor;
            _specularExponent = cpy._specularExponent;
            _dissolve = cpy._dissolve;
            _halo = cpy._halo;
            _dissolveMap = cpy._dissolveMap;
            _ambientMapColor = cpy._ambientMapColor;
            _diffuseMapColor = cpy._diffuseMapColor;
            _specularMapColor = cpy._specularMapColor;
            _normalMap = cpy._normalMap;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "name", &_name );
        bind_field( "ambientColor", &_ambientColor );
        bind_field( "diffuseColor", &_diffuseColor );
        bind_field( "specularColor", &_specularColor );
        bind_field( "specularExponent", &_specularExponent );
        bind_field( "dissolve", &_dissolve );
        bind_field( "dissolveMap", &_dissolveMap );
        bind_field( "ambientMapColor", &_ambientMapColor );
        bind_field( "diffuseMapColor", &_diffuseMapColor );
        bind_field( "specularMapColor", &_specularMapColor );
        bind_field( "normalMap", &_normalMap );
        return;
    }

protected:
    virtual void event_Saved()
    {
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        if( success )
        {
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Material() );
    }
    virtual XMLObject* clone() const
    {
        Material* object = new Material();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: namae
    QString _name;

public:
    const QString& name() const;
    void setName(const QString& name);

private: /// @section: ambient color (Ka)
    Vector3 _ambientColor;

public:
    const Vector3& ambientColor() const;
    void setAmbientColor( const Vector3& ambientColor );

private: /// @section: diffuse color (Kd)
    Vector3 _diffuseColor;

public:
    const Vector3& diffuseColor() const;
    void setDiffuseColor( const Vector3& diffuseColor );

private: /// @section: specular color (Ks)
    Vector3 _specularColor;

public:
    const Vector3& specularColor() const;
    void setSpecularColor( const Vector3& specularColor );

private: /// @section: specular exponent (Ns)
    float _specularExponent;

public:
    float specularExponent() const;
    void setSpecularExponent(float specularExponent);

private: /// @section: dissolve (d factor)
    float _dissolve;

public:
    float dissolve() const;
    void setDissolve(float dissolve);

private: /// @section: halo dissolve (d -halo factor)
    bool _halo;

public:
    bool halo() const;
    void setHalo(bool halo);

private: /// @section: map dissolve (map_d)
    QString _dissolveMap;

public:
    const QString& dissolveMap() const;
    void setDissolveMap(const QString& dissolveMap);

private: /// @section: ambient map color (map_Ka)
    QString _ambientMapColor;

public:
    const QString& ambientMapColor() const;
    void setAmbientMapColor(const QString& ambientMapColor);

private: /// @section: diffuse map color (map_Kd)
    QString _diffuseMapColor;

public:
    const QString& diffuseMapColor() const;
    void setDiffuseMapColor( const QString& diffuseMapColor );

private: /// @section: specular map color (map_Ks)
    QString _specularMapColor;

public:
    const QString& specularMapColor() const;
    void setSpecularMapColor(const QString& specularMapColor);

private: /// @section: normal map (bump)
    QString _normalMap;

public:
    const QString& normalMap() const;
    void setNormalMap( const QString& normalMap );
};

/// @todo: other mtl filters:
/// Tf... rgb
/// sharpness... val=0..1000
/// illum... val=0..10 (not supported)
///          0 - Color on and Ambient off
///          1 - Color on and Ambient on
///          2 - Highlight on
///          3 - Reflection on and Ray trace on
///          4 - Transparency: Glass on
///              Reflection: Ray trace on
///          5 - Reflection: Fresnel on and Ray trace on
///          6 - Transparency: Refraction on
///              Reflection: Fresnel off and Ray trace on
///          7 - Transparency: Refraction on
///              Reflection: Fresnel on and Ray trace on
///          8 - Reflection on and Ray trace off
///          9 - Transparency: Glass on
///              Reflection: Ray trace off
///         10 - Casts shadows onto invisible surfaces
/// Ni... optical_density (refract)
/// map_aat... on
/// decal... -options args filename
/// disp... -options args filename
/// refl... -type sphere -options -args filename

#endif // MATERIAL_H
