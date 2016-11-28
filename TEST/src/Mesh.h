#pragma once
#ifndef MESH_H
#define MESH_H
#include<glm/glm.hpp>
#include<glew/GL/glew.h>
//Vertex: x,y,z between -1 and 1

class Vertex
{
public:
	Vertex(const glm::vec3& pos, glm::vec2 texture_coordianates) {
		this->m_pos = pos;
		this->m_texture_coordianates = texture_coordianates;
	}

	glm::vec3 getPos() { return m_pos; }
	glm::vec2 getTextureCoords() { return m_texture_coordianates; }
private:
	glm::vec3 m_pos;
	glm::vec2 m_texture_coordianates;
};



class Mesh {

public:
	void draw();
	Mesh(Vertex* vertices, unsigned int num_vertices);
	virtual ~Mesh();
protected:
private:
	
	void operator=(const Mesh& other) {}

	enum {
		POSITION_VB,
        INDEX_VB,
		NUM_BUFFERS, //number of buffers in enumeration
		TEXCOORD_VB
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_draw_count;

};
#endif // MESH_H
