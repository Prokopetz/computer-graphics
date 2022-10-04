#include "Bullet.h"

Bullet::Bullet(Camera *camera, Texture *texture, Mesh *mesh)
{
  this->_mesh = mesh;
  this->_mesh->setTexture(texture);
  this->setPosition(camera->cameraPosition);
  this->cameraFront = camera->cameraFront;
}

void *Bullet::draw()
{

  this->setPosition(speed * cameraFront * (float)glfwGetTime() + this->position);
  this->_mesh->draw();
}