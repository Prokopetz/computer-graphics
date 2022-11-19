#ifndef PLAYER_H
#define PLAYER_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../models/Mesh.h"
#include "../models/Object.h"
#include "../models/Texture.h"
#include "Camera.h"
#include "Backpack.h"

class Player : public Object
{

private:
  float _scale = 1.0f;
  Camera* _camera;

public:
  Player(Camera* camera);
  float rotationDegrees = 0.0f;
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0, 1.0, 0.0);
  glm::vec3 scale = glm::vec3(1.0f);
  glm::vec2 colliderSize = glm::vec2(1.0f);
  int bullets = 3;

  Mesh *mesh() override
  {
    return nullptr;
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

  glm::vec2 getColliderSize() override
  {
    return this->colliderSize;
  };

  bool hasCollision() override
  {
    return true;
  };

  void *setPosition(glm::vec3 position) override{
    this->position = position;
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
    
  };

  void onCollision(Object* obj) override;

  bool shouldRender() override {
    return true;
  }

};

#endif