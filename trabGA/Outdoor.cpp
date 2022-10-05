#include "Outdoor.h"

Outdoor::Outdoor(Texture *texture)
{
  ObjectReader *reader = new ObjectReader();

  Mesh *mesh = reader->read("./trabGA/assets/outdoor.obj");

  this->_mesh = mesh;
  this->_mesh->setTexture(texture);
}

void *Outdoor::draw()
{
  this->_mesh->draw();
}

void Outdoor::onCollision(Object *obj)
{
}