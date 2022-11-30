#pragma once
#define NEW_MESH_H

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include "NewGroup.h"
#include "NewMaterial.h"

using namespace std;
using namespace glm;

class NewMesh
{

private:
	vector<NewGroup*> groups;
	vector<vec3*> vertices;
	vector<vec3*> normais;
	vector<vec2*> textures;
	map<string, NewMaterial*> materials;

public:
	NewMesh();
	~NewMesh();
	vec3* vertice(int id);
	vec3* normal(int id);
	vec2* texture(int id);

	int addVertice(vec3*);
	int addNormal(vec3*);
	int addTexture(vec2*);
	int addGroup(NewGroup*);
	int addMaterial(string name, NewMaterial* material);

	
	vector<NewGroup*> getGroups() {
		return groups;
	}

	NewMaterial* getMaterial(string name) {
		return materials[name];
	}
};
