#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

int HEIGHT = 600;
int WIDTH = 800;
GLFWwindow *window;

int initGLFW()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Quake", nullptr, nullptr);

  glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);

  if (window == nullptr)
  {
    std::cout << "Failed to create GLFW Window" << std::endl;
    glfwTerminate();

    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);

  glEnable(GL_DEPTH_TEST);
  glClear(GL_DEPTH_BUFFER_BIT);

  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed no init GLEW." << std::endl;
    return EXIT_FAILURE;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  return EXIT_SUCCESS;
}

int setupOpenGL()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);

  return EXIT_SUCCESS;
}
