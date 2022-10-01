#define FACE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

class Face
{

private:
  vector<int> vertices;
  vector<int> normals;
  vector<int> textures;

public:
  Face();
  ~Face();

  void setVertices(vector<int> &vec);
  void setNormals(vector<int> &vec);
  void setTextures(vector<int> &vec);
  void addVerticeId(int idVertice);
  void addNormalId(int idNormal);
  void addTextureId(int idTexture);

  vector<int> &getVertices()
  {
    return vertices;
  }

  vector<int> &getNormals()
  {
    return normals;
  }

  vector<int> &getTextures()
  {
    return textures;
  }
};