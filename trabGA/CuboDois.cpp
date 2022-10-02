#include "CuboDois.h"

CuboDois::CuboDois(Mesh *mesh)
{
  this->_mesh = mesh;
  for (Group *group : this->_mesh->getGroups())
  {
    std::cout << "SAI" << std::endl;

    vector<float> vertices;

    for (Face *face : group->getFaces())
    {
      std::cout << "FACE" << std::endl;

      for (int verticeID : face->getVertices())
      {

        glm::vec3 *vertice = this->_mesh->vertice(verticeID);
        vertices.push_back(vertice->x);
        vertices.push_back(vertice->y);
        vertices.push_back(vertice->z);
      }
    }
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
  std::cout << "SAI2" << std::endl;
}

void *CuboDois::draw()
{
  for (int i = 0; i < this->_mesh->getGroups().size(); i++)
  {
    for (Group *group : this->_mesh->getGroups())
    {
      glBindVertexArray(group->getVAO());
      glDrawArrays(GL_TRIANGLES, 0, group->numVertices());
    }
  }
}

void *CuboDois::setPosition(glm::vec3 position)
{
  this->position = position;
}
