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

struct ShadowData
{
    bool enable;
    mat4 projectionMtx;
    mat4 viewMtx;
};

uniform int u_lightAmount;
uniform ShadowData u_shadow[8];

// mesh...
varying vec4 v_color;
varying vec2 v_texturePos;
varying vec3 v_normal;
varying vec4 v_position;
varying mat4 v_viewMtx;
varying mat3 v_tbnMtx;
//varying int v_lightAmount;
varying vec4 v_positionLightSpace[8];

mat3 transpose( in mat3 inMtx )
{
    vec3 v0 = inMtx[0];
    vec3 v1 = inMtx[1];
    vec3 v2 = inMtx[2];

    mat3 result = mat3(
                vec3(v0.x, v1.x, v2.x),
                vec3(v0.y, v1.y, v2.y),
                vec3(v0.z, v1.z, v2.z));
    return result;
}

void main()
{
    mat4 mv_Mtx = u_viewMtx * u_modelMtx;
    gl_Position = u_projectionMtx * mv_Mtx * a_position;

    v_color       = a_color;
    v_texturePos  = a_texturePos;
    v_normal      = normalize(vec4(mv_Mtx * vec4(a_normal, 0.0)).xyz);
    v_position    = mv_Mtx * a_position;
    v_viewMtx     = u_viewMtx;

    vec3 tangent   = normalize(vec4(mv_Mtx * vec4(a_tangent, 0.0)).xyz);
    vec3 bitangent = normalize(vec4(mv_Mtx * vec4(a_bitangent, 0.0)).xyz);
    v_tbnMtx = transpose(mat3(tangent, bitangent, v_normal));

    //v_lightAmount = u_lightAmount*1;
    for( int i = 0; i < u_lightAmount; ++i )
    {
        if( u_shadow[i].enable )
            v_positionLightSpace[i] = u_shadow[i].projectionMtx * u_shadow[i].viewMtx * u_modelMtx * a_position;
    }
}
