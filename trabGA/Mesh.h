
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <vector>

#include "Face.h"

using namespace std;

class Mesh
{
public:
  Mesh(vector<glm::vec3> vertices, vector<Face *> faces);
  void draw();
  void addVertex(glm::vec3 vertex);

private:
  GLuint VAO;
  vector<glm::vec3> vertices;
  vector<Face *> faces;
  vector<int> indices;
};
#endif