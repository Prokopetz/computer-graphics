#include "CuboDois.h"

CuboDois::CuboDois(Mesh *mesh)
{
  this->_mesh = mesh;
  this->_mesh->prepare();
}

void *CuboDois::draw()
{
  for (int i = 0; i < this->_mesh->getGroups().size(); i++)
  {
    for (Group *group : this->_mesh->getGroups())
    {
      glBindVertexArray(group->getVAO());
      glDrawArrays(GL_TRIANGLES, 0, group->getNumVertices());
    }
  }
}

void *CuboDois::setPosition(glm::vec3 position)
{
  this->position = position;
}
