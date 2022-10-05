#ifndef BULLET_CREATOR_H
#define BULLET_CREATOR_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Bullet.h"
#include "ObjectReader.h"
#include "Texture.h"

class BulletCreator
{
private:
  Mesh *bulletMesh;
  Texture *bulletTexture;
  Camera *camera;

public:
  BulletCreator(Camera *camera, int program)
  {
    this->bulletTexture = new Texture();
    this->bulletTexture->load("./trabGA/assets/iron.jpeg", program);
    ObjectReader *reader = new ObjectReader();
    this->bulletMesh = reader->read("./trabGA/assets/cubee.obj");
    this->camera = camera;
  }
  Bullet *createBullet()
  {
    Bullet *bullet = new Bullet(camera, bulletTexture, bulletMesh);
    return bullet;
  };
};

#endif