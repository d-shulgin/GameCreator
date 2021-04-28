precision mediump float;

struct MaterialData
{
    // ambient
    vec3 ambientColor;
    bool useAmbientMap;
    sampler2D ambientMap;
    // diffuse
    vec3 diffuseColor;
    bool useDiffuseMap;
    sampler2D diffuseMap;
    // specular
    vec3 specularColor;
    float specExp;
    bool useSpecularMap;
    sampler2D specularMap;
    // normal (bump)
    bool useNormalMap;
    sampler2D normalMap;
    // dissolve /// @todo: not supported
    float dissolve;
    bool halo;
    bool useDissolveMap;
    sampler2D dissolveMap;
};

// material params...
uniform MaterialData u_material;
// mesh...
varying vec4 v_position;
varying vec2 v_texturePos;

void main()
{
//    float depth = (v_position.z / v_position.w)*0.5 + 0.5;

//    float d = depth * 255.0;
//    float p1 = floor(d) / 255.0;

//    d = fract(d) * 255.0;
//    float p2 = floor(d) / 255.0;

//    d = fract(d) * 255.0;
//    float p3 = floor(d) / 255.0;
//    float p4 = fract(d);

//    gl_FragColor = vec4( p1, p2, p3, p4 );

    if( u_material.useDissolveMap )
    {
        vec4 dissolve = texture2D(u_material.dissolveMap, v_texturePos);
        if( dissolve.r == 0 )
            discard;
    }

    float depth = 1.0 -((v_position.z / v_position.w)*0.5 + 0.5);

    float d = depth * 255.0;
    float p1 = floor(d) / 255.0;

    d = fract(d) * 255.0;
    float p2 = floor(d) / 255.0;

    d = fract(d) * 255.0;
    float p3 = floor(d) / 255.0;
    float p4 = fract(d);

    gl_FragColor = vec4( p1, p2, p3, p4 );
    //gl_FragColor = vec4( depth, depth, depth, 1.0);
}
