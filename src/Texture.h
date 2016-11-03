#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glew\gl\glew.h>


class Texture{
public:
	Texture(const std::string filename);

	void bind(unsigned int unit);//can hold up to 32 textures at once

	virtual ~Texture();

protected:

private:
	Texture(const Texture& other) {}
	void operator =(const Texture& other) {}
	
	GLuint m_texture;


};

#endif // TEXTURE_H
