#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include "Scene.h"

void Scene::processInput()
{
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    this->camera->moveForward();
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    this->camera->moveBackward();
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    this->camera->moveLeft();
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    this->camera->moveRight();
  }
}

Scene::Scene(int width, int height, std::string title)
{
  this->WIDTH = width;
  this->HEIGHT = height;
  this->SCREEN_TITLE = title;
}

int Scene::init()
{
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window = glfwCreateWindow(this->WIDTH, this->HEIGHT, this->SCREEN_TITLE.c_str(), NULL, NULL);
  glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!this->window)
  {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(this->window);
  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_DEPTH_TEST);
  glClear(GL_DEPTH_BUFFER_BIT);

  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed no init GLEW." << std::endl;
    return EXIT_FAILURE;
  }

  // glViewport(0, 0, this->WIDTH, this->HEIGHT);

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);

  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
  this->shader = new Shader("./trabGA/vertex.shader", "./trabGA/fragment.shader");
  this->camera = new Camera(this->WIDTH, this->HEIGHT, this->shader);
}

int Scene::run()
{
  while (!glfwWindowShouldClose(this->window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->processInput();

    for (Object *object : this->objects)
    {
      this->camera->updateCamera();
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, object->getPosition());
      this->shader->setMatrix4fv("model", model);
      object->draw();
    }
    glfwSwapBuffers(this->window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void Scene::addObject(Object *object)
{
  this->objects.push_back(object);
}
