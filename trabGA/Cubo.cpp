#include "Cubo.h"

Face *Cubo::createFace(int v0, int v1, int v2, int v3, int normal)
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

Cubo::Cubo()
{
  this->_mesh = new Mesh();
  int A = 0, B = 1, C = 2, D = 3, E = 4, F = 5, G = 6, H = 7;
  float escale = 4;

  this->_mesh->addVertice(new glm::vec3(1.0f / escale, 1.0f / escale, 1.0f / escale));    // A
  this->_mesh->addVertice(new glm::vec3(-1.0f / escale, 1.0f / escale, 1.0f / escale));   // B
  this->_mesh->addVertice(new glm::vec3(-1.0f / escale, -1.0f / escale, 1.0f / escale));  // C
  this->_mesh->addVertice(new glm::vec3(1.0f / escale, -1.0f / escale, 1.0f / escale));   // D
  this->_mesh->addVertice(new glm::vec3(1.0f / escale, 1.0f / escale, -1.0f / escale));   // E
  this->_mesh->addVertice(new glm::vec3(-1.0f / escale, 1.0f / escale, -1.0f / escale));  // F
  this->_mesh->addVertice(new glm::vec3(-1.0f / escale, -1.0f / escale, -1.0f / escale)); // G
  this->_mesh->addVertice(new glm::vec3(1.0f / escale, -1.0f / escale, -1.0f / escale));  // H

  Group *group = new Group();
  group->addFace(createFace(A, B, C, D, 4));
  group->addFace(createFace(A, D, H, E, 0));
  group->addFace(createFace(A, E, F, B, 2));
  group->addFace(createFace(C, B, F, G, 1));
  group->addFace(createFace(D, C, G, H, 3));
  group->addFace(createFace(H, G, F, E, 5));

  this->_mesh->addGroup(group);

  for (Group *group : this->_mesh->getGroups())
  {
    vector<float> vertices;

    for (Face *face : group->getFaces())
    {
      for (int verticeID : face->getVertices())
      {
        glm::vec3 *vertice = this->_mesh->vertice(verticeID);
        vertices.push_back(vertice->x);
        vertices.push_back(vertice->y);
        vertices.push_back(vertice->z);

        group->numVertices();
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

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void *Cubo::draw()
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

void *Cubo::setPosition(glm::vec3 position)
{
  this->position = position;
}