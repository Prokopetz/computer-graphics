#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

#include "Scene.h"
#include "CuboDois.h"
#include "ObjectReader.h"
#include "Face.h"
#include "stb_image.h"

Face *createFace(int v1, int v2, int v3, int v4)
{
  Face *face = new Face();
  face->addVerticeIndex(v1);
  face->addVerticeIndex(v2);
  face->addVerticeIndex(v3);

  face->addVerticeIndex(v1);
  face->addVerticeIndex(v4);
  face->addVerticeIndex(v3);
  return face;
}

int main()
{
  // start GL context and O/S window using the GLFW helper library

  Scene *scene = new Scene(800, 600, "Quake");

  scene->init();
  // scene->addObject(new Cubo());
  // Cubo *cubo = new Cubo();
  // cubo->setPosition(glm::vec3(3.0f, 1.0f, 1.0f));
  // scene->addObject(cubo);

  // Cubo *cubo2 = new Cubo();
  // scene->addObject(cubo2);

  // float escale = 2;

  // int A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7;

  // vector<glm::vec3> vertices;
  // vertices.push_back(glm::vec3(1.0f / escale, 1.0f / escale, 1.0f / escale));
  // vertices.push_back(glm::vec3(-1.0f / escale, 1.0f / escale, 1.0f / escale));   // B
  // vertices.push_back(glm::vec3(-1.0f / escale, -1.0f / escale, 1.0f / escale));  // C
  // vertices.push_back(glm::vec3(1.0f / escale, -1.0f / escale, 1.0f / escale));   // D
  // vertices.push_back(glm::vec3(1.0f / escale, 1.0f / escale, -1.0f / escale));   // E
  // vertices.push_back(glm::vec3(-1.0f / escale, 1.0f / escale, -1.0f / escale));  // F
  // vertices.push_back(glm::vec3(-1.0f / escale, -1.0f / escale, -1.0f / escale)); // G
  // vertices.push_back(glm::vec3(1.0f / escale, -1.0f / escale, -1.0f / escale));  // H

  // vector<Face *> faces;
  // faces.push_back(createFace(A, B, C, D));
  // faces.push_back(createFace(A, E, H, D));
  // faces.push_back(createFace(A, E, F, B));
  // faces.push_back(createFace(B, F, G, C));
  // faces.push_back(createFace(C, G, H, D));
  // faces.push_back(createFace(E, F, G, H));

  // Mesh *mesh = new Mesh(vertices, faces);

  // CuboDois *cubo = new CuboDois(mesh);

  ObjectReader *reader = new ObjectReader();
  int width, height, nrChannels;
  unsigned char *data = stbi_load("./trabGA/assets/mesa01.bmp", &width, &height, &nrChannels, 0);
  CuboDois *cubo3 = new CuboDois(reader->read("./trabGA/assets/mesa01.obj"));
  cubo3->setPosition(glm::vec3(0.8f, -3.0f, -1.0f));
  // scene->addObject(cubo);
  scene->addObject(cubo3);

  // scene.addObject("camera");
  return scene->run();
}