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

  Ground *ground = new Ground(groundTexture);
  Backpack *backpack = new Backpack(backpackTexture);
  Player *player = new Player(scene->camera);

  backpack->setPosition(glm::vec3(0.0f, 2.2f, -10.5f));
  scene->addObject(backpack);
  scene->addObject(ground);
  scene->addObject(player);

  // scene.addObject("camera");
  return scene->run();
}