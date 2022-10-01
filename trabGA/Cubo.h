#ifndef CUBO_H
#define CUBO_H
#include "./model/mesh/Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Cubo
{

private:
  GLint WIDTH, HEIGHT;
  std::string SCREEN_TITLE;
  vector<glm::vec3 *> cubePositions;
  Shader *shader;

  Mesh *mesh;

  static void processInput(GLFWwindow *window);
  static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
  static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

public:
  Cubo(int width, int height, std::string screenTitle);
  ~Cubo();
  int init(GLFWwindow *window);
  void run(GLFWwindow *window);
  bool keepRunning(GLFWwindow *window);
  void finish();
  int width();
  int height();
  std::string screenTitle();
};

#endif