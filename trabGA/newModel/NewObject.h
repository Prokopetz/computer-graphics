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
	NewMesh* newMesh;
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 translate =  glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	float rotationAngle = 0.0f;

public:
	NewObject(string meshPath);
	~NewObject();

	NewMesh* getMesh() {
    return newMesh;
  };

	glm::vec3 getScale() {
    return scale;
  };

	glm::vec3 getTranslate() {
    return translate;
  };

	glm::vec3 getRotation() {
    return rotation;
  };

	float getRotationAngle() {
    return rotationAngle;
  };

	void setScale(glm::vec3 newScale) {
    this->scale = newScale;
  };

	void setTranslate(glm::vec3 newTranslate) {
    this->translate = newTranslate;
  };

	void setRotation(glm::vec3 newRotation) {
    this->rotation = newRotation;
  };

	void setRotationAngle(float rotationAngle) {
    this->rotationAngle = rotationAngle;
  };
};
