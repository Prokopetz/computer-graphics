#ifndef CUBO_H
#define CUBO_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Face.h"

class Cubo
{

private:
  Face *createFace(int v0, int v1, int v2, int v3, int normal);
  Shader *shader;

  Mesh *mesh;

public:
  Cubo();
  int init(GLFWwindow *window);
  void run(GLFWwindow *window);
};

#endif