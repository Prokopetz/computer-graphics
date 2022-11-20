#pragma once
#ifndef NEW_OBJECT_READER_H
#define NEW_OBJECT_READER_H

#include <string>
#include "../newModel/NewGroup.h"
#include "../newModel/NewMesh.h"
#include "MaterialReader.h"

using namespace std;

class NewObjectReader
{
public:
	static NewMesh* read(string filename);

	static void material(NewMesh* mesh, stringstream& sline);
	static void vertice(NewMesh* mesh, stringstream& sline);
	static void normal(NewMesh* mesh, stringstream& sline);
	static void texture(NewMesh* mesh, stringstream& sline);
	static void face(NewGroup* group, stringstream& sline);
	static void usemtl(NewGroup* group, stringstream& sline);
};

#endif