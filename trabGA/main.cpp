#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include "Scene.h"
#include "models/Texture.h"
#include "objects/Backpack.h"
#include "objects/Ground.h"
#include "objects/Player.h"
#include "objects/Bullet.h"

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

  Ground *ground = new Ground(groundTexture);
  Backpack *backpack = new Backpack(backpackTexture);

  backpack->setPosition(glm::vec3(0.0f, 2.2f, -10.5f));
  scene->addObject(backpack);
  scene->addObject(ground);

  return scene->run();
}