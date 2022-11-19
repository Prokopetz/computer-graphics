
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <vector>

#include "Face.h"
#include "Texture.h"

using namespace std;

class Mesh
{
public:
  Mesh(vector<glm::vec3> vertices, vector<glm::vec2> texCoords, vector<Face *> faces);
  void draw();
  void addVertex(glm::vec3 vertex);
  void setTexture(Texture* texture);

private:
  GLuint VAO;
  vector<glm::vec3> vertices;
  vector<Face *> faces;
  vector<int> indices;
  Texture* texture;
};
#endif