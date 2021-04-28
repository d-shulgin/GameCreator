precision mediump int;
precision mediump float;

attribute vec4 a_position;

attribute vec2 a_texturePos;
attribute vec3 a_normal;
attribute vec4 a_color;
attribute vec3 a_tangent;
attribute vec3 a_bitangent;

uniform mat4 u_projectionMtx;
uniform mat4 u_viewMtx;
uniform mat4 u_modelMtx;

varying vec4 v_position;
varying vec2 v_texturePos;

void main()
{
    v_texturePos  = a_texturePos;
    v_position = u_projectionMtx * u_viewMtx * u_modelMtx * a_position;
    gl_Position = v_position;
}
