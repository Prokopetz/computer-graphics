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

}