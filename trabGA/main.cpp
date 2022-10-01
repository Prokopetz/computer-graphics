// #define SHADER_H

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

// // GLM Includes
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// #include <string>
// #include <fstream>
// #include <sstream>
// #include <iostream>
// #include <map>

// #include "../lib/shader/shader.h"
// #include "../lib/mesh/Mesh.h"
// #include "../lib/objectReader/ObjectReader.h"

// int HEIGHT = 600;
// int WIDTH = 800;
// GLFWwindow *window;
// Shader shader;

// int initGLFW()
// {
//   glfwInit();
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
//   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//   glfwWindowHint(GLFW_SAMPLES, 4);

//   window = glfwCreateWindow(WIDTH, HEIGHT, "Quake", nullptr, nullptr);

//   glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);

//   if (window == nullptr)
//   {
//     std::cout << "Failed to create GLFW Window" << std::endl;
//     glfwTerminate();

//     return EXIT_FAILURE;
//   }

//   glfwMakeContextCurrent(window);

//   glEnable(GL_DEPTH_TEST);
//   glClear(GL_DEPTH_BUFFER_BIT);

//   glewExperimental = GL_TRUE;

//   if (glewInit() != GLEW_OK)
//   {
//     std::cout << "Failed no init GLEW." << std::endl;
//     return EXIT_FAILURE;
//   }

//   glViewport(0, 0, WIDTH, HEIGHT);

//   return EXIT_SUCCESS;
// }

// int setupOpenGL()
// {
//   glEnable(GL_BLEND);
//   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//   glEnable(GL_DEPTH_TEST);

//   return EXIT_SUCCESS;
// }

// int setupShaders()
// {
//   shader = Shader("./vertex.shader", "./fragment.shader");
//   shader.Use();
//   return EXIT_SUCCESS;
// }

// int run(map<string, Mesh *> meshs, map<string, char *> textures, string initial)
// {
//   Mesh *mesh = meshs.find(initial)->second;
//   // char *texturePath = textures.find(initial)->second;

//   shader.Use();
//   // shader.LoadTexture(texturePath, "texture1", "woodTexture");

//   // glm::ortho(0.0f, (float) WIDTH, 0.0f, (float) HEIGHT, 0.1f, 100.0f);

//   glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

//   shader.setMatrix4fv("projection", proj);

//   for (Group *group : mesh->getGroups())
//   {
//     vector<float> vertices;
//     vector<float> normais;
//     vector<float> textures;

//     for (Face *face : group->getFaces())
//     {
//       for (int verticeID : face->getVertices())
//       {
//         glm::vec3 *vertice = mesh->getVertice(verticeID - 1);
//         vertices.push_back(vertice->x);
//         vertices.push_back(vertice->y);
//         vertices.push_back(vertice->z);
//       }

//       for (int normalID : face->getNormals())
//       {
//         glm::vec3 *normal = mesh->getNormal(normalID - 1);
//         normais.push_back(normal->x);
//         normais.push_back(normal->y);
//         normais.push_back(normal->z);
//       }

//       // for (int textureID : face->getTextures())
//       // {
//       //   glm::vec2 *texture = mesh->getTexture(textureID - 1);
//       //   textures.push_back(texture->x);
//       //   textures.push_back(texture->y);
//       // }
//     }

//     GLuint VBOvertices, VBOnormais, VAO;
//     // GLuint VBOtextures;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBOvertices);
//     glGenBuffers(1, &VBOnormais);
//     // glGenBuffers(1, &VBOtextures);

//     // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//     glBindVertexArray(VAO);

//     // Vertices
//     glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
//     glEnableVertexAttribArray(0);

//     // Normais
//     glBindBuffer(GL_ARRAY_BUFFER, VBOnormais);
//     glBufferData(GL_ARRAY_BUFFER, normais.size() * sizeof(float), normais.data(), GL_STATIC_DRAW);

//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
//     glEnableVertexAttribArray(1);

//     // Textures
//     // glBindBuffer(GL_ARRAY_BUFFER, VBOtextures);
//     // glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(float), textures.data(), GL_STATIC_DRAW);

//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
//     glEnableVertexAttribArray(2);

//     group->setVAO(VAO);
//     // glBindVertexArray(0); // Unbind VAO
//   }

//   float camX = 5.0f;
//   float camY = 0.5f;
//   float camZ = 5.0f;

//   float angle = 20.0f;
//   float translateX = 0.0f;
//   float translateY = 0.0f;
//   float translateZ = 0.0f;

//   while (!glfwWindowShouldClose(window))
//   {

//     glfwPollEvents();

// #pragma region Input Handling

//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//     {
//       glfwSetWindowShouldClose(window, GLFW_TRUE);
//     }

//     if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//     {
//       camZ -= 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && camZ > 0)
//     {
//       camZ += 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//     {
//       camX -= 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//     {
//       camX += 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
//     {
//       angle += 0.1f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//     {
//       angle -= 0.1f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
//     {
//       translateX += 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//     {
//       translateX -= 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
//     {
//       translateY += 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
//     {
//       translateY -= 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
//     {
//       translateZ += 0.01f;
//     }

//     if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//     {
//       translateZ -= 0.01f;
//     }

//     // if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
//     // {
//     //   Run(meshs, textures, "trout");
//     // }

//     // if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
//     // {
//     //   Run(meshs, textures, "mesa");
//     // }

//     // if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
//     // {
//     //   cout << "X: " << translateX << " - Y: " << translateY << " - Z: " << translateZ << endl;
//     // }

// #pragma endregion

//     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     shader.Use();

//     glm::mat4 view(1.0f);
//     view = glm::lookAt(glm::vec3(camX, camY, camZ),
//                        glm::vec3(0.0f, 0.0f, 0.0f),
//                        glm::vec3(0.0f, 1.0f, 0.0f));

//     shader.setMatrix4fv("view", view);

//     glm::vec3 lightColor = glm::vec3(0.0f, 1.0f, 0.0f);
//     glm::vec3 lightPos = glm::vec3(-5.0f, -5.0f, -10.0f);
//     glm::vec3 viewPos = glm::vec3(camX, camY, camZ);

//     shader.setVec3("lightColor", lightColor);
//     shader.setVec3("lightPos", lightPos);
//     shader.setVec3("viewPos", viewPos);

//     glm::mat4 model(1.0f);
//     model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
//     model = glm::translate(model, glm::vec3(translateX, translateY, translateZ));

//     shader.setMatrix4fv("model", model);
//     // shader.UseTexture("woodTexture");

//     for (Group *group : mesh->getGroups())
//     {
//       glBindVertexArray(group->getVAO());
//       glDrawArrays(GL_TRIANGLES, 0, group->numVertices());
//       // glBindVertexArray(0);
//     }

//     glfwSwapBuffers(window);
//   }

//   return EXIT_SUCCESS;
// }

// int main(void)
// {
//   initGLFW();
//   setupOpenGL();
//   setupShaders();

//   map<string, Mesh *> meshs;
//   meshs["mesa"] = ObjectReader::read("Objects/mesa01.obj");

//   map<string, char *> textures;
//   textures["mesa"] = (char *)"Objects/mesa01.bmp";
//   run(meshs, textures, "mesa");
//   return EXIT_SUCCESS;
// }