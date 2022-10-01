#include "Face.h"

Face::Face() {}

Face::~Face()
{
  vertices.clear();
  vertices.shrink_to_fit();

  normais.clear();
  normais.shrink_to_fit();

  // textures.clear();
  // textures.shrink_to_fit();
}

void Face::setVertices(vector<int> &vec)
{
  this->vertices = vec;
}

void Face::setNormais(vector<int> &vec)
{
  this->normais = vec;
}

// void Face::setTextures(vector<int> &vec)
// {
//   this->textures = vec;
// }

void Face::addVerticeId(int idVertice)
{
  this->vertices.push_back(idVertice);
}

void Face::addNormalId(int idNormal)
{
  this->normais.push_back(idNormal);
}

// void Face::addTextureId(int idTexture)
// {
//   this->textures.push_back(idTexture);
// }

vector<int> &Face::getVertices()
{
  return vertices;
}

vector<int> &Face::getNormais()
{
  return normais;
}

// vector<int> &Face::getTextures()
// {
//   return textures;
// }