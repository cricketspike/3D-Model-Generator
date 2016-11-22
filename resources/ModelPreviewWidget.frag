#version 330

uniform sampler2D texture;
uniform int useTexture;

varying mediump vec2 texc;

void main()
{
    if (useTexture > 0)
        gl_FragColor = texture2D(texture, texc);
    else
        gl_FragColor = vec4(0.8, 0.8, 0.8, 1.0);

    if (gl_FragColor.rgb == vec3(1.0, 1.0, 1.0))
        gl_FragColor.a = 0.4;
}
