#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include "Scene.h"

int main()
{
  // start GL context and O/S window using the GLFW helper library

  Scene* scene = new Scene(600, 600, "Quake");

  scene->init();
  // scene.addObject("camera");
  return scene->run();
  
}