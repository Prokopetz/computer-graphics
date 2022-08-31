#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

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

  GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
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

  const char *vertex_shader =
      "#version 410\n"
      "layout(location=0) in vec3 vp;"
      "layout(location=1) in vec3 vc;"
      "out vec3 color;"
      "uniform mat4 matrix;"
      "void main() {"
      "  color = vc;"
      "  gl_Position = matrix * vec4(vp, 1.0);"
      "}";

  const char *fragment_shader =
      "#version 410\n"
      "in vec3 color;"
      "out vec4 frag_color;"
      "void main() {"
      "  frag_color = vec4(color, 1.0);"
      "}";

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  GLuint program = glCreateProgram();
  glAttachShader(program, fs);
  glAttachShader(program, vs);

  glLinkProgram(program);

  glUseProgram(program);
  float matrix[] = {
      1.0f,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      1.0f,
      0.0f,
      0.25f,
      0.25f,
      0.0f,
      1.0f};
  float speedX = 0.5f;
  float speedY = 0.3f;
  float lastPositionX = 0.0f;
  float lastPositionY = 0.0f;
  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int matrixLocation = glGetUniformLocation(program, "matrix");

    glUseProgram(program);
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

    glBindVertexArray(VAO);

    static double previousSeconds = glfwGetTime();
    double currentSeconds = glfwGetTime();
    double elapsedSeconds = currentSeconds - previousSeconds;
    if (elapsedSeconds > 0.008f)
    {
      previousSeconds = currentSeconds;
      if (elapsedSeconds > 0.008)
      {
        previousSeconds = currentSeconds;
        float nX;
        float nY;
        bool collision = false;

        if (lastPositionX + 0.5f > 1.0f) // right
        {
          nX = -1.0f;
          nY = 0.0f;
          collision = true;
        }
        else if (lastPositionY + 0.5f > 1.0f) // top
        {
          nX = 0.0f;
          nY = -1.0f;
          collision = true;
        }
        else if (lastPositionX - 0.5f < -1.0f) // left
        {
          nX = 1.0f;
          nY = 0.0f;
          collision = true;
        }
        else if (lastPositionY - 0.5f < -1.0f) // bottom
        {
          nX = 0.0f;
          nY = 1.0f;
          collision = true;
        }

        if (collision)
        {
          float r2X = -speedX;
          float r2Y = -speedY;
          float a = (nX * r2X + nY * r2Y);
          float routX = 2 * nX * a - r2X;
          float routY = 2 * nY * a - r2Y;
          speedX = routX;
          speedY = routY;
        }

        matrix[12] = elapsedSeconds * speedX + lastPositionX;
        matrix[13] = elapsedSeconds * speedY + lastPositionY;
        lastPositionX = matrix[12];
        lastPositionY = matrix[13];
      }
    }

    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}