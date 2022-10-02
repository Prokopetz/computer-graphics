#ifndef CAR_H
#define CAR_H

#include "Object.h"

class Car : public Object {
  private:
    string objFile;
    string route;
    Mesh* _mesh;
    glm::mat4* _transform;

  public:
      Car(string objFile, string route);
      ~Car() override;
      Mesh* mesh() override;
      glm::mat4* transform() override;

};


#endif