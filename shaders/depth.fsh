precision mediump float;

// material params...
uniform sampler2D u_textureUnit;

// mesh...
varying vec2 v_texturePos;

float getClosestDepth( sampler2D shadowMap, vec2 uvCoords )
{
    vec4 v = texture2D( shadowMap, uvCoords );
    return( (v.x*255.0 + (v.y*255.0 + (v.z*255.0 + v.w)/255.0)/255.0)/255.0 );
    //return( v.x );
}

void main()
{
    vec4 resultColor;
    float depth = getClosestDepth(u_textureUnit, v_texturePos);
    resultColor = vec4(depth, depth, depth, 1.0);
    gl_FragColor = resultColor;
}
