#version 330

attribute highp vec3 positionCoords;
attribute highp vec2 textureCoords;

uniform highp mat4 model;
uniform highp mat4 view;
uniform highp mat4 projection;

// Image/face focus
uniform highp float zoom;
uniform highp vec2 offset;

varying mediump vec2 texc;

void main()
{
  gl_Position = projection * view * model * vec4(positionCoords, 1.0);

  /* Texture coordinates based on the image/face focus
  *     1. Change from [0,1] to [-0.5,+0.5] UV space
  *         in order to scale the UV area according to zoom
  *     2. Change from [-0.5,+0.5] back to [0,1] UV space
  *    3. Apply the panning offset
  *
  */

  texc = (textureCoords - vec2(0.5, 0.5))/zoom + vec2(0.5, 0.5) - offset;
}
