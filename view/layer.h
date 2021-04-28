#ifndef LAYER_H
#define LAYER_H

#include "../parser/xml_meta_data.h"
#include "drawable.h"
#include "resizeable.h"
#include "render_item.h"
#include "camera.h"
#include "light.h"
#include "widgets/package.h"
#include "shaders/package.h"

class Layer : public RenderItem
        , public Drawable
        , public Resizeable
        , public ProgramMgr::Callback
        , public Shadow::Callback
{
public:
    static QString class_name() { return( QString("Layer") ); }
    virtual QString xml_class_name() const
    {
        if( RenderItem::xml_class_name().isEmpty() )
            return( class_name() );
        return( RenderItem::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( RenderItem::isModify() || _modify
                                            || isAnyElementModify() ); }

public:
    Layer();
    virtual ~Layer();

public:
    Layer( const Layer& cpy )
        : RenderItem( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _programs = cpy._programs;
        _cameras = cpy._cameras;
        _current_camera_id = cpy._current_camera_id;
        _lights = cpy._lights;
        _views = cpy._views;
    }
    Layer& operator = ( const Layer& cpy )
    {
        if( this != &cpy )
        {
            RenderItem::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _programs = cpy._programs;
            _cameras = cpy._cameras;
            _current_camera_id = cpy._current_camera_id;
            _lights = cpy._lights;
            _views = cpy._views;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        RenderItem::bind_fields();
        bind_field( "programs", &_programs );
        bind_field( "cameras", &_cameras );
        bind_field( "lights", &_lights );
        bind_field( "views", &_views );
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
        return( new Layer() );
    }
    virtual XMLObject* clone() const
    {
        Layer* object = new Layer();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;
    bool isAnyElementModify() const
    {
        bool modify = false;
        for( size_t i = 0; i < cameras().count() && !modify; ++i )
            modify = cref_cameras().itemAt(i) -> isModify();
        for( size_t i = 0; i < views().count() && !modify; ++i )
            modify = cref_views().itemAt(i) -> isModify();
        for( size_t i = 0; i < lights().count() && !modify; ++i )
            modify = cref_lights().itemAt(i) -> isModify();
        return( modify );
    }

private: /// @section: program
    std::vector< QString > _programs;

    bool isSupported( const QString& namae ) const
    {
        if( !namae.isEmpty() )
        {
            for( size_t i = 0; i < _programs.size(); ++i )
                if( _programs[i] == namae )
                    return( true );
        }
        return( false );
    }
    QString default_program() const
    {
        if( _programs.empty() )
            return( QString() );
        return( _programs.front() );
    }
public:
    void addProgram( const QString& namae )
    {
        if( !namae.isEmpty() )
        {
            _programs.push_back( namae );
            _modify = true;
        }
        return;
    }

public: /// @section: program... global model matrix
    virtual void setGlobalMtx( const QMatrix4x4& );

private: /// @section: camera
    XMLCollection _cameras;
    size_t _current_camera_id;

protected:
    XMLCollection& ref_cameras() { return( _cameras ); }
    const XMLCollection& cref_cameras() const { return( _cameras ); }

public:
    const XMLCollectionU& cameras() const { return( _cameras ); }
    Camera* camera( size_t );
    const Camera* camera_const( size_t ) const;

public:
    Layer& addCamera( Camera* camera )
    {
        _cameras << static_cast<XMLObject*>( camera );
        _modify = true;
        return( *this );
    }

protected:
    void bind_camera( ProgramShader*, QGLFunctions* ) const;

private: /// @section: light
    enum { MAX_LIGHTS = 8 };
    XMLCollection _lights;

protected:
    XMLCollection& ref_lights() { return( _lights ); }
    const XMLCollection& cref_lights() const { return( _lights ); }

public:
    const XMLCollectionU& lights() const { return( _lights ); }
    Light* light( size_t );
    const Light* light_const( size_t ) const;

public:
    Layer& addLight( Light* light )
    {
        _lights << static_cast< XMLObject* >( light );
        _modify = true;
        return( *this );
    }

protected:
    void bind_lights( ProgramShader*, QGLFunctions* ) const;

private: /// @section: view
    XMLCollection _views;

protected:
    XMLCollection& ref_views() { return( _views ); }
    const XMLCollection& cref_views() const { return( _views ); }

public:
    const XMLCollectionU& views() const { return( _views ); }
    View* view( size_t );
    const View* view_const( size_t ) const;

public:
    Layer& addView( View* view )
    {
        _views << static_cast< XMLObject* >( view );
        _modify = true;
        return( *this );
    }
    View* getView( size_t );
    View* getView( const QString& );

public: /// @section: drawable interface
    virtual void draw( QGLFunctions* ) const;
    virtual void drawShadow( QGLFunctions* ) const;

public: /// @section: resizeable interface
    virtual void resize( int, int );

public: /// @section: initialize
    virtual void initialize( QGLFunctions* );

public: /// @section: program callback
    virtual void event_ProgramActivated( ProgramShader*, QGLFunctions* ) const;
    virtual void event_ProgramDeactivated( ProgramShader*, QGLFunctions* ) const;
    virtual QString event_DefaultProgram() const;

public: /// @section: shadow callback
    virtual void event_DrawShadow( QGLFunctions* ) const;
};

#endif // LAYER_H
