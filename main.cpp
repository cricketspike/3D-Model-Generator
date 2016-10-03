#include <iostream>
#include "Display.h"
#include<glew\GL\glew.h>
#include "shader.h"
#include "mesh.h"
#include "Texture.h"
int main(int argc, char* argv[])
{

	/*
	Based on modern openGL tutorial:
	https://www.youtube.com/watch?v=ftiKrP3gW3k

	SDL->OS->Window
	OPenGL context makes OS give up control of window and allows GPU to write to it
	OpenGL->GPU(proccessor)->Window
	*/



	/*
	how does a drawing/rendering happen?
	data(raw)->
	proccessing(standard form)(vertices)(vertex shader)->
	rasterization(triangles)->(sends all of triangle's pixels)
	proccessing2(pixels colors)->
	output image
	a bunch of this done in parallel


	need to break down data for this "pipeline"

	shader is code

	*/
	Display display(800,600,"hello");

	Shader shader("./res/basic_shader");
	Texture texture("./res/image1.jpg");
	Vertex vertices[] = { 
		
		Vertex(glm::vec3(-0.5,-0.5,0),glm::vec2(0.0,1.0)) ,
		Vertex(glm::vec3(-0.5,0.5,0),glm::vec2(0.0,0.0)) ,
		Vertex(glm::vec3(0.5,-0.5,0),glm::vec2(1.0,1.0)),

		Vertex(glm::vec3(-0.5,0.5,0),glm::vec2(0.0,0.0)) ,
		Vertex(glm::vec3(0.5,-0.5,0),glm::vec2(1.0,1.0)),
		Vertex(glm::vec3(0.5,0.5,0),glm::vec2(1.0,0.0))


	};//vertex is from mesh.h
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));//ammount of objects in array=size of array/size of objects
	float counter= 0.0f;
	Transform transform;
	while (!display.isClosed())
	{
		counter += 0.1f;
		transform.getLoc().x = sinf(counter);
		transform.getRot().z = counter;
		float cosCounter = cosf(counter);
		transform.setScale(.8, .8*cosCounter, 1);

		
		display.clear(0.0f,0.1f,0.1f,1.0f);
		shader.bind();
		shader.update(transform);
		
		texture.bind(0);
		
		mesh.draw();
		
		display.update();
	}
	return 0;
}