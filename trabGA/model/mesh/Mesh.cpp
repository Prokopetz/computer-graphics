#include "Mesh.h"

Mesh::Mesh(string name)
{
  this->name = name;
}

Mesh::~Mesh()
{
  this->groups.clear();
  this->normais.clear();
  this->vertices.clear();
  this->normais.clear();
}

glm::vec3 *Mesh::vertice(int id)
{
  return this->vertices[id];
}

glm::vec3 *Mesh::normal(int id)
{
  return this->normais[id];
}

glm::vec2 *Mesh::texture(int id)
{
  return this->textures[id];
}

void Mesh::setName(string name)
{
  this->name = name;
}

// void Mesh::setMaterialsFile(string materialsFile)
// {
//   this->materialsFile = materialsFile;
// }

// Material *Mesh::getMaterial(string materialName)
// {
//   if (materialsHandler == nullptr)
//   {
//     materialsHandler = new MaterialHandler();
//   }
//   return this->materialsHandler->getMaterial(materialName);
// }

// void Mesh::setMaterialHandler(MaterialHandler *handler)
// {
//   this->materialsHandler = handler;
// }

int Mesh::addGroup(Group *group)
{
  this->groups.push_back(group);
  return this->groups.size() - 1;
}

int Mesh::addVertice(glm::vec3 *vertice)
{
  this->vertices.push_back(vertice);
  return this->vertices.size() - 1;
}

int Mesh::addNormal(glm::vec3 *normal)
{
  this->normais.push_back(normal);
  return this->normais.size() - 1;
}

// int Mesh::addTexture(glm::vec2 *texture)
// {
//   this->textures.push_back(texture);
//   return this->textures.size() - 1;
// }

void Mesh::setTextures(vector<glm::vec2 *> &textures)
{
  this->textures = textures;
}

vector<Group *> &Mesh::getGroups()
{
  return groups;
}

// string Mesh::getMaterialsFile()
// {
//   return this->materialsFile;
// }

void Mesh::prepare()
{
  for (Group *group : this->getGroups())
  {
    vector<float> vertices;
    vector<float> normais;
    vector<float> textures;
    for (Face *face : group->getFaces())
    {

      // TODO the below code for vertices and normais are equal, and the only thing different for texture
      //      is that only it ignores Z coordinate. The goal is try to do only 1 method for this logic.

      for (int verticeID : face->getVertices())
      {
        glm::vec3 *vertice = this->vertice(verticeID);
        vertices.push_back(vertice->x);
        vertices.push_back(vertice->y);
        vertices.push_back(vertice->z);
      }

      for (int normalID : face->getNormais())
      {
        glm::vec3 *normal = this->normal(normalID);
        normais.push_back(normal->x);
        normais.push_back(normal->y);
        normais.push_back(normal->z);
      }

      // for (int textureID : face->getTextures())
      // {
      //   glm::vec2 *texture = this->texture(textureID);
      //   textures.push_back(texture->x);
      //   textures.push_back(texture->y);
      // }
    }

    group->bindVAO();
    group->bindBuffer(vertices);
    group->bindBuffer(normais);
    // group->bindBuffer(textures, 2);

    // if (group->getMaterialName() != "")
    // {
    //   Material *material = getMaterial(group->getMaterialName());
    //   if (material->getTextureName() != "")
    //   {
    //     group->setTexture(material->getTextureName());
    //   }
    // }
  }
}