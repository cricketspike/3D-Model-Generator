#version 120

attribute vec3 position;
attribute vec2 texture_coord;

varying vec2 texture_coord0;//varying will be shared with .fs
uniform mat4 transform; //uniform can be set by cpu

void main()
{
 gl_Position = transform* vec4(position, 1.0);//the 1.0 is like weight
 texture_coord0=texture_coord;//send to .fs since they cn share a varying variable
}