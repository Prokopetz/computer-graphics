#include "NewGroup.h"

NewGroup::NewGroup() {}

NewGroup::~NewGroup() {
	faces.clear();
}

int NewGroup::addFace(NewFace* face) {
	faces.push_back(face);
	return faces.size() - 1;
}
