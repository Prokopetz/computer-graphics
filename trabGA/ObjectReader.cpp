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

    face->addVerticeId(v);
  }
  return face;
}

Mesh *ObjectReader::read(string filename)
{
  this->mesh = new Mesh();

  int firstGroup = 1;
  this->group = new Group();

  ifstream arq(filename);

  // cout << "Lendo arquivo: " << filename << endl;

  if (!arq)
  {
    // cout << "- Arquivo de objeto nao encontrado" << endl;
    exit(EXIT_FAILURE);
  }

  // cout << endl;

  while (!arq.eof())
  {
    string line;
    getline(arq, line);

    stringstream sline(line);

    // l� tipo de elemento
    string temp;
    sline >> temp;

    if (temp.empty() || temp == "#")
    {
      continue;
    }

    // cout << "Linha lida: " << line << endl;
    // cout << "- Tipo: " << temp << endl;

    // if (temp == "mtllib")
    // {
    //   material(mesh, sline);
    // }
    if (temp == "v")
    {
      vertice(sline);
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
      Face *face = createFace(sline);
      this->group->addFace(face);
    }
    if (temp == "g")
    {
      if (firstGroup == 1)
      {
        firstGroup = 0;
      }
      else
      {
        mesh->addGroup(this->group);
        this->group = new Group();
      }

      string name;
      sline >> name;
      this->group->setName(name);
    }
    // else if (temp == "usemtl")
    // {
    // }

    // cout << endl;
  }

  arq.close();
  std::cout << "ERROR GROUP" << endl;

  this->mesh->addGroup(this->group);
  return this->mesh;
}

void ObjectReader::vertice(stringstream &sline)
{
  float x, y, z;
  sline >> x >> y >> z;
  std::cout << " " << x << " " << y << " " << z << std::endl;
  mesh->addVertice(new glm::vec3(x, y, z));
}
