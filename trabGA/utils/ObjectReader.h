#ifndef OBJECT_READER_H
#define OBJECT_READER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "../models/Mesh.h"
#include "../models/Face.h"

class ObjectReader
{
private:
  bool _debug = false;

public:
  Mesh *read(string filename);
};

#endif