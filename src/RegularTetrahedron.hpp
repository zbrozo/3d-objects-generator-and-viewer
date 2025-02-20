#pragma once

#include "Object3D.hpp"
#include "IGenerator.hpp"

class RegularTetrahedron : public Object3D, public IGenerator
{

  int mRadius = 50;

public:

  RegularTetrahedron(const char* name, int radius = 50) :
    Object3D(name), mRadius(radius)
  {
  }

  virtual ~RegularTetrahedron() = default;

  RegularTetrahedron(RegularTetrahedron const &) = delete;
  RegularTetrahedron(RegularTetrahedron &&) = delete;
  RegularTetrahedron& operator=(const RegularTetrahedron& v) = delete;
  RegularTetrahedron& operator=(RegularTetrahedron &&) = delete;

  virtual void Generate() override;

};
