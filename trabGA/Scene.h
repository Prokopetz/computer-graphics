#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <string>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Scene
{
  
private:
  GLint WIDTH, HEIGHT;
  std::string SCREEN_TITLE;
  GLuint program;
  GLFWwindow* window;

public:
  Scene(int width, int height, std::string title);
  int init();
  int run();
  void addObject();

};

#endif