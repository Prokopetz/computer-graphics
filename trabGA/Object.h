#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "Mesh.h"

class Object
{
  public:
    virtual ~Object() {};
    virtual Mesh* mesh() = 0;
    virtual glm::mat4* transform() = 0;
};

#endif