#include "Player.h"

Player::Player(Camera* camera)
{
  this->_camera = camera;
}

void *Player::draw()
{
  this->setPosition(this->_camera->cameraPosition);
}

void Player::onCollision(Object* obj) {
  Backpack *backpack = dynamic_cast<Backpack *>(obj);
  if (backpack)
  {
    this->bullets += 3;
  }
}