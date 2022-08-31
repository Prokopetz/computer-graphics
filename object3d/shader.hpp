#include <GL/glew.h> // include GLEW and new version of GL on Windows

#ifndef SHADER_HPP
#define SHADER_HPP

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

#endif
