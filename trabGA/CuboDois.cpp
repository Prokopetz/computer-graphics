#include "CuboDois.h"

CuboDois::CuboDois(Mesh *mesh, Texture *texture )
{
  this->_mesh = mesh;
  this->_mesh->setTexture(texture);
}

void *CuboDois::draw()
{
  this->_mesh->draw();
}

void *CuboDois::setPosition(glm::vec3 position)
{
  this->position = position;
}
