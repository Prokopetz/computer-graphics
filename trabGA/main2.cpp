#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include "Shader.h"
#include "Cubo.h"

int main()
{
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Quake", NULL, NULL);
  if (!window)
  {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  GLfloat vertices[] = {
      // Positions          // Colors
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // Bottom Right
      -0.5f, -0.5f, -0.0f, 0.0f, 0.0f, 1.0f, // Bottom Left
      0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f     // Top
  };

  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
               vertices, GL_STATIC_DRAW);
  // Posições:
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(GLfloat), (GLvoid *)0);
  glEnableVertexAttribArray(0);
  // Cores:
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  Shader shader = Shader("./trabGA/vertex.shader", "./trabGA/fragment.shader");
  shader.use();

  Cubo *cubo = new Cubo(600, 800, "Quake");
  while (!glfwWindowShouldClose(window))
  {
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // int matrixLocation = glGetUniformLocation(shader.program, "matrix");

    // glUseProgram(shader.program);
    // glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

    // glBindVertexArray(VAO);

    // glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

    // glDrawArrays(GL_TRIANGLES, 0, 3);

    // glfwSwapBuffers(window);
    // glfwPollEvents();
    cubo->run(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}