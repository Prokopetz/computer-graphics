#include "Enemy.h"

Enemy::Enemy(Texture *texture)
{
  ObjectReader *reader = new ObjectReader();

  Mesh *mesh = reader->read("./trabGA/assets/enemy.obj");

  this->_mesh = mesh;
  this->_mesh->setTexture(texture);
}

void *Enemy::draw()
{
  this->_mesh->draw();
}

void Enemy::onCollision(Object *obj)
{
  this->_shouldRender = false;
  this->_hasCollision = false;
}