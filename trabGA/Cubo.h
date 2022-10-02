#ifndef CUBO_H
#define CUBO_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Face.h"
#include "Object.h"

class Cubo : public Object
{

private:
  Face *createFace(int v0, int v1, int v2, int v3, int normal);
  Shader *shader;
  Mesh *_mesh;

public:
  Cubo();
  glm::vec3 position = glm::vec3(1.0f);
  Mesh *mesh() override
  {
    return this->_mesh;
  };
  int init();
  void *draw() override;
  glm::vec3 getPosition() override
  {
    return this->position;
  };
  void *setPosition(glm::vec3 position) override;
};

#endif