#include "NewObject.h"
#include "../utils/NewObjectReader.h"

NewObject::NewObject(string meshPath) {
  this->newMesh = NewObjectReader::read(meshPath);
}

NewObject::~NewObject() {

}