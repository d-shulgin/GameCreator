precision mediump int;
precision mediump float;

attribute vec4 a_position;
attribute vec2 a_texturePos;
attribute vec4 a_color;

uniform mat4 u_projectionMtx;
uniform mat4 u_viewMtx;
uniform mat4 u_modelMtx;

// mesh...
varying vec4 v_color;
varying vec2 v_texturePos;
varying vec4 v_position;

void main()
{
    mat4 viewMtx = u_viewMtx;
    viewMtx[3][0] = 0.0;
    viewMtx[3][1] = 0.0;
    viewMtx[3][2] = 0.0;
    mat4 mv_Mtx = viewMtx * u_modelMtx;
    gl_Position = u_projectionMtx * mv_Mtx * a_position;

    v_color       = a_color;
    v_texturePos  = a_texturePos;
    v_position    = mv_Mtx * a_position;
}
