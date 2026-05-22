#ifndef _REGULARDODECAHEDRON_HPP_
#define _REGULARDODECAHEDRON_HPP_

#include "Object3D.hpp"
#include "IGenerator.hpp"

class RegularDodecahedron : public Object3D, public IGenerator
{

  int mRadius = 0;

public:

  explicit RegularDodecahedron(const char* name, int radius) :
    Object3D(name), mRadius(radius)
  {
  }

  virtual ~RegularDodecahedron() = default;

  RegularDodecahedron(RegularDodecahedron const &) = delete;
  RegularDodecahedron(RegularDodecahedron &&) = delete;
  RegularDodecahedron& operator=(const RegularDodecahedron& v) = delete;
  RegularDodecahedron& operator=(RegularDodecahedron &&) = delete;

  virtual void Generate() override;

};

#endif
