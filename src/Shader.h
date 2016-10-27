#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glew/GL/glew.h>
#include "Transform.h"

class Shader {
public:
	Shader(const std::string file_name);//takes shadder from separate file
	void bind();//have our renderer start using this shader
	void update(const Transform& transform);
	
	
	
	virtual ~Shader();

protected:
private:
	static const unsigned int NUM_SHADERS = 2;


	void operator=(const Shader& other) {}
	
	Shader(const Shader& other) {}

	//get the text from the shader file
	std::string LoadShader(const std::string& fileName);
	
	
	//make sure the shader is working
	void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	
	//use shader input text to create a shader
	GLuint CreateShader(const std::string& text, unsigned int type);
	
	enum {//enum are like local cont variables

		TRANSFORM_U,//0(index of transform variable)
		NUM_UNIFORMS//1
	};


	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];//uniforms are variables for shader
	GLuint m_uniforms[NUM_UNIFORMS];


};





#endif //SHADER_H
