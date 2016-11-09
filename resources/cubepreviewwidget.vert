#version 330

attribute highp vec3 positionCoords;
attribute highp vec2 textureCoords;

uniform highp mat4 model;
uniform highp mat4 view;
uniform highp mat4 projection;

varying mediump vec2 texc;

void main()
{
  gl_Position = projection * view * model * vec4(positionCoords, 1.0);
  texc = textureCoords;
}
