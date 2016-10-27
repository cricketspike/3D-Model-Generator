#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string file_name) {
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(file_name +".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(file_name +".fs"), GL_FRAGMENT_SHADER);
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}
	glBindAttribLocation(m_program, 0, "position");//the string will be a variable in shader file
		glBindAttribLocation(m_program, 1, "texture_coord");//the string will be a variable in shader file

		glLinkProgram(m_program);
		CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: linking failed");
		glValidateProgram(m_program);
		CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");
		m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");//get transform variable from shader file
	
}
void Shader::bind() {
	glUseProgram(m_program);

}
Shader::~Shader() {
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		//delete shaders
		glDetachShader(m_program,m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	//delete program
	glDeleteProgram(m_program);
}




std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}


void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}


GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)//if shader doesnt contain a shader
		std::cerr << "Error compiling shader type " << type << std::endl;

	const GLchar* shader_texts[1];
	shader_texts[0] = text.c_str();
	GLint shader_lengths[1];
	shader_lengths[0] = text.length();

	glShaderSource(shader, 1, shader_texts, shader_lengths);//sets shader to be compiled
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}
void Shader::update(const Transform& transform){
	glm::mat4 modelMatrix =transform.getModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &modelMatrix[0][0]);//4x4 float matrix

}