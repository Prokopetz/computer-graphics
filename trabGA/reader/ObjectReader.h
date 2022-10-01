#ifndef OBJ_READER_H
#define OBJ_READER_H

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <map>
#include "./model/mesh/Mesh.h"

using namespace std;

static map<string, Mesh *> meshes;

class ObjectReader
{

private:
public:
  ObjectReader();
  ~ObjectReader();
  Mesh *read(string filename);
};
#endif