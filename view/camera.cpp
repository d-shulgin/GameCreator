#include "camera.h"

Camera::Camera()
    : RenderItem()
    , _modify( false )
{
    mtx_projection.setToIdentity();
    mtx_view.setToIdentity();
    bind_fields();
}
/// @section: bind //////////////////////////////////// |
bool Camera::bind( ProgramShader* shader_program     // |
                   , QGLFunctions* functions ) const // |
{
    if( 0 != shader_program && shader_program -> is_linked() )
    {
        if( isSupported(shader_program -> name()) )
        {
            programsMgr().uniform().initProjectionMtx( functions
                                                       , shader_program
                                                       , projection_matrix() );
            programsMgr().uniform().initViewMtx( functions
                                                 , shader_program
                                                 , view_matrix() );
            programsMgr().uniform().initCameraPos( functions
                                                   , shader_program
                                                   , getPosition().toVector4D() );
            return( true );
        }
    }
    return( false );
}
Camera::~Camera()
{
}


Ortho::Ortho( const Resolution& resolution
              , float left
              , float top
              , float right
              , float bottom
              , float Znear
              , float Zfar )
    : Camera()
    , _modify( false )
    , _base_resolution( resolution )
    , _left( left )
    , _right( right )
    , _top( top )
    , _bottom( bottom )
    , _Znear( Znear )
    , _Zfar( Zfar )
{
    _resolution = _base_resolution;
    bind_fields();
    create_projectionMtx();
}
void Ortho::create_projectionMtx()
{
    mtx_projection.setToIdentity();
    if( base_resolution().equal_ratio(resolution()) )
    {
        mtx_projection.ortho( left(), right()
                              , bottom(), top()
                              , Znear(), Zfar() );
    }
    else
    {
        mtx_projection.ortho( left(), right()*base_resolution().width_ratio(resolution())
                              , bottom(), top()
                              , Znear(), Zfar() );
    }
    return;
}
void Ortho::create_viewMtx()
{
    mtx_view = transform().matrix();
    return;
}
Ortho::~Ortho()
{
}


Perspective::Perspective( const Resolution& resolution
                          , const Angle& angle_vertical
                          , float Znear, float Zfar )
    : Camera()
    , _modify( false )
    , _base_resolution( resolution )
    , _angle( angle_vertical )
    , _Znear( Znear )
    , _Zfar( Zfar )
{
    _resolution = _base_resolution;
    bind_fields();
    create_projectionMtx();
    create_viewMtx();
}
void Perspective::create_projectionMtx()
{
    mtx_projection.setToIdentity();
    mtx_projection.perspective( angle().as_degrees()
                                , resolution().aspect_ratio()
                                , Znear(), Zfar() );
    return;
}
void Perspective::create_viewMtx()
{
    mtx_view = transform().matrix();
    return;
}
Perspective::~Perspective()
{
}


Eye::Eye( const Resolution& resolution
          , const Angle& angle_vertical
          , float Znear, float Zfar )
    : Camera()
    , _modify( false )
    , _base_resolution( resolution )
    , _angle( angle_vertical )
    , _Znear( Znear )
    , _Zfar( Zfar )
    , _position( Vector3(0.0f, 0.0f, 0.0f) )
    , _target( Vector3(0.0f, 0.0f, -1.0f) )
    , _up( Vector3(0.0f, 1.0f, 0.0f) )
{
    _resolution = _base_resolution;
    bind_fields();
    create_projectionMtx();
    create_viewMtx();
}
void Eye::create_projectionMtx()
{
    mtx_projection.setToIdentity();
    mtx_projection.perspective( angle().as_degrees()
                                , resolution().aspect_ratio()
                                , Znear(), Zfar() );
}
void Eye::create_viewMtx()
{
    mtx_view.setToIdentity();
    mtx_view.lookAt( position().vec(), target().vec(), up().vec() );
}
void Eye::translate(const Vector3 &v)
{
    if( v.lenght() > 0 )
    {
        _position += v;
        _target += v;
        _modify = true;
        create_viewMtx();
    }
    return;
}
void Eye::rotate( const Angle &angleH, const Angle &angleV )
{
    Vector3 target = this->target() - position();
    QQuaternion qH = QQuaternion::fromAxisAndAngle( up().vec(), -angleH.as_degrees() );

    target = Vector3( qH.rotatedVector(target.vec()) );
    Vector3 right = Vector3::cross( target.normalized(), up() );
    right.normalize();

    QQuaternion qV = QQuaternion::fromAxisAndAngle( right.vec(), -angleV.as_degrees() );
    target = Vector3( qV.rotatedVector(target.vec()) );
    _target = position() + target;
    _modify = true;
    create_viewMtx();
    return;
}
Eye::~Eye()
{
}
