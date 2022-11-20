#pragma once
#define NEW_GROUP_H
#include <vector>
#include <string>
#include "NewFace.h"

#include <GL/glew.h>

using namespace std;

class Group
{
private:
	GLuint VAO;
	int numVertices;
	string name;
	string material;
	vector<Face*> faces;

public:
	Group();
	~Group();
	int addFace(Face* face);

	vector<Face*> getFaces() {
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
