
#ifndef FACE_H
#define FACE_H

#include <vector>
#include <iostream>
using namespace std;

class Face
{

private:
  vector<int> vertices = {};

public:
  Face();
  ~Face();

  void addVerticeIndex(int verticeIndex);

  vector<int> getVertices();
};
#endif