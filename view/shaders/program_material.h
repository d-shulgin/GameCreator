#ifndef PROGRAM_MATERIAL_H
#define PROGRAM_MATERIAL_H

#include <QGLFunctions>
#include "../../parser/xml_meta_data.h"
#include "program_shader.h"
#include "../vector3.h"

class ProgramMaterial : public XMLObject
{
public:
    static QString class_name() { return( QString("pMaterial") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    ProgramMaterial();
    virtual ~ProgramMaterial();

public:
    ProgramMaterial( const ProgramMaterial& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _ambientColor   = cpy._ambientColor;
        _ambientMap     = cpy._ambientMap;
        _useAmbientMap  = cpy._useAmbientMap;
        _diffuseColor   = cpy._diffuseColor;
        _diffuseMap     = cpy._diffuseMap;
        _useDiffuseMap  = cpy._useDiffuseMap;
        _specularColor  = cpy._specularColor;
        _specularExp    = cpy._specularExp;
        _specularMap    = cpy._specularMap;
        _useSpecularMap = cpy._useSpecularMap;
        _dissolve       = cpy._dissolve;
        _halo           = cpy._halo;
        _dissolveMap    = cpy._dissolveMap;
        _useDissolveMap = cpy._useDissolveMap;
        _normalMap      = cpy._normalMap;
        _useNormalMap   = cpy._useNormalMap;
    }
    ProgramMaterial& operator = ( const ProgramMaterial& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _ambientColor   = cpy._ambientColor;
            _ambientMap     = cpy._ambientMap;
            _useAmbientMap  = cpy._useAmbientMap;
            _diffuseColor   = cpy._diffuseColor;
            _diffuseMap     = cpy._diffuseMap;
            _useDiffuseMap  = cpy._useDiffuseMap;
            _specularColor  = cpy._specularColor;
            _specularExp    = cpy._specularExp;
            _specularMap    = cpy._specularMap;
            _useSpecularMap = cpy._useSpecularMap;
            _dissolve       = cpy._dissolve;
            _halo           = cpy._halo;
            _dissolveMap    = cpy._dissolveMap;
            _useDissolveMap = cpy._useDissolveMap;
            _normalMap      = cpy._normalMap;
            _useNormalMap   = cpy._useNormalMap;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "ambientColor",   &_ambientColor   );
        bind_field( "ambientMap",     &_ambientMap     );
        bind_field( "useAmbientMap",  &_useAmbientMap  );
        bind_field( "diffuseColor",   &_diffuseColor   );
        bind_field( "diffuseMap",     &_diffuseMap     );
        bind_field( "useDiffuseMap",  &_useDiffuseMap  );
        bind_field( "specularColor",  &_specularColor  );
        bind_field( "specularExp",    &_specularExp    );
        bind_field( "specularMap",    &_specularMap    );
        bind_field( "useSpecularMap", &_useSpecularMap );
        bind_field( "dissolve",       &_dissolve       );
        bind_field( "halo",           &_halo           );
        bind_field( "dissolveMap",    &_dissolveMap    );
        bind_field( "useDissolveMap", &_useDissolveMap );
        bind_field( "normalMap",      &_normalMap      );
        bind_field( "useNormalMap",   &_useNormalMap   );
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
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new ProgramMaterial() );
    }
    virtual XMLObject* clone() const
    {
        ProgramMaterial* object = new ProgramMaterial();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: uniform... material.ambientColor
    QString _ambientColor;

public:
    const QString& ambientColor() const;
    void setAmbientColor( const QString& ambientColor );

private: /// @section: uniform... material.ambientMap
    QString _ambientMap;
    QString _useAmbientMap;

public:
    const QString& ambientMap() const;
    void setAmbientMap( const QString& ambientMap );
    const QString& useAmbientMap() const;
    void setUseAmbientMap( const QString& useAmbientMap );

private: /// @section: uniform... material.diffuseColor
    QString _diffuseColor;

public:
    const QString& diffuseColor() const;
    void setDiffuseColor( const QString& diffuseColor );

private: /// @section: uniform... material.diffuseMap
    QString _diffuseMap;
    QString _useDiffuseMap;

public:
    const QString& diffuseMap() const;
    void setDiffuseMap( const QString& diffuseMap );
    const QString& useDiffuseMap() const;
    void setUseDiffuseMap( const QString& useDiffuseMap );

private: /// @section: uniform... material.specularColor
    QString _specularColor;

public:
    const QString& specularColor() const;
    void setSpecularColor( const QString& specularColor );

private: /// @section: uniform... material.specExp
    QString _specularExp;

public:
    const QString& specularExp() const;
    void setSpecularExp( const QString& specularExp );

private: /// @section: uniform... material.specularMap
    QString _specularMap;
    QString _useSpecularMap;

public:
    const QString& specularMap() const;
    void setSpecularMap( const QString& specularMap );
    const QString& useSpecularMap() const;
    void setUseSpecularMap( const QString& useSpecularMap );

private: /// @section: uniform... material.dissolve
    QString _dissolve;

public:
    const QString& dissolve() const;
    void setDissolve( const QString& dissolve );

private: /// @section: uniform... material.halo
    QString _halo;

public:
    const QString& halo() const;
    void setHalo( const QString& halo );

private: /// @section: uniform... material.dissolveMap
    QString _dissolveMap;
    QString _useDissolveMap;

public:
    const QString& dissolveMap() const;
    void setDissolveMap( const QString& dissolveMap );
    const QString& useDissolveMap() const;
    void setUseDissolveMap( const QString& useDissolveMap );

private: /// @section: uniform... material.normalMap
    QString _normalMap;
    QString _useNormalMap;

public:
    const QString& normalMap() const;
    void setNormalMap( const QString& normalMap );
    const QString& useNormalMap() const;
    void setUseNormalMap( const QString& useNormalMap );

public: /// @section: initialize
    void initAmbientColor ( QGLFunctions*, ProgramShader*, const Vector3& ) const;
    void initAmbientMap   ( QGLFunctions*, ProgramShader*, int ) const;
    void initDiffuseColor ( QGLFunctions*, ProgramShader*, const Vector3& ) const;
    void initDiffuseMap   ( QGLFunctions*, ProgramShader*, int ) const;
    void initSpecularColor( QGLFunctions*, ProgramShader*, const Vector3& ) const;
    void initSpecularExp  ( QGLFunctions*, ProgramShader*, float ) const;
    void initSpecularMap  ( QGLFunctions*, ProgramShader*, int ) const;
    void initDissolve     ( QGLFunctions*, ProgramShader*, float ) const;
    void initHalo         ( QGLFunctions*, ProgramShader*, bool ) const;
    void initDissolveMap  ( QGLFunctions*, ProgramShader*, int ) const;
    void initNormalMap    ( QGLFunctions*, ProgramShader*, int ) const;
};

#endif // PROGRAM_MATERIAL_H
