#include "NewFace.h"

NewFace::NewFace() {}

NewFace::~NewFace() {
	vertices.clear();
	normais.clear();
	textures.clear();
}

int NewFace::addVertice(int v) {
	vertices.push_back(v);
	return vertices.size() - 1;
}

void NewFace::push(int v, int n, int t) {
	vertices.push_back(v);
	normais.push_back(n);
	textures.push_back(t);
}
