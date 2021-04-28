precision mediump int;
precision mediump float;

attribute vec4 a_position;
attribute vec2 a_texturePos;
attribute vec3 a_normal;
attribute vec4 a_color;

uniform mat4 u_projectionMtx;
uniform mat4 u_viewMtx;
uniform mat4 u_modelMtx;

// mesh...
varying vec4 v_color;
varying vec2 v_texturePos;
varying vec3 v_normal;
varying vec4 v_position;
varying mat4 v_viewMtx;

void main()
{
    mat4 mv_Mtx = u_viewMtx * u_modelMtx;
    gl_Position = u_projectionMtx * mv_Mtx * a_position;

    v_color       = a_color;
    v_texturePos  = a_texturePos;
    v_normal      = normalize(mv_Mtx * vec4(a_normal, 0.0));
    v_position    = mv_Mtx * a_position;
    v_viewMtx     = u_viewMtx;
}
