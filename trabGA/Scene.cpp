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
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
  {
    this->camera->rotateRight();
  }
  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
  {
    this->camera->rotateLeft();
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    std::cout << "New bullet" << std::endl;
    objects.push_back(this->bulletCreator->createBullet());
    std::cout << "added" << std::endl;
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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

  if (glewInit() != GLEW_OK)
  {
    std::cout << "Failed no init GLEW." << std::endl;
    return EXIT_FAILURE;
  }

  glewExperimental = GL_TRUE;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  // glFrontFace(GL_CCW);

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);

  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
  this->shader = new Shader("./trabGA/vertex.shader", "./trabGA/fragment.shader");
  this->camera = new Camera(this->WIDTH, this->HEIGHT, this->shader);
  this->bulletCreator = new BulletCreator(camera, shader->program);
}

int Scene::run()
{
  while (!glfwWindowShouldClose(this->window))
  {
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->processInput();
    this->camera->updateCamera();

    for (Object *object : this->objects)
    {
      if (object->shouldRender())
      {
        this->shader->use();

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, glm::radians(object->getRotationDegrees()), object->getRotation());
        trans = glm::scale(trans, object->getScale());
        trans = glm::translate(trans, object->getPosition());
        this->shader->setMatrix4fv("model", trans);
        object->draw();
      }
    }

    int pos = 1;
    for (Object *obj1 : this->objects)
    {
      for (Object *obj2 : this->objects)
      {
        if (obj1 != obj2)
        {
          if (obj1->hasCollision() && obj2->hasCollision())
          {
            if (this->checkCollision(obj1, obj2))
            {
              obj1->onCollision(obj2);
              obj2->onCollision(obj1);
            }
          }
        }
      }
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

bool Scene::checkCollision(Object *one, Object *two)
{
  bool collisionX = one->getPosition().x + one->getColliderSize().x >= two->getPosition().x &&
                    two->getPosition().x + two->getColliderSize().x >= one->getPosition().x;
  bool collisionY = one->getPosition().z + one->getColliderSize().y >= two->getPosition().z &&
                    two->getPosition().z + two->getColliderSize().y >= one->getPosition().z;
  return collisionX && collisionY;
}