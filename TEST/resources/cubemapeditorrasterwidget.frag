#version 330

uniform sampler2D texture;
uniform int haveTexture;

varying mediump vec2 texc;

void main()
{
    if (haveTexture > 0)
        gl_FragColor = texture2D(texture, texc);
    else
        gl_FragColor = vec4(0.8, 0.8, 0.8, 1.0);
}
