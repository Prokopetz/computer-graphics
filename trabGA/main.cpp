#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include "Scene.h"
#include "Backpack.h"
#include "Ground.h"
#include "Player.h"
#include "Bullet.h"
#include "Outdoor.h"
#include "Enemy.h"

int main()
{
  Scene *scene = new Scene(800, 600, "Quake");
  scene->init();

  Texture *groundTexture = new Texture();
  groundTexture->load("./trabGA/assets/ground.jpg", scene->shader->program);

  Texture *backpackTexture = new Texture();
  backpackTexture->load("./trabGA/assets/backpack.jpg", scene->shader->program);

  Texture *bulletTexture = new Texture();
  bulletTexture->load("./trabGA/assets/mesa01.bmp", scene->shader->program);

  Texture *outdoorTexture = new Texture();
  outdoorTexture->load("./trabGA/assets/iron.jpeg", scene->shader->program);

  Texture *enemyTexture = new Texture();
  enemyTexture->load("./trabGA/assets/enemy.jpeg", scene->shader->program);

  Ground *ground = new Ground(groundTexture);
  Backpack *backpack = new Backpack(backpackTexture);
  Player *player = new Player(scene->camera);
  Outdoor *outdoor = new Outdoor(outdoorTexture);
  Enemy *enemy = new Enemy(enemyTexture);

  backpack->setPosition(glm::vec3(0.0f, 2.2f, -10.5f));
  outdoor->setPosition(glm::vec3(5.0f, 0.0f, -20.0f));
  enemy->setPosition(glm::vec3(3.0f, 0.0f, 5.0f));
  scene->addObject(backpack);
  scene->addObject(ground);
  scene->addPlayer(player);
  scene->addObject(outdoor);
  scene->addObject(enemy);

  // scene.addObject("camera");
  return scene->run();
}