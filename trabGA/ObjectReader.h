#ifndef OBJECT_READER_H
#define OBJECT_READER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include "Mesh.h"

class ObjectReader
{
public:
  Mesh *mesh;
  Group *group;
  Mesh *read(string filename);
  void vertice(stringstream &sline);
  void face(stringstream &sline);
};

#endif