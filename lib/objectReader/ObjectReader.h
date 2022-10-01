#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <math.h>

#include "Mesh.h"
#include "Group.h"

using namespace std;

class ObjectReader
{
public:
  static Mesh *read(string filename);

private:
  static void material(Mesh *mesh, stringstream &sline);
  static void vertice(Mesh *mesh, stringstream &sline);
  static void normal(Mesh *mesh, stringstream &sline);
  static void texture(Mesh *mesh, stringstream &sline);
  static void face(Group *group, stringstream &sline);
  static void usemtl(Group *group, stringstream &sline);
};
