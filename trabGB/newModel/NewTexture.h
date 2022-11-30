#pragma once
#ifndef NEW_TEXTURE_H
#define NEW_TEXTURE_H

#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <string>

class Texture
{
private:
	GLuint textureID;
	GLint textureLocation;
	GLshort textureNum;

public:
	Texture();
	~Texture();

	void Load( char* path, char* textureUniformName, GLuint shaderProgram, GLint textureNum );

	GLuint GetTextureId() { return textureID; }
	GLshort GetTextureNum() { return textureNum; }

};

#endif
