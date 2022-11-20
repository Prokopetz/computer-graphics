#pragma once
#define NEW_FACE_H

#include <vector>

using namespace std;


class NewFace
{
private:
	vector<int> vertices;
	vector<int> normais;
	vector<int> textures;

public:
	NewFace();
	~NewFace();
	int addVertice(int v);
	void push(int v, int n, int t);

	vector<int> getVertices() {
		return vertices;
	}

	vector<int> getNormais() {
		return normais;
	}

	vector<int> getTextures() {
		return textures;
	}
};
