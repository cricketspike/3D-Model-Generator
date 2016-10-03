#version 120
varying vec2 texture_coord0;
uniform sampler2D diffuse;


void main()
{
gl_FragColor=texture2D(diffuse,texture_coord0);

}//texture coordinbates are normalized