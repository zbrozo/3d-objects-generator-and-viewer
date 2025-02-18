#pragma once

#include "Object3D.hpp"
#include "IGenerator.hpp"

class Tetrahedron : public Object3D, public IGenerator
{

  int mRadius = 50;

public:

  Tetrahedron(const char* name, int radius = 50) :
    Object3D(name), mRadius(radius)
  {
  }

  virtual ~Tetrahedron() = default;

  Tetrahedron(Tetrahedron const &) = delete;
  Tetrahedron(Tetrahedron &&) = delete;
  Tetrahedron& operator=(const Tetrahedron& v) = delete;
  Tetrahedron& operator=(Tetrahedron &&) = delete;

  virtual void Generate() override;

};
