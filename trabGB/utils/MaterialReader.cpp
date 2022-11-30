#include "MaterialReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void MaterialReader::read(NewMesh* mesh, string filename)
{
	int firstMtl = 1;
	NewMaterial* material = new NewMaterial();

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

		if (temp == "newmtl") {
			if (firstMtl == 1) {
				firstMtl = 0;
			}
			else {
				mesh->addMaterial(material->getName(), material);
				material = new NewMaterial();
			}

			name(material, sline);
		}
		else if (temp == "Ka") {
			ambient(material, sline);
		}
		else if (temp == "Kd") {
			diffuse(material, sline);
		}
		else if (temp == "Ks") {
			specular(material, sline);
		}
		else if (temp == "Ns") {
			shininess(material, sline);
		}
		else if (temp == "map_Kd") {
			texture(material, sline);
		}
	}

	arq.close();

	mesh->addMaterial(material->getName(), material);
}

void MaterialReader::name(NewMaterial* material, stringstream& sline) {
	string name;
	sline >> name;
	material->setName(name);
}

void MaterialReader::ambient(NewMaterial* material, stringstream& sline) {
	float x, y, z;
	sline >> x >> y >> z;
	material->setAmbient(new glm::vec3(x, y, z));
}

void MaterialReader::diffuse(NewMaterial* material, stringstream& sline) {
	float x, y, z;
	sline >> x >> y >> z;
	material->setDiffuse(new glm::vec3(x, y, z));
}

void MaterialReader::specular(NewMaterial* material, stringstream& sline) {
	float x, y, z;
	sline >> x >> y >> z;
	material->setSpecular(new glm::vec3(x, y, z));
}

void MaterialReader::shininess(NewMaterial* material, stringstream& sline) {
	float shininess;
	sline >> shininess;
	material->setShininess(shininess);
}

void MaterialReader::texture(NewMaterial* material, stringstream& sline) {
	string texture;
	sline >> texture;
	material->setTexture(texture);
}

