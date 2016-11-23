#version 330

uniform sampler2D texture;
uniform int haveTexture;
uniform int isProjection;

varying mediump vec2 texc;

void main()
{
    if (haveTexture > 0)
        gl_FragColor = texture2D(texture, texc);
    else
        gl_FragColor = vec4(0.8, 0.8, 0.8, 1.0);

    if (isProjection > 0) {
        gl_FragColor = vec4(gl_FragColor.rgb/2.0, 1.0);
    }
}
