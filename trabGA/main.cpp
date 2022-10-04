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
#include "Face.h"

Face *createFace(int v1, int v2, int v3, int v4)
{
  Face *face = new Face();
  face->addVerticeIndex(v1);
  face->addVerticeIndex(v2);
  face->addVerticeIndex(v3);

  face->addVerticeIndex(v1);
  face->addVerticeIndex(v4);
  face->addVerticeIndex(v3);
  return face;
}

int main()
{
  Scene *scene = new Scene(800, 600, "Quake");
  scene->init();

  Texture *groundTexture = new Texture();
  groundTexture->load("./trabGA/assets/ground.jpg", scene->shader->program);

  Texture *backpackTexture = new Texture();
  backpackTexture->load("./trabGA/assets/backpack.jpg", scene->shader->program);
  
  Backpack *backpack = new Backpack(backpackTexture);
  Ground *ground = new Ground(groundTexture);

  backpack->setPosition(glm::vec3(0.0f, 2.2f, -10.5f));
  scene->addObject(backpack);
  scene->addObject(ground);

  // scene.addObject("camera");
  return scene->run();
}