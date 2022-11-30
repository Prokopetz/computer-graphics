#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include "NewTexture.h"

Texture::Texture() {}

Texture::~Texture() {}

void Texture::Load(char *path, char *textureUniformName, GLuint shaderProgram, GLint textureNum)
{
	this->textureNum = textureNum;

	glGenTextures(1, &textureID);

	textureLocation = glGetUniformLocation(shaderProgram, textureUniformName);

	glActiveTexture(GL_TEXTURE0 + this->textureNum);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glUniform1i(textureLocation, this->textureNum);

	glBindTexture(GL_TEXTURE_2D, 0);
}
