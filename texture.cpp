#include "texture.h"
#include "stb_image.h"
#include <iostream>


texture::texture(const string& file)
{
	int width, height, numComponents;
	//Loadind the texture file from public domain image reader
	unsigned char* imageData = stbi_load(file.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		cerr << "Texture loading failed for texture: " << file << endl;
	}
	//Tell OpenGL how to interpret the texture
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

texture::~texture()
{
	glDeleteTextures(1, &_texture);
}

void texture::bind(unsigned int unit)
{
	//Texture will be bound to a unit between 0 and 31
	if (!(unit >= 0 && unit <= 31))
	{
		cerr << "unit out of bounds" << endl;
	}

	glActiveTexture(GL_TEXTURE + unit);
	glBindTexture(GL_TEXTURE_2D, _texture);
}