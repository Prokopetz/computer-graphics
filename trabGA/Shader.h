#pragma once
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
  GLuint program;

public:
  Shader(const char *vertexPath, const char *fragmentPath);

  void use()
  {
    glUseProgram(this->program);
  }

  void Delete()
  {
    glDeleteProgram(this->program);
  }

  void setMatrix4fv(const std::string &name, glm::mat4 matrix);
  void setVec3(const std::string &name, glm::vec3 &vec3);
};