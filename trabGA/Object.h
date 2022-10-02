#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "Mesh.h"

class Object
{
public:
  virtual ~Object(){};
  virtual Mesh *mesh() = 0;
  virtual void *draw() = 0;
  virtual glm::vec3 getPosition() = 0;
  virtual void setMesh(Mesh *mesh) = 0;
  virtual void *setPosition(glm::vec3 position) = 0;
};

#endif