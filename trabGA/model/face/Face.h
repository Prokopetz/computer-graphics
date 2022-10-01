
#ifndef FACE_H
#define FACE_H

#include <vector>
#include <iostream>
using namespace std;

class Face
{

private:
  vector<int> vertices = {};
  vector<int> normais = {};
  // vector<int> textures;

public:
  Face();
  ~Face();
  const static int VERTICES = 3;

  void setVertices(vector<int> &vec);
  void setNormais(vector<int> &vec);
  // void setTextures(vector<int> &vec);
  void addVerticeId(int idVertice);
  void addNormalId(int idNormal);
  // void addTextureId(int idTexture);

  vector<int> &getVertices();
  vector<int> &getNormais();
  // vector<int> &getTextures();
};
#endif