#include "Face.h"

Face::Face() {}

void Face::addVerticeIndex(int verticeIndex)
{
  this->vertices.push_back(verticeIndex);
}

vector<int> Face::getVertices()
{
  return this->vertices;
}