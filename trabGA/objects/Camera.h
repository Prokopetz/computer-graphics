
#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include <vector>
#include <iostream>

#include "../models/Shader.h"

using namespace std;

class Camera
{

private:
  float yaw = -90.0f;
  float cameraSpeed = 0.1f;
  glm::mat4 projection;
  glm::mat4 view;
  Shader *shader;
  int WIDTH;
  int HEIGHT;

public:
  Camera(int width, int height, Shader *shader)
  {
    this->WIDTH = width;
    this->HEIGHT = height;
    this->shader = shader;
  };
  ~Camera();

  glm::vec3 cameraPosition = glm::vec3(0.0f, 3.0f, 0.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

  void updateCamera();
  void moveForward();
  void moveLeft();
  void moveRight();
  void moveBackward();
  void rotateRight();
  void rotateLeft();
};
#endif