#version 330

in highp vec3 positionCoords;
in highp vec3 texColor;

uniform highp mat4 model;
uniform highp mat4 view;
uniform highp mat4 projection;

out mediump vec3 vertexColor;


void main()
{
  gl_Position = projection * view * model * vec4(positionCoords, 1.0);
  vertexColor = texColor; // Set the output variable to a dark-red color

}
