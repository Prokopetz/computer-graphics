
#include "Face.h"

Face::Face() {}

Face::~Face()
{
  vertices.clear();
  normals.clear();
  textures.clear();
}

void Face::setVertices(vector<int> &vec)
{
  this->vertices = vec;
}

void Face::setNormals(vector<int> &vec)
{
  this->normals = vec;
}

void Face::setTextures(vector<int> &vec)
{
  this->textures = vec;
}

void Face::addVerticeId(int idVertice)
{
  this->vertices.push_back(idVertice);
}

void Face::addNormalId(int idNormal)
{
  this->normals.push_back(idNormal);
}

void Face::addTextureId(int idTexture)
{
  this->textures.push_back(idTexture);
}

vector<int> &Face::getVertices()
{
  return vertices;
}

vector<int> &Face::getNormals()
{
  return normals;
}

vector<int> &Face::getTextures()
{
  return textures;
}