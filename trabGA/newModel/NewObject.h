#pragma once
#define NEW_MESH_H

#include <vector>
#include <map>
#include "NewMesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class NewObject
{

private:
  NewMesh *newMesh;
  glm::vec3 direction = glm::vec3(0.0f);
  glm::vec3 scale = glm::vec3(1.0f);
  glm::vec3 translate = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f, 1.0f, 0.0f);
  float velocity = 0.0f;
  float rotationAngle = 0.0f;
  bool isBullet = false;
  bool hasCollision = false;

public:
  NewObject(string meshPath);
  ~NewObject();

  NewMesh *getMesh()
  {
    return newMesh;
  };

  glm::vec3 getScale()
  {
    return scale;
  };

  glm::vec3 getTranslate()
  {
    return translate;
  };

  float getVelocity()
  {
    return velocity;
  };

  glm::vec3 getRotation()
  {
    return rotation;
  };

  float getRotationAngle()
  {
    return rotationAngle;
  };

  bool getHasCollision()
  {
    return hasCollision;
  };

  bool getIsBullet()
  {
    return isBullet;
  };

  glm::vec3 getDirection()
  {
    return direction;
  }

  void setScale(glm::vec3 newScale)
  {
    this->scale = newScale;
  };

  void setTranslate(glm::vec3 newTranslate)
  {
    this->translate = newTranslate;
  };

  void setDirection(glm::vec3 newDirection)
  {
    this->direction = newDirection;
  }

  void setVelocity(float velocity)
  {
    this->velocity = velocity;
  };

  void setRotation(glm::vec3 newRotation)
  {
    this->rotation = newRotation;
  };

  void setRotationAngle(float rotationAngle)
  {
    this->rotationAngle = rotationAngle;
  };

  void setHasCollision(bool hasCollision)
  {
    this->hasCollision = hasCollision;
  };

  void setIsBullet(bool isBullet)
  {
    this->isBullet = isBullet;
  };
};
