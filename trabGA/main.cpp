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

  Player *player = new Player(scene->camera);
  scene->addPlayer(player);

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
  Outdoor *outdoor = new Outdoor(outdoorTexture);
  Outdoor *outdoor2 = new Outdoor(outdoorTexture);

  vector<glm::vec3> enemies = {
    glm::vec3(3.0f, 0.0f, 5.0f),
    glm::vec3(13.0f, 0.0f, 2.0f),
    glm::vec3(24.0f, 0.0f, 12.0f),
    glm::vec3(33.0f, 0.0f, -5.0f),
    glm::vec3(23.0f, 0.0f, -15.0f),
    glm::vec3(-38.0f, 0.0f, -58.0f),
  };

  for(glm::vec3 enemyCoord : enemies) {
    Enemy *enemy = new Enemy(enemyTexture);
    enemy->setPosition(enemyCoord);
    scene->addObject(enemy);
  }

  backpack->setPosition(glm::vec3(0.0f, 2.2f, -10.5f));
  outdoor->setPosition(glm::vec3(5.0f, 0.0f, -20.0f));
  outdoor2->setPosition(glm::vec3(-30.0f, 0.0f, 20.0f));
  scene->addObject(backpack);
  scene->addObject(ground);
  scene->addObject(outdoor);

  // scene.addObject("camera");
  return scene->run();
}