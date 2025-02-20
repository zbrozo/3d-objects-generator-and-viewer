#pragma once

#include "Object3D.hpp"
#include "IGenerator.hpp"

class Tetrahedron : public Object3D, public IGenerator
{

  int mRadius = 50;
  int mHeight = 0;
  
public:

  Tetrahedron(const char* name, int radius = 50, int height = 0) :
    Object3D(name), mRadius(radius), mHeight(height)
  {
  }

  virtual ~Tetrahedron() = default;

  Tetrahedron(Tetrahedron const &) = delete;
  Tetrahedron(Tetrahedron &&) = delete;
  Tetrahedron& operator=(const Tetrahedron& v) = delete;
  Tetrahedron& operator=(Tetrahedron &&) = delete;

  virtual void Generate() override;

};
