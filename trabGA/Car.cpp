#include "Car.h"

Car::Car(string objFile, string route) {
    this->objFile = objFile;
    this->route = route;
}

Car::~Car() {}

Mesh* Car::mesh() {
    return this->_mesh;
}

glm::mat4* Car::transform() {
    return this->_transform;
}