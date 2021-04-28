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

    bool useShadowMap;
    sampler2D shadowMap;
};

// material params...
uniform MaterialData u_material;
// light params...
uniform int u_lightAmount;
uniform LightData u_light[8];
// shadow params...
uniform int u_useShadowFiltering; // 0 - none; 1 - PCF
// camera params...
uniform vec4 u_cameraPos;
// font params...
uniform sampler2D u_fontUnit;

// mesh...
varying vec4 v_color;
varying vec2 v_texturePos;
varying vec3 v_normal;
varying vec4 v_position;
varying mat4 v_viewMtx;
varying mat3 v_tbnMtx;
//varying int v_lightAmount;
// shadow...
varying vec4 v_positionLightSpace[8];

float getShadow( vec4, sampler2D, float );
float getShadowPCF( vec4, sampler2D, float );

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

            // shadow...
            float shadow = 0.0;
            if( u_light[i].useShadowMap )
            {
                if( u_useShadowFiltering == 0 )
                    shadow = getShadow( v_positionLightSpace[i], u_light[i].shadowMap, 0.00020 );
                else if( u_useShadowFiltering == 1 )
                    shadow = getShadowPCF( v_positionLightSpace[i], u_light[i].shadowMap, 0.00020 );
            }

            // ambient...
            float Ia = 0.3;
            vec4 ambientColor = vec4(u_material.ambientColor, 1.0) * vec4(lightAColor, 1.0);
            if( u_material.useAmbientMap )
                ambientColor = ambientColor * texture2D(u_material.ambientMap, v_texturePos);

            // diffuse...
            vec4 diffuseColor = vec4(0.0, 0.0, 0.0, 1.0);
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
            vec3 normalVec = v_normal;
            if( u_material.useNormalMap )
            {
                normalVec = normalize(texture2D(u_material.normalMap, v_texturePos).rgb * 2.0 - 1.0);
                lightVec = normalize(v_tbnMtx * lightVec);
            }
            if( length(u_material.diffuseColor) > 0.0001 )
            {
                float diffuse = max(dot(normalVec, lightVec), 0.0) * fading;
                diffuseColor = vec4(diffuse * u_material.diffuseColor, 1.0) * vec4(lightDColor, 1.0);
            }
//            if( u_material.useDiffuseMap )
//                materialColor = (diffuseColor + ambientColor) * texture2D(u_material.diffuseMap, v_texturePos);
            lightColor += diffuseColor*I*(1.0 - shadow) + ambientColor;

            // specular...
            vec4 specularColor = vec4(0.0, 0.0, 0.0, 1.0);
            if( length(u_material.specularColor) > 0.0001 )
            {
                vec3 reflectVec = normalize(reflect(-lightVec, normalVec));
                vec3 lookVec = normalize(u_cameraPos.xyz - v_position.xyz);
                if( u_material.useNormalMap )
                {
                    lookVec = normalize(v_tbnMtx * lookVec);
                }
                float specular = pow(max(dot(lookVec, reflectVec), 0.0), u_material.specExp) * fading;
                if( specular > 0.0001 )
                {
                    specularColor = vec4(specular * u_material.specularColor, 1.0) * vec4(lightSColor, 1.0);
                    if( u_material.useSpecularMap )
                        specularColor = specularColor * texture2D(u_material.specularMap, v_texturePos);
                }
            }

            lightSpecularColor += specularColor*I*(1.0 - shadow);
            //resultColor += (diffuseColor + specularColor);
            //resultColor += materialColor;
        }

        if( u_material.useDiffuseMap )
            resultColor = lightColor * texture2D(u_material.diffuseMap, v_texturePos) + lightSpecularColor;
        else
            resultColor = lightColor * v_color + lightSpecularColor;
    }
    else
    {
        if( u_material.useDiffuseMap )
            resultColor = v_color * texture2D(u_material.diffuseMap, v_texturePos);
        else
            resultColor = v_color;
    }
    gl_FragColor = resultColor * vec4(1.0, 1.0, 1.0, texture2D(u_fontUnit, v_texturePos).r );
}

float getClosestDepth( sampler2D shadowMap, vec2 uvCoords )
{
    vec4 v = texture2D( shadowMap, uvCoords );
    return( (v.x*255.0 + (v.y*255.0 + (v.z*255.0 + v.w)/255.0)/255.0)/255.0 );
    //return( v.x );
}
float getShadow( vec4 positionLightSpace, sampler2D shadowMap, float bias )
{
    vec3 projCoords = positionLightSpace.xyz / positionLightSpace.w;
    projCoords = projCoords*0.5 + 0.5;
    float closestDepth = getClosestDepth( shadowMap, projCoords.xy );
    if( closestDepth > (1.0 - projCoords.z)+ bias )
        return( 1.0 );
    return( 0.0 );
    //return( step(closestDepth, (1.0 - projCoords.z)) );
}
float getShadowPCF( vec4 positionLightSpace, sampler2D shadowMap, float bias )
{
    vec3 projCoords = positionLightSpace.xyz / positionLightSpace.w;
    projCoords = projCoords*0.5 + 0.5;
    float result = 0.0;
    vec2 texelSize = 1.0 / textureSize( shadowMap, 0 );
    for( int x = -1; x <= 1; ++x )
    {
        for( int y = -1; y <= 1; ++y )
        {
            if( x != 0 || y != 0 )
            {
                float closestDepth = getClosestDepth( shadowMap, projCoords.xy + vec2(x, y)*texelSize );
                if( closestDepth > (1.0 - projCoords.z)+ bias )
                    result += 1.0;
            }
        }
    }
    return( result / 8.0 );
}
