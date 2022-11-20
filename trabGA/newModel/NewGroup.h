#pragma once
#define NEW_GROUP_H
#include <vector>
#include <string>
#include "NewFace.h"

#include <GL/glew.h>

using namespace std;

class NewGroup
{
private:
	GLuint VAO;
	int numVertices;
	string name;
	string material;
	vector<NewFace*> faces;

public:
	NewGroup();
	~NewGroup();
	int addFace(NewFace* face);

	vector<NewFace*> getFaces() {
		return faces;
	}

	GLuint& getVAO() {
		return VAO;
	}

	void setVAO(GLuint* v) {
		VAO = *v;
	}

	int getNumVertices() {
		return numVertices;
	}

	void increaseNumVertices() {
		numVertices++;
	}
	
	void setName(string n) {
		name = n;
	}

	string getName() {
		return name;
	}

	void setMaterial(string n) {
		material = n;
	}

	string getMaterial() {
		return material;
	}
};

