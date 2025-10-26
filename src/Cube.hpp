#pragma once

#include "Object3D.hpp"
#include "IGenerator.hpp"

class Cube : public Object3D, public IGenerator
{

  int mSize = 50;
  
public:

  explicit Cube(const char* name, int size = 50) :
    Object3D(name), mSize(size)
  {
  }

  virtual ~Cube() = default;
  
  Cube(Cube const &) = delete;
  Cube(Cube &&) = delete;
  Cube& operator=(const Cube& v) = delete;
  Cube& operator=(Cube &&) = delete;
  
  virtual void Generate() override;

protected:
  
  std::pair<Faces, Vertices> CreateCube(const Faces& faces, const Vertices& vertices);

  static void RotateSide(
    int degx, int degy, int degz,
    const Faces& faces,
    const Vertices& vertices,
    Faces& objectFaces,
    Vertices& objectVertices);
  
};
