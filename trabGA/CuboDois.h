#ifndef CUBO_DOIS_H
#define CUBO_DOIS_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Object.h"

class CuboDois : public Object
{

private:
  Mesh *_mesh;

public:
  CuboDois(Mesh *mesh);
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
  void setMesh(Mesh *mesh) override
  {
    this->_mesh = mesh;
  };
  void *setPosition(glm::vec3 position) override;
};

#endif