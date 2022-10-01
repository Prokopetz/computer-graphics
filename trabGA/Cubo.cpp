#include "Cubo.h"

Cubo::Cubo(int width, int height, std::string screenTitle)
{
  this->WIDTH = width;
  this->HEIGHT = height;
  this->SCREEN_TITLE = screenTitle;
}

Cubo::~Cubo() {}

Face *createFace(int v0, int v1, int v2, int v3, int normal)
{
  Face *face = new Face();
  face->addVerticeId(v0);
  face->addVerticeId(v1);
  face->addVerticeId(v3);

  face->addVerticeId(v1);
  face->addVerticeId(v2);
  face->addVerticeId(v3);
  return face;
}

int Cubo::init(GLFWwindow *window)
{

  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // glfwSetCursorPosCallback(window, mouse_callback);
  // glfwSetScrollCallback(window, scroll_callback);

  this->mesh = new Mesh();
  int A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7;
  float escale = 2;

  this->mesh->addVertice(new glm::vec3(1.0f / escale, 1.0f / escale, 1.0f / escale));    // A
  this->mesh->addVertice(new glm::vec3(-1.0f / escale, 1.0f / escale, 1.0f / escale));   // B
  this->mesh->addVertice(new glm::vec3(-1.0f / escale, -1.0f / escale, 1.0f / escale));  // C
  this->mesh->addVertice(new glm::vec3(1.0f / escale, -1.0f / escale, 1.0f / escale));   // D
  this->mesh->addVertice(new glm::vec3(1.0f / escale, 1.0f / escale, -1.0f / escale));   // E
  this->mesh->addVertice(new glm::vec3(-1.0f / escale, 1.0f / escale, -1.0f / escale));  // F
  this->mesh->addVertice(new glm::vec3(-1.0f / escale, -1.0f / escale, -1.0f / escale)); // G
  this->mesh->addVertice(new glm::vec3(1.0f / escale, -1.0f / escale, -1.0f / escale));  // H

  Group *group = new Group();
  group->addFace(createFace(A, B, C, D, 4));
  group->addFace(createFace(A, D, H, E, 0));
  group->addFace(createFace(A, E, F, B, 2));
  group->addFace(createFace(C, B, F, G, 1));
  group->addFace(createFace(D, C, G, H, 3));
  group->addFace(createFace(H, G, F, E, 5));

  /*      |
          |
     A----|---D
    /+    |  /+
   / +    | / +
  B-------|C  +
  +  +    |+  +
  +  E----|+--H
  + /     |+ /
  +/      |+/
  F-------|G
          |
          |
          |
          |
  */

  this->mesh->addGroup(group);

  Shader shader = Shader("./trabGA/vertex.shader", "./trabGA/fragment.shader");
  shader.use();

  glm::ortho(0.0f, 600.0f, 0.0f, 600.0f, 0.1f, 100.0f);

  this->cubePositions.push_back(new glm::vec3(0.0f, 0.0f, 0.0f));
  this->cubePositions.push_back(new glm::vec3(2.0f, 5.0f, -15.0f));
  this->cubePositions.push_back(new glm::vec3(-1.5f, -2.2f, -2.5f));
  this->cubePositions.push_back(new glm::vec3(-3.8f, -2.0f, -12.3f));
  this->cubePositions.push_back(new glm::vec3(2.4f, -0.4f, -3.5f));
  this->cubePositions.push_back(new glm::vec3(-1.7f, 3.0f, -7.5f));
  this->cubePositions.push_back(new glm::vec3(1.3f, -2.0f, -2.5f));
  this->cubePositions.push_back(new glm::vec3(1.5f, 2.0f, -2.5f));
  this->cubePositions.push_back(new glm::vec3(1.5f, 0.2f, -1.5f));
  this->cubePositions.push_back(new glm::vec3(-1.3f, 1.0f, -1.5f));

  for (Group *group : this->mesh->getGroups())
  {
    vector<float> vertices;

    // for (Face *face : group->getFaces())
    // {
    //   for (int verticeID : face->getVertices())
    //   {
    //     glm::vec3 *vertice = this->mesh->vertice(verticeID);
    //     vertices.push_back(vertice->x);
    //     vertices.push_back(vertice->y);
    //     vertices.push_back(vertice->z);

    //     group->numVertices();
    //   }
    // }

    GLuint VAO, VBOvert;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBOvert);

    glBindBuffer(GL_ARRAY_BUFFER, VBOvert);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);

    group->setVAO(VAO);
  }

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  return EXIT_SUCCESS;
}

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 600.0f / 2.0f;
float lastY = 600.0f / 2.0f;
float pitch = 0.0f, yaw = -90.0f;
bool firstMouse = true;
float fov = 45.0f;

void Cubo::run(GLFWwindow *window)
{
  float currentFrame = glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  // processInput(window);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 projection(1.0f);
  projection = glm::perspective(glm::radians(fov), (float)this->WIDTH / (float)this->HEIGHT, 0.1f, 100.0f);

  glm::mat4 view(1.0f);
  view = glm::lookAt(cameraPos,
                     cameraPos + cameraFront,
                     cameraUp);

  for (int i = 0; i < cubePositions.size(); i++)
  {
    glm::vec3 cubePosition = *cubePositions[i];
    glm::mat4 model(1.0f);
    model = glm::translate(model, cubePosition);
    float angle = 20.0f * (i + 1);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

    shader->use();
    for (Group *group : this->mesh->getGroups())
    {
      shader->setMatrix4fv("model", model);
      shader->setMatrix4fv("view", view);
      shader->setMatrix4fv("projection", projection);
      glBindVertexArray(group->getVAO());
      glDrawArrays(GL_TRIANGLES, 0, group->numVertices());
    }

    shader->use();
    for (Group *group : this->mesh->getGroups())
    {
      shader->setMatrix4fv("model", model);
      shader->setMatrix4fv("view", view);
      shader->setMatrix4fv("projection", projection);
      glBindVertexArray(group->getVAO());
      glDrawArrays(GL_LINE_LOOP, 0, group->numVertices());
    }
  }
}

// bool Cubo::keepRunning(GLFWwindow *window)
// {
//   return !glfwWindowShouldClose(window);
// }

// void Cubo::processInput(GLFWwindow *window)
// {
//   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//   {
//     glfwSetWindowShouldClose(window, true);
//   }

//   float cameraSpeed = 5.0f * deltaTime;
//   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//   {
//     cameraPos += cameraSpeed * cameraFront;
//   }
//   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//   {
//     cameraPos -= cameraSpeed * cameraFront;
//   }
//   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//   {
//     cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//   }
//   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//   {
//     cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//   }
// }

// void Cubo::mouse_callback(GLFWwindow *window, double xpos, double ypos)
// {
//   if (firstMouse)
//   {
//     lastX = xpos;
//     lastY = ypos;
//     firstMouse = false;
//   }

//   float xoffset = xpos - lastX;
//   float yoffset = lastY - ypos;
//   lastX = xpos;
//   lastY = ypos;

//   float sensitivity = 0.05;
//   xoffset *= sensitivity;
//   yoffset *= sensitivity;

//   yaw += xoffset;
//   pitch += yoffset;

//   if (pitch > 89.0f)
//     pitch = 89.0f;
//   if (pitch < -89.0f)
//     pitch = -89.0f;

//   glm::vec3 front;
//   front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//   front.y = sin(glm::radians(pitch));
//   front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//   cameraFront = glm::normalize(front);
// }

// void Cubo::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
// {
//   if (fov >= 1.0f && fov <= 45.0f)
//     fov -= yoffset;
//   if (fov <= 1.0f)
//     fov = 1.0f;
//   if (fov >= 45.0f)
//     fov = 45.0f;
// }

void Cubo::finish()
{
  delete this->mesh;
}

int Cubo::width()
{
  return this->WIDTH;
}

int Cubo::height()
{
  return this->HEIGHT;
}

std::string Cubo::screenTitle()
{
  return this->SCREEN_TITLE;
}