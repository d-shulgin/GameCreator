#ifndef PROGRAM_UNIFORM_H
#define PROGRAM_UNIFORM_H

#include "../../parser/xml_meta_data.h"
#include "program_material.h"
#include "program_light.h"
#include "program_shadow.h"

class ProgramUniform : public XMLObject
{
public:
    static QString class_name() { return( QString("Uniform") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    ProgramUniform();
    virtual ~ProgramUniform();

public:
    ProgramUniform( const ProgramUniform& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _projectionMtx   = cpy._projectionMtx;
        _viewMtx         = cpy._viewMtx;
        _modelMtx        = cpy._modelMtx;
        _cameraPos       = cpy._cameraPos;
        _textureUnit     = cpy._textureUnit;
        _lightsAmount    = cpy._lightsAmount;
        _light           = cpy._light;
        _material        = cpy._material;
        _shadow          = cpy._shadow;
        _shadowFiltering = cpy._shadowFiltering;
        _fontUnit        = cpy._fontUnit;
    }
    ProgramUniform& operator = ( const ProgramUniform& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _projectionMtx   = cpy._projectionMtx;
            _viewMtx         = cpy._viewMtx;
            _modelMtx        = cpy._modelMtx;
            _cameraPos       = cpy._cameraPos;
            _textureUnit     = cpy._textureUnit;
            _lightsAmount    = cpy._lightsAmount;
            _light           = cpy._light;
            _material        = cpy._material;
            _shadow          = cpy._shadow;
            _shadowFiltering = cpy._shadowFiltering;
            _fontUnit        = cpy._fontUnit;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "projectionMtx",   &_projectionMtx   );
        bind_field( "viewMtx",         &_viewMtx         );
        bind_field( "modelMtx",        &_modelMtx        );
        bind_field( "cameraPos",       &_cameraPos       );
        bind_field( "textureUnit",     &_textureUnit     );
        bind_field( "lightsAmount",    &_lightsAmount    );
        bind_field( "light",           &_light           );
        bind_field( "material",        &_material        );
        bind_field( "shadow",          &_shadow          );
        bind_field( "shadowFiltering", &_shadowFiltering );
        bind_field( "fontUnit",        &_fontUnit        );
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
        return( new ProgramUniform() );
    }
    virtual XMLObject* clone() const
    {
        ProgramUniform* object = new ProgramUniform();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: uniform... projection matrix
    QString _projectionMtx;

public:
    const QString& projectionMtx() const;
    void setProjectionMtx( const QString& projectionMtx );

private: /// @section: uniform... view matrix
    QString _viewMtx;

public:
    const QString& viewMtx() const;
    void setViewMtx( const QString& viewMtx );

private: /// @section: uniform... model matrix
    QString _modelMtx;

public:
    const QString& modelMtx() const;
    void setModelMtx( const QString& modelMtx );

private: /// @section: uniform... camera position
    QString _cameraPos;

public:
    const QString& cameraPos() const;
    void setCameraPos( const QString& cameraPos );

private: /// @section: uniform... texture
    QString _textureUnit;

public:
    const QString& textureUnit() const;
    void setTextureUnit( const QString& textureUnit );

private: /// @section: uniform... lights amount
    QString _lightsAmount;

public:
    const QString& lightsAmount() const;
    void setLightsAmount( const QString& lightsAmount );

private: /// @section: uniform... material data
    ProgramMaterial _material;

public:
    const ProgramMaterial& material() const { return( _material ); }
    ProgramMaterial& ref_material() { return( _material ); }

private: /// @section: uniform... light data
    ProgramLight _light;

public:
    const ProgramLight& light() const { return( _light ); }
    ProgramLight& ref_light() { return( _light ); }

private: /// @section: uniform... shadow data
    ProgramShadowData _shadow;

public:
    const ProgramShadowData& shadow() const { return( _shadow ); }
    ProgramShadowData& ref_shadow() { return( _shadow ); }

private: /// @section: uniform... shadow filtering
    QString _shadowFiltering;

public:
    const QString& shadowFiltering() const;
    void setShadowFiltering( const QString& shadowFiltering );

private: /// @section: uniform... font
    QString _fontUnit;
    QString _fontOffset;

public:
    const QString& fontUnit() const;
    const QString& fontOffset() const;
    void setFontUnit( const QString& fontUnit );
    void setFontOffset( const QString& fontOffset );

public: /// @section: initialize
    void initProjectionMtx   ( QGLFunctions*, ProgramShader*, const QMatrix4x4& ) const;
    void initViewMtx         ( QGLFunctions*, ProgramShader*, const QMatrix4x4& ) const;
    void initModelMtx        ( QGLFunctions*, ProgramShader*, const QMatrix4x4& ) const;
    void initCameraPos       ( QGLFunctions*, ProgramShader*, const QVector4D& ) const;
    void initTextureUnit     ( QGLFunctions*, ProgramShader*, int ) const;
    void initLightsAmount    ( QGLFunctions*, ProgramShader*, size_t ) const;
    void initShadowFiltering ( QGLFunctions*, ProgramShader*, int ) const;
    void initFontUnit        ( QGLFunctions*, ProgramShader*, int ) const;
    void initFontOffset      ( QGLFunctions*, ProgramShader*, const QVector2D& ) const;
};

#endif // PROGRAM_UNIFORM_H
