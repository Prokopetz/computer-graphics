#include "Camera.h"

void Camera::updateCamera()
{
  this->projection = glm::perspective(glm::radians(45.0f), (float)this->WIDTH / (float)this->HEIGHT, 0.1f, 100.0f);
  // this->projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

  this->view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

  this->shader->setMatrix4fv("projection", this->projection);
  this->shader->setMatrix4fv("view", this->view);

  this->shader->use();
}

void Camera::moveForward()
{
  cameraPosition += cameraSpeed * cameraFront;
}

void Camera::moveBackward()
{
  cameraPosition -= cameraSpeed * cameraFront;
}

void Camera::moveLeft()
{
  cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * this->cameraSpeed;
}

void Camera::moveRight()
{
  cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::rotateRight() {
  yaw += 1.0f;
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw));
  direction.y = 0.0f;
  direction.z = sin(glm::radians(yaw));
  cameraFront = glm::normalize(direction);
}

void Camera::rotateLeft() {
  yaw -= 1.0f;
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)); 
  direction.y = 0.0f;
  direction.z = sin(glm::radians(yaw));
  cameraFront = glm::normalize(direction);
}