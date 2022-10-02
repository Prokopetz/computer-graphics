#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include "Scene.h"
#include "Cubo.h"
#include "CuboDois.h"
#include "ObjectReader.h"

int main()
{
  // start GL context and O/S window using the GLFW helper library

  Scene *scene = new Scene(800, 600, "Quake");

  scene->init();
  // scene->addObject(new Cubo());
  // Cubo *cubo = new Cubo();
  // cubo->setPosition(glm::vec3(3.0f, 1.0f, 1.0f));
  // scene->addObject(cubo);

  // Cubo *cubo2 = new Cubo();
  // scene->addObject(cubo2);

  ObjectReader *reader = new ObjectReader();
  CuboDois *cubo3 = new CuboDois(reader->read("./trabGA/trout.obj"));
  cubo3->setPosition(glm::vec3(0.8f, 1.2f, -1.0f));
  scene->addObject(cubo3);

  // scene.addObject("camera");
  return scene->run();
}