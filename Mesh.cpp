#include "mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int num_vertices)
{
	m_draw_count = num_vertices;
	// create array to store all vertices

	glGenVertexArrays(1, &m_vertexArrayObject);//number of them to create,object
	glBindVertexArray(m_vertexArrayObject);//makes any vertex array opperations be done on this object
		
	std::vector < glm::vec3> positions;
	std::vector < glm::vec2> texture_coords;

	positions.reserve(num_vertices);
	texture_coords.reserve(num_vertices);
	//this only works when we know the number

	for (unsigned int i = 0; i < num_vertices; i++) {

		positions.push_back(vertices[i].getPos());
		texture_coords.push_back(vertices[i].getTextureCoords());

	}

	//create a buffer and find a place for it and tell gl to send its vertices to it
		glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);//initializes the array, buffer
		glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[POSITION_VB]);//how to interpret buffer(glarray means as an array), buffer
		glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(positions[0]),&positions[0],GL_STATIC_DRAW);
		//takes data from ram and give it to gpu,
		//GLSTATIC DRAW: plan on not modifying this data so put it in a place based on that assumption
		//vertex attrib arrays tell how to read in data
		
		glEnableVertexAttribArray(0);//get opengl ready to take in info

		//this will read in data from a vector in a certain way, ***if you have a crash when drawing check here
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//array #0 (created above),peices of data(vector3 pos),type of data(float), dont normalize,dont skip between steps(skip 0),start again at 0 since no skipping

		
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);//how to interpret buffer(glarray means as an array), buffer
		glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(texture_coords[0]), &texture_coords[0], GL_STATIC_DRAW);



		glEnableVertexAttribArray(1);//get opengl ready to take in info
		glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE,0,0);//array #1 (created above),2 peices of data(vector3 pos),type of data(float), dont normalize,dont skip between steps(skip 0),start again at 0 since no skipping
		
		
		glBindVertexArray(0);//makes any vertex array opperations be done on no object

}
Mesh::~Mesh() {
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);

}
void Mesh::draw() {
	glBindVertexArray(m_vertexArrayObject);//makes any vertex array opperations be done on this object
	glDrawArrays(GL_TRIANGLES,0,m_draw_count);//draw all vertices starting at 0 as triangles
	//this will cause an error id 

	glBindVertexArray(0);//makes any vertex array opperations be done on no object

}
