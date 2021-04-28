#ifndef PROGRAM_SHADOW_H
#define PROGRAM_SHADOW_H

#include <QGLFunctions>
#include "../../parser/xml_meta_data.h"
#include "program_shader.h"
#include "../vector3.h"
#include "../angle.h"

class ProgramShadowData : public XMLObject
{
public:
    static QString class_name() { return( QString("ShadowData") ); }
    virtual QString xml_class_name() const
    {
        return( class_name() );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    ProgramShadowData();
    virtual ~ProgramShadowData();

public:
    ProgramShadowData( const ProgramShadowData& cpy )
        : XMLObject( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _enable = cpy._enable;
        _projectionMtx = cpy._projectionMtx;
        _viewMtx = cpy._viewMtx;
    }
    ProgramShadowData& operator = ( const ProgramShadowData& cpy )
    {
        if( this != &cpy )
        {
            XMLObject::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _enable = cpy._enable;
            _projectionMtx = cpy._projectionMtx;
            _viewMtx = cpy._viewMtx;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        XMLObject::bind_fields();
        bind_field( "enable", &_enable );
        bind_field( "projectionMtx", &_projectionMtx );
        bind_field( "viewMtx", &_viewMtx );
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
        return( new ProgramShadowData() );
    }
    virtual XMLObject* clone() const
    {
        ProgramShadowData* object = new ProgramShadowData();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: uniform... enable
    QString _enable;

public:
    const QString& enable() const;
    void setEnable( const QString& enable );

private: /// @section: uniform... projectionMtx
    QString _projectionMtx;

public:
    const QString& projectionMtx() const;
    void setProjectionMtx( const QString& projectionMtx );

private: /// @section: uniform... viewMtx
    QString _viewMtx;

public:
    const QString& viewMtx() const;
    void setViewMtx( const QString& viewMtx );

private: /// @section: initialize
    QString locName( size_t, const QString& ) const;

public:
    void initEnable       ( size_t, QGLFunctions*, ProgramShader*, bool ) const;
    void initProjectionMtx( size_t, QGLFunctions*, ProgramShader*, const QMatrix4x4& ) const;
    void initViewMtx      ( size_t, QGLFunctions*, ProgramShader*, const QMatrix4x4& ) const;
};

#endif // PROGRAM_SHADOW_H
