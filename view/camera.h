#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QGLShaderProgram>

#include "../parser/xml_meta_data.h"
#include "render_item.h"
#include "transform.h"
#include "resolution.h"
#include "shaders/package.h"

class Camera      : public RenderItem
{
public:
    static QString class_name() { return( QString("Camera") ); }
    virtual QString xml_class_name() const
    {
        if( RenderItem::xml_class_name().isEmpty() )
            return( class_name() );
        return( RenderItem::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( RenderItem::isModify() || _modify ); }

public:
    Camera();
    virtual ~Camera();

public:
    Camera( const Camera& cpy )
        : RenderItem( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        create_projectionMtx();
        create_viewMtx();
    }
    Camera& operator = ( const Camera& cpy )
    {
        if( this != &cpy )
        {
            RenderItem::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            create_projectionMtx();
            create_viewMtx();
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        RenderItem::bind_fields();
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
            create_projectionMtx();
            _modify = false;
        }
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Camera() );
    }
    virtual XMLObject* clone() const
    {
        Camera* object = new Camera();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

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

protected: /// @section: projection matrix
    QMatrix4x4 mtx_projection;
    virtual void create_projectionMtx()
    {
    }

public:
    const QMatrix4x4& projection_matrix() const { return( mtx_projection ); }

protected: /// @section: view matrix
    QMatrix4x4 mtx_view;

    virtual void create_viewMtx()
    {
    }

public:
    const QMatrix4x4& view_matrix() const { return( mtx_view ); }
    virtual QVector3D getPosition() const { return( QVector3D() ); }

public: /// @section: bind
    bool bind( ProgramShader*, QGLFunctions* ) const;

protected: /// @section: resolution
    Resolution _resolution;

public:
    const Resolution& resolution() const { return( _resolution ); }
    void resize( int w, int h )
    {
        _resolution = Resolution( static_cast<unsigned int>(w)
                                  , static_cast<unsigned int>(h) );
        create_projectionMtx();
        return;
    }
};
class Ortho       : public Camera
{
public:
    static QString class_name() { return( QString("Ortho") ); }
    virtual QString xml_class_name() const
    {
        if( Camera::xml_class_name().isEmpty() )
            return( class_name() );
        return( Camera::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( _modify || transform().isModify() ); }

public:
    explicit Ortho( const Resolution& = Resolution()
            , float = 0.0f, float = 0.0f
            , float = 0.0f, float = 0.0f
            , float = 0.0f, float = 0.0f );
    virtual ~Ortho();

public:
    Ortho( const Ortho& cpy )
        : Camera( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _left   = cpy._left;
        _right  = cpy._right;
        _top    = cpy._top;
        _bottom = cpy._bottom;
        _Znear  = cpy._Znear;
        _Zfar   = cpy._Zfar;
        _transform = cpy._transform;
        create_projectionMtx();
        create_viewMtx();
    }
    Ortho& operator = ( const Ortho& cpy )
    {
        if( this != &cpy )
        {
            Camera::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _left   = cpy._left;
            _right  = cpy._right;
            _top    = cpy._top;
            _bottom = cpy._bottom;
            _Znear  = cpy._Znear;
            _Zfar   = cpy._Zfar;
            _transform = cpy._transform;
            create_projectionMtx();
            create_viewMtx();
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Camera::bind_fields();
        bind_field( "base_resolution", &_base_resolution );
        bind_field( "left",      &_left   );
        bind_field( "right",     &_right  );
        bind_field( "top",       &_top    );
        bind_field( "bottom",    &_bottom );
        bind_field( "Znear",     &_Znear  );
        bind_field( "Zfar",      &_Zfar   );
        bind_field( "transform", &_transform );
        return;
    }

protected:
    virtual void event_Saved()
    {
        Camera::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        Camera::event_Loaded( success );
        if( success )
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Ortho() );
    }
    virtual XMLObject* clone() const
    {
        Ortho* object = new Ortho();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected:
    virtual void create_projectionMtx();

private: /// @section: resolution
    Resolution _base_resolution;

public:
    const Resolution& base_resolution() const { return( _base_resolution ); }
    void setBaseResolution( const Resolution& r )
    {
        Resolution origin = base_resolution();
        _base_resolution = r;
        _modify = _modify || (origin != base_resolution());
        return;
    }

private: /// @section: ortho params
    float _left;
    float _right;
    float _top;
    float _bottom;
    float _Znear;
    float _Zfar;

public:
    float left() const { return( _left ); }
    float right() const { return( _right ); }
    float top() const { return( _top ); }
    float bottom() const { return( _bottom ); }
    float Znear() const { return( _Znear ); }
    float Zfar() const { return( _Zfar ); }

private: /// @section: view matrix
    Transform _transform;

protected:
    virtual void create_viewMtx();

public:
    virtual QVector3D getPosition() const { return( transform().position().vec() ); }
    const Transform& transform() const { return( _transform ); }
    void transform_Modify( const Transform& t )
    {
        Transform origin = transform();
        _transform = t;
        bool transform_modify = (origin != transform());
        if( transform_modify )
            create_viewMtx();
        _modify = _modify || transform_modify;
        return;
    }
    void transform_Modify( const Position& p )
    {
        Position origin = transform().position();
        _transform.setPosition( p );
        if( origin != transform().position() )
            create_viewMtx();
        return;
    }
    void transform_Modify( const Rotate& r )
    {
        Rotate origin = transform().rotate();
        _transform.setRotate( r );
        if( origin != transform().rotate() )
            create_viewMtx();
        return;
    }
    void transform_Modify( const Scale& s )
    {
        Scale origin = transform().scale();
        _transform.setScale( s );
        if( origin != transform().scale() )
            create_viewMtx();
        return;
    }

};
class Perspective : public Camera
{
public:
    static QString class_name() { return( QString("Perspective") ); }
    virtual QString xml_class_name() const
    {
        if( Camera::xml_class_name().isEmpty() )
            return( class_name() );
        return( Camera::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( _modify || transform().isModify() ); }

public:
    explicit Perspective( const Resolution& = Resolution()
            , const Angle& = Angle(60.0f, Angle::degrees_unit)
            , float = 0.10f, float = 1000.0f );
    virtual ~Perspective();

public:
    Perspective( const Perspective& cpy )
        : Camera( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _base_resolution = cpy._base_resolution;
        _angle = cpy._angle;
        _Znear = cpy._Znear;
        _Zfar  = cpy._Zfar;
        _transform = cpy._transform;
        create_projectionMtx();
        create_viewMtx();
    }
    Perspective& operator = ( const Perspective& cpy )
    {
        if( this != &cpy )
        {
            Camera::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _base_resolution = cpy._base_resolution;
            _angle = cpy._angle;
            _Znear = cpy._Znear;
            _Zfar  = cpy._Zfar;
            _transform = cpy._transform;
            create_projectionMtx();
            create_viewMtx();
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Camera::bind_fields();
        bind_field( "base_resolution", &_base_resolution );
        bind_field( "angle", &_angle );
        bind_field( "Znear", &_Znear );
        bind_field( "Zfar", &_Zfar );
        bind_field( "transform", &_transform );
        return;
    }

protected:
    virtual void event_Saved()
    {
        Camera::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        Camera::event_Loaded( success );
        if( success )
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Perspective() );
    }
    virtual XMLObject* clone() const
    {
        Perspective* object = new Perspective();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected:
    virtual void create_projectionMtx();

private: /// @section: resolution
    Resolution _base_resolution;

public:
    const Resolution& base_resolution() const { return( _base_resolution ); }
    void setBaseResolution( const Resolution& r )
    {
        Resolution origin = base_resolution();
        _base_resolution = r;
        _modify = _modify || (origin != base_resolution());
        return;
    }

private: /// @section: vertical angle
    Angle _angle;

public:
    const Angle& angle() const { return( _angle ); }
    void setAngle( const Angle& angle )
    {
        Angle origin = this -> angle();
        _angle = angle;
        _modify = _modify || (origin != this -> angle());
        return;
    }

private: /// @section: Z(near\far)
    float _Znear;
    float _Zfar;

public:
    float Znear() const { return( _Znear ); }
    float Zfar() const { return( _Zfar ); }

private: /// @section: view matrix
    Transform _transform;

protected:
    virtual void create_viewMtx();

public:
    virtual QVector3D getPosition() const { return( transform().position().vec() ); }
    const Transform& transform() const { return( _transform ); }
    void transform_Modify( const Transform& t )
    {
        Transform origin = transform();
        _transform = t;
        bool transform_modify = (origin != transform());
        if( transform_modify )
            create_viewMtx();
        _modify = _modify || transform_modify;
        return;
    }
    void transform_Modify( const Position& p )
    {
        Position origin = transform().position();
        _transform.setPosition( p );
        if( origin != transform().position() )
            create_viewMtx();
        return;
    }
    void transform_Modify( const Rotate& r )
    {
        Rotate origin = transform().rotate();
        _transform.setRotate( r );
        if( origin != transform().rotate() )
            create_viewMtx();
        return;
    }
    void transform_Modify( const Scale& s )
    {
        Scale origin = transform().scale();
        _transform.setScale( s );
        if( origin != transform().scale() )
            create_viewMtx();
        return;
    }
};
class Eye         : public Camera
{
public:
    static QString class_name() { return( QString("Eye") ); }
    virtual QString xml_class_name() const
    {
        if( Camera::xml_class_name().isEmpty() )
            return( class_name() );
        return( Camera::xml_class_name().append(".").append(class_name()) );
    }
    virtual bool isModify() const { return( _modify ); }

public:
    explicit Eye( const Resolution& = Resolution()
            , const Angle& = Angle(60.0f, Angle::degrees_unit)
            , float = 0.10f, float = 1000.0f );
    virtual ~Eye();

public:
    Eye( const Eye& cpy )
        : Camera( cpy )
    {
        unbind_fields();
        bind_fields();
        _modify = cpy._modify;
        _base_resolution = cpy._base_resolution;
        _angle = cpy._angle;
        _Znear = cpy._Znear;
        _Zfar  = cpy._Zfar;
        _position = cpy._position;
        _target = cpy._target;
        _up = cpy._up;
        create_projectionMtx();
        create_viewMtx();
    }
    Eye& operator = ( const Eye& cpy )
    {
        if( this != &cpy )
        {
            Camera::operator = ( cpy );
            unbind_fields();
            bind_fields();
            _modify = cpy._modify;
            _base_resolution = cpy._base_resolution;
            _angle = cpy._angle;
            _Znear = cpy._Znear;
            _Zfar  = cpy._Zfar;
            _position = cpy._position;
            _target = cpy._target;
            _up = cpy._up;
            create_projectionMtx();
            create_viewMtx();
        }
        return( *this );
    }

protected:
    virtual void bind_fields()
    {
        Camera::bind_fields();
        bind_field( "base_resolution", &_base_resolution );
        bind_field( "angle", &_angle );
        bind_field( "Znear", &_Znear );
        bind_field( "Zfar", &_Zfar );
        bind_field( "position", &_position );
        bind_field( "target", &_target );
        bind_field( "up", &_up );
        return;
    }

protected:
    virtual void event_Saved()
    {
        Camera::event_Saved();
        _modify = false;
        return;
    }
    virtual void event_Loaded( bool success )
    {
        Camera::event_Loaded( success );
        if( success )
            _modify = false;
        return;
    }

public:
    virtual XMLObject* create() const
    {
        return( new Eye() );
    }
    virtual XMLObject* clone() const
    {
        Eye* object = new Eye();
        (*object) = (*this);
        return( object );
    }

private:
    bool _modify;

protected:
    virtual void create_projectionMtx();

private: /// @section: resolution
    Resolution _base_resolution;

public:
    const Resolution& base_resolution() const { return( _base_resolution ); }
    void setBaseResolution( const Resolution& r )
    {
        Resolution origin = base_resolution();
        _base_resolution = r;
        _modify = _modify || (origin != base_resolution());
        return;
    }

private: /// @section: vertical angle
    Angle _angle;

public:
    const Angle& angle() const { return( _angle ); }
    void setAngle( const Angle& angle )
    {
        Angle origin = this -> angle();
        _angle = angle;
        _modify = _modify || (origin != this -> angle());
        return;
    }

private: /// @section: Z(near\far)
    float _Znear;
    float _Zfar;

public:
    float Znear() const { return( _Znear ); }
    float Zfar() const { return( _Zfar ); }

private: /// @section: view matrix
    Vector3 _position;
    Vector3 _target;
    Vector3 _up;

protected:
    virtual void create_viewMtx();

public:
    const Vector3& position() const { return( _position ); }
    const Vector3& target() const { return( _target ); }
    const Vector3& up() const { return( _up ); }
    Vector3 direction() const
    {
        Vector3 result = target() - position();
        result.normalize();
        return( result );
    }
    Vector3 right() const
    {
        return( Vector3::cross(direction(), up()) );
    }
    void setPosition( const Vector3& v )
    {
        Vector3 origin = position();
        _position = v;
        bool vector_modify = (origin != position());
        if( vector_modify )
            create_viewMtx();
        _modify = _modify || vector_modify;
        return;
    }
    void setTarget( const Vector3& v )
    {
        Vector3 origin = target();
        _target = v;
        bool vector_modify = (origin != target());
        if( vector_modify )
            create_viewMtx();
        _modify = _modify || vector_modify;
        return;
    }
    void setUp( const Vector3& v )
    {
        Vector3 origin = up();
        _target = v;
        bool vector_modify = (origin != up());
        if( vector_modify )
            create_viewMtx();
        _modify = _modify || vector_modify;
        return;
    }

    virtual QVector3D getPosition() const { return( position().vec() ); }

public: /// @section: control
    void translate( const Vector3& v );
    void rotate( const Angle& angleH, const Angle& angleV );
};

#endif // CAMERA_H
