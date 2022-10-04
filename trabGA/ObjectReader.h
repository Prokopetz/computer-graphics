#ifndef OBJECT_READER_H
#define OBJECT_READER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "Mesh.h"
#include "Face.h"

class ObjectReader
{
private:
  bool _debug = false;

public:
  Mesh *read(string filename);
};

#endif