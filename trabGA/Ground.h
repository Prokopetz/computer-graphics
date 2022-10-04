#ifndef GROUND_H
#define GROUND_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Object.h"
#include "Texture.h"
#include "ObjectReader.h"

class Ground : public Object
{

private:
  Mesh *_mesh;
  Texture *_texture;

public:
  Ground(Texture *texture);
  float rotationDegrees = 0.0f;
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0, 1.0, 0.0);
  glm::vec3 scale = glm::vec3(1.0f);
  
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

  glm::vec3 getScale() override
  {
    return this->scale;
  };

  glm::vec3 getRotation() override
  {
    return this->rotation;
  };

  float getRotationDegrees() override
  {
    return this->rotationDegrees;
  };

  void *setPosition(glm::vec3 position) override{
    this->position  =position;
  };

  void *setRotation(glm::vec3 rotation) override{
    this->rotation = rotation;
  };

  void *setScale(glm::vec3 scale) override{
    this->scale = scale;
  };

  void *setRotationDegrees(float degrees) override{
    this->rotationDegrees = degrees;
  };

  void setMesh(Mesh *mesh) override
  {
    this->_mesh = mesh;
  };
};

#endif