#include "NewObjectReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

NewMesh* NewObjectReader::read(string filename)
{
	NewMesh* mesh = new NewMesh();

	int firstGroup = 1;
	NewGroup* group = new NewGroup();
	group->setName("default");

	ifstream arq(filename);

	if (!arq) {
		exit(EXIT_FAILURE);
	}

	while (!arq.eof()) {
		string line;
		getline(arq, line);

		stringstream sline(line);

		string temp;
		sline >> temp;

		if (temp.empty() || temp == "#") {
			continue;
		}

		if (temp == "mtllib") {
			material(mesh, sline);
		} else if (temp == "v") {
			vertice(mesh, sline);
		}
		else if (temp == "vn") {
			normal(mesh, sline);
		}
		else if (temp == "vt") {
			texture(mesh, sline);
		}
		else if (temp == "f") {
			face(group, sline);
		}
		else if (temp == "g") {
			if (firstGroup == 1) {
				firstGroup = 0;
			}
			else {
				mesh->addGroup(group);
				group = new NewGroup();
			}

			string name;
			sline >> name;
			group->setName(name);
		}
		else if (temp == "usemtl") {
			usemtl(group, sline);
		}

	}

	arq.close();

	mesh->addGroup(group);
	return mesh;
}

void NewObjectReader::material(NewMesh* mesh, stringstream& sline) {
	string path;
	sline >> path;
	MaterialReader::read(mesh, path);
}

void NewObjectReader::vertice(NewMesh* mesh, stringstream &sline) {
	float x, y, z;
	sline >> x >> y >> z;
	mesh->addVertice(new glm::vec3(x, y, z));
}

void NewObjectReader::normal(NewMesh* mesh, stringstream& sline) {
	float x, y, z;
	sline >> x >> y >> z;
	mesh->addNormal(new glm::vec3(x, y, z));
}

void NewObjectReader::texture(NewMesh* mesh, stringstream& sline) {
	float x, y;
	sline >> x >> y;
	mesh->addTexture(new glm::vec2(x, y));
}

int getNextTokenValue2(stringstream& stoken) {
	string temp;
	getline(stoken, temp, '/');
	return temp.empty() ? 0 : stoi(temp);
}

void NewObjectReader::face(NewGroup* group, stringstream& sline) {
	NewFace* face = new NewFace();

	string token;
	while (getline(sline, token, ' ')) {

		if (token.empty()) {
			continue;
		}

		stringstream stoken(token);

		int v = getNextTokenValue2(stoken);
		int t = getNextTokenValue2(stoken);
		int n = getNextTokenValue2(stoken);

		face->push(v, n, t);
	}

	group->addFace(face);
}

void NewObjectReader::usemtl(NewGroup* group, stringstream& sline) {
	string name;
	sline >> name;
	group->setMaterial(name);
}
