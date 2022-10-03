#include "Mesh.h"

Mesh::Mesh(vector<glm::vec3> vertices, vector<glm::vec2> texCoords, vector<Face *> faces)
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

  unsigned int VBOtextures, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBOtextures);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  // Texture
  glBindBuffer(GL_ARRAY_BUFFER, VBOtextures);
  glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*) 0);
  glEnableVertexAttribArray(1);


  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void Mesh::draw()
{
  glBindTexture(GL_TEXTURE_2D, this->texture->getTextureId());
  glBindVertexArray(VAO);
  cout << indices.size() << endl;
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

void Mesh::setTexture(Texture* texture) {
  this->texture = texture;
}