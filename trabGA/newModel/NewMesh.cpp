#include "NewMesh.h"

NewMesh::NewMesh() {}

NewMesh::~NewMesh() {
	groups.clear();
	vertices.clear();
	normais.clear();
	textures.clear();
	materials.clear();
}

glm::vec3* NewMesh::vertice(int id) {
	return vertices[id];
}

glm::vec3* NewMesh::normal(int id) {
	return normais[id];
}

glm::vec2* NewMesh::texture(int id) {
	return textures[id];
}

int NewMesh::addVertice(vec3* vec)
{
	vertices.push_back(vec);
	return vertices.size() - 1;
}

int NewMesh::addNormal(vec3* vec)
{
	normais.push_back(vec);
	return normais.size() - 1;
}

int NewMesh::addTexture(vec2* vec)
{
	textures.push_back(vec);
	return textures.size() - 1;
}

int NewMesh::addGroup(NewGroup* group) {
	groups.push_back(group);
	return groups.size() - 1;
}

int NewMesh::addMaterial(string name, NewMaterial* material) {
	materials[name] = material;
	return materials.size() - 1;
}
