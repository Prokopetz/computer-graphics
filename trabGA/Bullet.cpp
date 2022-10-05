#include "Bullet.h"

Bullet::Bullet(Camera *camera, Texture *texture, Mesh *mesh)
{
  this->_mesh = mesh;
  this->_mesh->setTexture(texture);
  this->setPosition(camera->cameraPosition);
  this->cameraFront = camera->cameraFront;
  this->cameraUp = camera->cameraUp;
  this->cameraPosition = camera->cameraPosition;
}

void *Bullet::draw()
{
  this->setPosition(speed * cameraFront + this->position);
  this->setRotation(glm::vec3(1.0, 0.0, -1.0) * cameraPosition);
  this->_mesh->draw();
}