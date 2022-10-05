#include "Enemy.h"
#include "Bullet.h"
#include "Object.h"

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
  Bullet *bullet = dynamic_cast<Bullet *>(obj);
  if (bullet)
  {
    this->_shouldRender = false;
    this->_hasCollision = false;
  }
}