#include "Mesh.h"

Mesh::Mesh(vector<glm::vec3> vertices, vector<Face *> faces)
{
  this->vertices = vertices;
  this->faces = faces;

  for (Face *face : faces)
  {
    for (int verticeIndex : face->getVertices())
    {
      this->indices.push_back(verticeIndex);
    }
  }

  unsigned int VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void Mesh::draw()
{
  glBindVertexArray(VAO);
  cout << indices.size() << endl;
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}