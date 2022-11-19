#include "Ground.h"

Ground::Ground(Texture* texture)
{
  ObjectReader *reader = new ObjectReader();
  
  Mesh* mesh = reader->read("./trabGA/assets/ground.obj");

  this->_mesh = mesh;
  this->_mesh->setTexture(texture);
}

void *Ground::draw()
{
  this->_mesh->draw();
}