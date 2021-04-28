#ifndef SHADOW_H
#define SHADOW_H

#include "render_item.h"

class Shadow : public RenderItem
        , ProgramMgr::Callback
{
public:
    static QString class_name() { return( QString("Shadow") ); }
    virtual QString xml_class_name() const
    {
        if( RenderItem::xml_class_name().isEmpty() )
            return( class_name() );
        return( RenderItem::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( RenderItem::isModify() || _modify ); }

public:
    class Quality : public EnumValue
    {
    public:
        enum id{ poor
                 , low
                 , fine
                 , finest

                 , _first = poor
                 , _last  = finest
               };
        static int count() { return( last() - first() + 1 ); }
        static int first() { return( _first ); }
        static int last()  { return( _last ); }
        static QString to_string( int v )
        {
            return( to_string(id(v)) );
        }
        static QString to_string( id v )
        {
            switch( v )
            {
            case poor   : return( QString("poor") );
            case low    : return( QString("low") );
            case fine   : return( QString("fine") );
            case finest : return( QString("finest") );
            default:
                break;
            }
            throw( Exception(Error::unknown_enum_id, "for Shadow::Quality") );
        }

    public:
        Quality()
            : EnumValue()
            , _id( low )
        {}
        explicit Quality( const QString& v )
            : EnumValue( v )
        {
            for( int index = first(); index <= last(); ++index )
            {
                if( to_string(index) == v )
                {
                    _id = id(index);
                    return;
                }
            }
            throw( Exception(Error::unknown_enum_id, "for Shadow::Quality") );
        }
        explicit Quality( id v )
            : EnumValue()
            , _id( v )
        {
        }
        virtual ~Quality()
        {}

    private:
        id _id;

    public:
        virtual QString to_string() const
        {
            return( to_string(_id) );
        }
        virtual int to_int() const
        {
            switch( _id )
            {
            case poor   : return( 512  );
            case low    : return( 1024 );
            case fine   : return( 2048 );
            case finest : return( 4096 );
            default:
                break;
            }
            return( 0 );
        }
    };

public:
    explicit Shadow( const QString& = QString() );
    explicit Shadow( const QString&, Quality::id );
    virtual ~Shadow();

public:
    Shadow( const Shadow& cpy )
        : RenderItem( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify  = cpy._modify;
        _program = cpy._program;
        _active  = cpy._active;
        release( _gl_func );
        _depthFBO = cpy._depthFBO;
        _depthMap = cpy._depthMap;
        _gl_func = cpy._gl_func;
        _quality = cpy._quality;
    }
    Shadow& operator = ( const Shadow& cpy )
    {
        if( this != &cpy )
        {
            RenderItem::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify  = cpy._modify;
            _program = cpy._program;
            _active  = cpy._active;
            release( _gl_func );
            _depthFBO = cpy._depthFBO;
            _depthMap = cpy._depthMap;
            _gl_func = cpy._gl_func;
            _quality = cpy._quality;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        RenderItem::bind_fields();
        bind_field( "program", &_program );
        bind_field( "active", &_active );
        bind_field( "quality", &_quality );
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
        return( new Shadow() );
    }
    virtual XMLObject* clone() const
    {
        Shadow* object = new Shadow();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: program
    QString _program;

public:
    const QString& program() const;
    void setProgram(const QString& program);

private: /// @section: activate status
    bool _active;

public:
    bool active() const;
    void setActive( bool active );

public: /// @section: callback
    class Callback
    {
    public:
        Callback(){}

        virtual void event_DrawShadow( QGLFunctions* ) const = 0;
    };

public: /// @section: program callback
    virtual void event_ProgramActivated( ProgramShader*, QGLFunctions* ) const;
    virtual void event_ProgramDeactivated( ProgramShader*, QGLFunctions* ) const;
    virtual QString event_DefaultProgram() const;

public: /// @section: drawable
    virtual void draw( QGLFunctions*, const Callback* ) const;

public: /// @section: initialize
    virtual void initialize( QGLFunctions* );

protected: /// @section: bind data
    virtual void bind_projectionMtx( ProgramShader*, QGLFunctions* ) const {}
    virtual void bind_viewMtx( ProgramShader*, QGLFunctions* ) const {}
public:
    virtual void bind( size_t, ProgramShader*, QGLFunctions* ) const {}

private: /// @section: frame buffer
    GLuint _depthFBO;
    GLuint _depthMap;
    QGLFunctions* _gl_func;

    void createDepthFBO( QGLFunctions* );
    void bindDepthFBO( QGLFunctions* ) const;
    void unbindDepthFBO( QGLFunctions* ) const;

public:
    GLuint depthMap() const { return( _depthMap ); }
    void release( QGLFunctions* functions )
    {
        if( 0 != functions && 0 != _depthFBO )
        {
            functions -> glFramebufferTexture2D( GL_FRAMEBUFFER
                                                 , GL_COLOR_ATTACHMENT0
                                                 , GL_TEXTURE_2D, 0, 0 );
            functions -> glDeleteFramebuffers( 1, &_depthFBO );
        }
        _depthFBO = 0;
        if( 0 != _depthMap )
            glDeleteTextures( 1, &_depthMap );
        _depthMap = 0;
        return;
    }

private: /// @section: shadow map quality
    EnumAs< Quality > _quality;

public:
    const EnumAs< Quality >& quality() const { return( _quality ); }
};
class ShadowDirection: public Shadow
{
public:
    static QString class_name() { return( QString("sDirection") ); }
    virtual QString xml_class_name() const
    {
        if( Shadow::xml_class_name().isEmpty() )
            return( class_name() );
        return( Shadow::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( Shadow::isModify() || _modify ); }

public:
    explicit ShadowDirection( const QString& = QString() );
    explicit ShadowDirection( const QString&, Quality::id );
    virtual ~ShadowDirection();

public:
    ShadowDirection( const ShadowDirection& cpy )
        : Shadow( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
    }
    ShadowDirection& operator = ( const ShadowDirection& cpy )
    {
        if( this != &cpy )
        {
            Shadow::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Shadow::bind_fields();
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
        return( new ShadowDirection() );
    }
    virtual XMLObject* clone() const
    {
        ShadowDirection* object = new ShadowDirection();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

private: /// @section: projection matrix
    QMatrix4x4 _projection;

public:
    const QMatrix4x4& projection() const { return( _projection ); }

private: /// @section: view matrix
    QMatrix4x4 _view;

    void create_view()
    {
//        Vector3 position = (_direction * -1.0f).normalized()*distance() + target();
//        _view.setToIdentity();
//        _view.lookAt( position.vec(), target().vec(), QVector3D(0.0f, 1.0f, 0.0f) );
        _view.setToIdentity();
        _view.lookAt( target().vec(), target().vec() + _direction.vec(), QVector3D(0.0f, 1.0f, 0.0f) );
        return;
    }

public:
    const QMatrix4x4& view() const { return( _view ); }

protected: /// @section: bind data
    virtual void bind_projectionMtx( ProgramShader*, QGLFunctions* ) const;
    virtual void bind_viewMtx( ProgramShader*, QGLFunctions* ) const;
public:
    virtual void bind( size_t, ProgramShader*, QGLFunctions* ) const;

private: /// @section: direction
    Vector3 _direction;

public:
    const Vector3& direction() const;
    void setDirection( const Vector3& direction );

private: /// @section: target
    Vector3 _target;

public:
    const Vector3& target() const;
    void setTarget( const Vector3& target );

private: /// @section: distance
    float _distance;

public:
    float distance() const;
    void setDistance( float distance );
};

#endif // SHADOW_H
