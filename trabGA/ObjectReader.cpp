#include "ObjectReader.h"

int getNextTokenValue(stringstream &stoken)
{
  string temp;
  getline(stoken, temp, '/');
  return temp.empty() ? 0 : stoi(temp);
}

Face *createFace(stringstream &sline)
{
  Face *face = new Face();
  string token;
  while (getline(sline, token, ' '))
  {
    if (token.empty())
    {
      continue;
    }

    stringstream stoken(token);

    int v = getNextTokenValue(stoken);
    // int t = getNextTokenValue(stoken);
    // int n = getNextTokenValue(stoken);

    // cout << "  Resultado de " << token << ": " << endl;
    // cout << "   - Vertice: " << v << endl;
    // cout << "   - Textura: " << t << endl;
    // cout << "   - Normal:  " << n << endl;

    face->addVerticeIndex(v - 1);
  }
  return face;
}

glm::vec3 vertice(stringstream &sline)
{
  float x, y, z;
  sline >> x >> y >> z;
  return glm::vec3(x, y, z);
}

Mesh *ObjectReader::read(string filename)
{

  vector<Face *> faces;
  vector<glm::vec3> vertices;

  ifstream arq(filename);

  if (!arq)
  {
    if (this->_debug)
      cout << "ERRO - Arquivo de objeto nao encontrado" << endl;

    exit(EXIT_FAILURE);
  }

  while (!arq.eof())
  {
    string line;
    getline(arq, line);

    stringstream sline(line);

    string temp;
    sline >> temp;

    if (temp.empty() || temp == "#")
    {
      continue;
    }

    if (this->_debug)
    {
      cout << "Linha lida..." << endl;
    }

    // if (temp == "mtllib")
    // {
    //   material(mesh, sline);
    // }
    if (temp == "v")
    {
      if (this->_debug)
      {
        cout << "Cria vertice: " << sline.str() << endl;
      }
      vertices.push_back(vertice(sline));
    }
    // if (temp == "vn")
    // {
    //   normal(mesh, sline);
    // }
    // if (temp == "vt")
    // {
    //   texture(mesh, sline);
    // }
    if (temp == "f")
    {
      if (this->_debug)
      {
        cout << "Cria face: " << sline.str() << endl;
      }
      faces.push_back(createFace(sline));
    }
    if (temp == "g")
    {
      string name;
      sline >> name;
    }
  }

  arq.close();

  return new Mesh(vertices, faces);
}
