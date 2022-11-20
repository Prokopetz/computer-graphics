#pragma once
#ifndef MATERIAL_READER_H
#define MATERIAL_READER_H

#include <string>
#include "../newModel/NewMaterial.h"
#include "../newModel/NewMesh.h"

using namespace std;

class MaterialReader
{
public:
	static void read(NewMesh* mesh, string filename);

	static void name(NewMaterial* material, stringstream& sline);
	static void ambient(NewMaterial* material, stringstream& sline);
	static void diffuse(NewMaterial* material, stringstream& sline);
	static void specular(NewMaterial* material, stringstream& sline);
	static void shininess(NewMaterial* material, stringstream& sline);
	static void texture(NewMaterial* material, stringstream& sline);
};

#endif

