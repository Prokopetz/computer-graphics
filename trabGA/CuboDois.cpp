#include "CuboDois.h"

CuboDois::CuboDois(Mesh *mesh)
{
  this->_mesh = mesh;
}

void *CuboDois::draw()
{
  this->_mesh->draw();
}

void *CuboDois::setPosition(glm::vec3 position)
{
  this->position = position;
}
