#include "Group.h"

Group::Group()
{
}

Group::~Group()
{
  this->faces.clear();
  this->faces.shrink_to_fit();

  glDeleteVertexArrays(1, &vao);
  for (auto &vbo : this->vbos)
  {
    glDeleteBuffers(1, &vbo);
  }

  this->vbos.clear();
  this->vbos.shrink_to_fit();
}

int Group::numVertices()
{
  return faces.size() * Face::VERTICES;
}

void Group::bindVAO()
{
  if (this->vao == NULL)
  {
    glGenVertexArrays(1, &vao);
  }
  glBindVertexArray(vao);
}

// void Group::bindTexture()
// {
//   if (this->texture == NULL)
//   {
//     return;
//   }
//   // glActiveTexture(GL_TEXTURE0);
//   glBindTexture(GL_TEXTURE_2D, texture);
// }

// GLuint Group::getTexture()
// {
//   return this->texture;
// }

void Group::bindBuffer(const vector<float> &data, const int vecSize)
{
  if (data.empty())
  {
    return;
  }

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.front(), GL_STATIC_DRAW);

  glVertexAttribPointer(shaderLocation, vecSize, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(shaderLocation);

  shaderLocation++;
  this->addVBO(vbo);
}

// void Group::setTexture(string filename)
// {
//   glGenTextures(1, &texture);
//   glBindTexture(GL_TEXTURE_2D, texture);

//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//   int width, height, nrChannels;

//   unsigned char *imageData = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

//   if (imageData)
//   {
//     GLenum format;
//     if (nrChannels == 1)
//     {
//       format = GL_RED;
//     }
//     else if (nrChannels == 3)
//     {
//       format = GL_RGB;
//     }
//     else if (nrChannels == 4)
//     {
//       format = GL_RGBA;
//     }
//     glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
//     glGenerateMipmap(GL_TEXTURE_2D);
//   }
//   else
//   {
//     std::cout << "Failed to load texture" << std::endl;
//   }

//   stbi_image_free(imageData);
//   this->addVBO(texture);
// }

void Group::setName(string newName)
{
  this->name = newName;
}

string Group::getName()
{
  return this->name;
}

vector<Face *> &Group::getFaces()
{
  return this->faces;
}

void Group::addFace(Face *face)
{
  this->faces.push_back(face);
}

void Group::addVBO(GLuint vbo)
{
  this->vbos.push_back(vbo);
}

// void Group::setMaterialName(string material)
// {
//   this->material = material;
// }

// string Group::getMaterialName()
// {
//   return this->material;
// }