#pragma once

#include "Object3D.hpp"
#include "IGenerator.hpp"

class FractalTetrahedron : public Object3D, public IGenerator
{

  int mRadius = 50;

public:

  FractalTetrahedron(const char* name, int radius = 50) :
    Object3D(name), mRadius(radius)
  {
  }

  virtual ~FractalTetrahedron() = default;

  FractalTetrahedron(FractalTetrahedron const &) = delete;
  FractalTetrahedron(FractalTetrahedron &&) = delete;
  FractalTetrahedron& operator=(const FractalTetrahedron& v) = delete;
  FractalTetrahedron& operator=(FractalTetrahedron &&) = delete;

  virtual void Generate() override;

};
