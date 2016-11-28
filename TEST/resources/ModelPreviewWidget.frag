#version 330

in vec3 vertexColor; // The input variable from the vertex shader (same name and same type)
out vec4 color;
void main()
{
        color = vec4(vertexColor[0],vertexColor[1],vertexColor[2],1);

}
