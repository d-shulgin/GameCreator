precision mediump float;

struct LightData
{
    int type; // 0 - light direction
              // 1 - light point
              // 2 - light spot
    float power;
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 position;
    vec3 direction;
    float angle;
    float borderArea;
    // bool useShadowMap;
    // sampler2D shadowMap;
};

// material params...
uniform sampler2D u_textureUnit;
// light params...
uniform int u_lightAmount;
uniform LightData u_light[8];
//uniform vec4 u_lightPos;
//uniform float u_lightPower;
// camera params...
uniform vec4 u_cameraPos;

// mesh...
varying vec4 v_color;
varying vec2 v_texturePos;
varying vec3 v_normal;
varying vec4 v_position;
varying mat4 v_viewMtx;

void main()
{
    vec4 resultColor;
    if( u_lightAmount > 0 && u_lightAmount <= 8 )
    {
        vec3 lightAColor = u_light[0].ambientColor;
        for( int i = 1; i < u_lightAmount; ++i )
        {
            lightAColor = max( lightAColor, u_light[i].ambientColor );
        }
        vec4 lightColor = vec4(0.0, 0.0, 0.0, 1.0);
        vec4 lightSpecularColor = vec4(0.0, 0.0, 0.0, 1.0);

        float ambient = 0.10;
        float k_diffuse = 0.80;
        float k_specular = 0.60;
        float specular_factor = 60.0;
        vec4 materialColor = v_color * texture2D(u_textureUnit, v_texturePos);

        for( int i = 0; i < u_lightAmount; ++i )
        {
            vec3 lightDColor = u_light[i].diffuseColor;
            vec3 lightSColor = u_light[i].specularColor;
            vec4 lightPos = v_viewMtx * vec4(u_light[i].position, 1.0);
            vec4 lightDirect = v_viewMtx * vec4(u_light[i].direction, 0.0);
            float lightOuterCutOff = cos( u_light[i].angle );
            float lightCutOff = cos(u_light[i].angle*(1.0 - u_light[i].borderArea));

            float dist = distance(v_position.xyz, lightPos.xyz)/100.0;
            float fading = u_light[i].power / (1 + 0.25*pow(dist,2));

            // ambient
            vec4 ambientColor = vec4(lightAColor, 1.0);

            // diffuse
            vec3 lightVec;
            float I = 1.0;
            if       ( u_light[i].type == 0 ) // direction |
            {
                lightVec = normalize(-lightDirect.xyz);
                fading = u_light[i].power;
            } else if( u_light[i].type == 1 ) // point     |
            {
                lightVec = normalize(lightPos.xyz - v_position.xyz);
            } else if( u_light[i].type == 2 ) // spot      |
            {
                lightVec = normalize(lightPos.xyz - v_position.xyz);
                float angle = dot(lightVec, normalize(-lightDirect.xyz));
                I = clamp( (angle - lightOuterCutOff)/(lightCutOff - lightOuterCutOff), 0.0, 1.0 );
//                if( angle < lightOuterCutOff )
//                    lightVec = vec3(0.0, 0.0, 0.0);
            }
            vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 1.0);
            float diffuse = k_diffuse * max(dot(v_normal, lightVec), 0.0) * fading;
            diffuseColor = vec4(diffuse * lightDColor, 1.0);

            lightColor += diffuseColor*I + ambientColor;

            // specular
            vec4 specularColor = vec4(0.0, 0.0, 0.0, 1.0);
            if( k_specular > 0.0 )
            {
                vec3 reflectVec = normalize(reflect(-lightVec, v_normal));
                vec3 lookVec = normalize(u_cameraPos.xyz - v_position.xyz);
                float specular = k_specular * pow(max(dot(lookVec, reflectVec), 0.0), specular_factor) * fading;

                if( specular > 0.001 )
                    specularColor = vec4(specular * lightSColor, 1.0);
                    //resultColor += vec4(specular * lightColor.rgb, 0.0);
            }
            lightSpecularColor += specularColor*I;
        }
        resultColor = lightColor * materialColor + lightSpecularColor;


        //resultColor = vec4((ambient + diffuse) * materialColor.rgb, materialColor.a);
//        if( k_specular > 0.0 )
//        {
//            vec3 reflectVec = normalize(reflect(-lightVec, v_normal));
//            vec3 lookVec = normalize(u_cameraPos.xyz - v_position.xyz);
//            float specular = k_specular * pow(max(dot(lookVec, reflectVec), 0.0), specular_factor) * fading;
//            if( specular > 0.001 )
//                resultColor += vec4(specular * lightColor.rgb, 0.0);
//        }
    }
    else
    {
        resultColor = v_color * texture2D(u_textureUnit, v_texturePos);
    }
    gl_FragColor = resultColor;
}
