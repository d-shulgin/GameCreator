precision mediump float;

// material params...
uniform sampler2D u_textureUnit;

// mesh...
varying vec4 v_color;
varying vec2 v_texturePos;
varying vec4 v_position;

void main()
{
    vec4 resultColor = texture2D(u_textureUnit, v_texturePos);
    gl_FragColor = resultColor;
}
