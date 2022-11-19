#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "stb_image.h"

void Texture::load(char* path, GLuint shaderProgram )
{
	this->textureNum = textureNum;
	glGenTextures( 1, &textureID );

	glBindTexture( GL_TEXTURE_2D, textureID );

	int width, height, nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0); 

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glUniform1i( glGetUniformLocation( shaderProgram, "ourTexture" ), this->textureID );

	glBindTexture( GL_TEXTURE_2D, 0 );
}

