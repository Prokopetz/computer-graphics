#include "Backpack.h"

Backpack::Backpack(Texture* texture)
{
  ObjectReader *reader = new ObjectReader();
  
  Mesh* mesh = reader->read("./trabGA/assets/Backpack.obj");

  this->_mesh = mesh;
  this->_mesh->setTexture(texture);
}

void *Backpack::draw()
{
  this->_scale = 2.25f - sin(glm::radians(glfwGetTime() * 200.0f))*0.05f; 

  this->setPosition(glm::vec3(this->position.x, 1.0f + this->_scale, this->position.z));
  this->_mesh->draw();
}

void Backpack::onCollision(Object* obj) {
  this->_shouldRender = false;
  this->_hasCollision = false;
}