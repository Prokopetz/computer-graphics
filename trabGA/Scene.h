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

#include "Object.h"
#include "Camera.h"
#include "Shader.h"
#include "Bullet.h"
#include "Player.h"
#include "BulletCreator.h"

class Scene
{

private:
  GLint WIDTH, HEIGHT;
  std::string SCREEN_TITLE;
  GLuint program;
  GLFWwindow *window;
  vector<Object *> objects = {};
  BulletCreator *bulletCreator;
  Player* player;

  bool checkCollision(Object *one, Object *two);

public:
  Shader *shader;
  Scene(int width, int height, std::string title);
  Camera *camera;
  int init();
  int run();
  void addObject(Object *object);
  void addPlayer(Player *player);

private:
  void processInput();
};

#endif