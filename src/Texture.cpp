#include "Texture.h"
#include "stb_image.h"
#include <assert.h>
#include <iostream>
Texture::Texture(const std::string filename) {
	int width, height, quantity_components;
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &quantity_components, 4);
	//& variables will be loaded from this
	if (imageData == NULL) {
		std::cerr << "could not load texture "<<std::endl;
	}
	glGenTextures(1,&m_texture);//generate 1 texture here
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//if mesh goes out of textures x bounds wrap repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//if mesh goes out of textures y bounds just fill with black

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//if scaling down do so with linear interpolation
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//if scaling up do so with linear interpolation

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	//level for mipmapping (better texture up close)
	//pices stored with red green blue alpha format

	stbi_image_free(imageData);
}

Texture::~Texture() {

	glDeleteTextures(1, &m_texture);
}
void Texture::bind(unsigned int unit) {
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);//gltexure0 is a number value, and all these values are sequential
	glBindTexture(GL_TEXTURE_2D,m_texture);
}