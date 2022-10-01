// #include "ObjectReader.h"

// ObjectReader::ObjectReader()
// {
// }

// ObjectReader::~ObjectReader() {}

// Mesh *ObjectReader::read(string filename)
// {
//   if (meshes.find(filename) != meshes.end())
//   {
//     return meshes[filename];
//   }

//   ifstream arq(filename);

//   if (!arq)
//   {
//     exit(EXIT_FAILURE);
//   }

//   while (!arq.eof())
//   {
//     string line;
//     stringstream restLine;
//     string command;

//     getline(arq, line);
//     restLine << line;

//     restLine >> command;

//     this->meshBuilder->processLine(command, restLine);
//   }

//   Mesh *mesh = this->meshBuilder->build();
//   meshes.insert(make_pair(filename, mesh));

//   // if (mesh->getMaterialsFile().empty())
//   // {
//   //   return mesh;
//   // }

//   // MaterialHandler *handler = this->mtlReader->read(mesh->getMaterialsFile());
//   // mesh->setMaterialHandler(handler);

//   return mesh;
// }