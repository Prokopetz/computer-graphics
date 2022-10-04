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
  virtual glm::vec3 getRotation() = 0;
  virtual glm::vec3 getScale() = 0;
  virtual float getRotationDegrees() = 0;
  virtual void setMesh(Mesh *mesh) = 0;
  virtual void *setPosition(glm::vec3 position) = 0;
  virtual void *setRotation(glm::vec3 rotate) = 0;
  virtual void *setScale(glm::vec3 scale) = 0;
  virtual void *setRotationDegrees(float degrees) = 0;
};

#endif