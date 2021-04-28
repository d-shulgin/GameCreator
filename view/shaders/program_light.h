#ifndef PROGRAM_LIGHT_H
#define PROGRAM_LIGHT_H

#include <QGLFunctions>
#include "../../parser/xml_meta_data.h"
#include "program_shader.h"
#include "../vector3.h"
#include "../angle.h"

class ProgramLight : public XMLObject
{
public:
    static QString class_name() { return( QString("pLight") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    ProgramLight();
    virtual ~ProgramLight();

public:
    ProgramLight( const ProgramLight& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _type         = cpy._type;
        _power        = cpy._power;
        _ambientColor = cpy._ambientColor;
        _diffuseColor = cpy._diffuseColor;
        _specularColor= cpy._specularColor;
        _position     = cpy._position;
        _direction    = cpy._direction;
        _angle        = cpy._angle;
        _borderArea   = cpy._borderArea;
        _shadowMap    = cpy._shadowMap;
        _useShadowMap = cpy._useShadowMap;
    }
    ProgramLight& operator = ( const ProgramLight& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _type         = cpy._type;
            _power        = cpy._power;
            _ambientColor = cpy._ambientColor;
            _diffuseColor = cpy._diffuseColor;
            _specularColor= cpy._specularColor;
            _position     = cpy._position;
            _direction    = cpy._direction;
            _angle        = cpy._angle;
            _borderArea   = cpy._borderArea;
            _shadowMap    = cpy._shadowMap;
            _useShadowMap = cpy._useShadowMap;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "type",          &_type          );
        bind_field( "power",         &_power         );
        bind_field( "ambientColor",  &_ambientColor  );
        bind_field( "diffuseColor",  &_diffuseColor  );
        bind_field( "specularColor", &_specularColor );
        bind_field( "position",      &_position      );
        bind_field( "direction",     &_direction     );
        bind_field( "angle",         &_angle         );
        bind_field( "borderArea",    &_borderArea    );
        bind_field( "shadowMap",     &_shadowMap     );
        bind_field( "useShadowMap",  &_useShadowMap  );
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
        return( new ProgramLight() );
    }
    virtual XMLObject* clone() const
    {
        ProgramLight* object = new ProgramLight();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: uniform... type
    QString _type;

public:
    const QString& type() const;
    void setType( const QString& type );

private: /// @section: uniform... power
    QString _power;

public:
    const QString& power() const;
    void setPower( const QString& power );

private: /// @section: uniform... ambient color
    QString _ambientColor;

public:
    const QString& ambientColor() const;
    void setAmbientColor( const QString& ambientColor );

private: /// @section: uniform... diffuse color
    QString _diffuseColor;

public:
    const QString& diffuseColor() const;
    void setDiffuseColor( const QString& diffuseColor );

private: /// @section: uniform... specular color
    QString _specularColor;

public:
    const QString& specularColor() const;
    void setSpecularColor( const QString& specularColor );

private: /// @section: uniform... position
    QString _position;

public:
    const QString& position() const;
    void setPosition( const QString& position );

private: /// @section: uniform... direction
    QString _direction;

public:
    const QString& direction() const;
    void setDirection( const QString& direction );

private: /// @section: uniform... angle
    QString _angle;

public:
    const QString& angle() const;
    void setAngle( const QString& angle );

private: /// @section: uniform... border area
    QString _borderArea;

public:
    const QString& borderArea() const;
    void setBorderArea( const QString& borderArea );

private: /// @section: uniform... shadowMap
    QString _shadowMap;
    QString _useShadowMap;

public:
    const QString& shadowMap() const;
    void setShadowMap( const QString& shadowMap );
    const QString& useShadowMap() const;
    void setUseShadowMap( const QString& useShadowMap );

private: /// @section: initialize
    QString locName( size_t, const QString& ) const;

public:
    void initType         ( size_t, QGLFunctions*, ProgramShader*, int ) const;
    void initPower        ( size_t, QGLFunctions*, ProgramShader*, float ) const;
    void initAmbientColor ( size_t, QGLFunctions*, ProgramShader*, const Vector3& ) const;
    void initDiffuseColor ( size_t, QGLFunctions*, ProgramShader*, const Vector3& ) const;
    void initSpecularColor( size_t, QGLFunctions*, ProgramShader*, const Vector3& ) const;
    void initPosition     ( size_t, QGLFunctions*, ProgramShader*, const Vector3& ) const;
    void initDirection    ( size_t, QGLFunctions*, ProgramShader*, const Vector3& ) const;
    void initAngle        ( size_t, QGLFunctions*, ProgramShader*, const Angle& ) const;
    void initBorderArea   ( size_t, QGLFunctions*, ProgramShader*, float ) const;
    void initShadowMap    ( size_t, QGLFunctions*, ProgramShader*, int ) const;
};

#endif // PROGRAM_LIGHT_H
