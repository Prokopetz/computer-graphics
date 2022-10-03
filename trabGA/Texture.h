#pragma once
#define TEXTURE_H

#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

class Texture
{
private:
	GLuint textureID;
	GLint textureLocation;

public:
  void load(char* path, GLuint shaderProgram);
  
	GLuint getTextureId() { return textureID; }

};