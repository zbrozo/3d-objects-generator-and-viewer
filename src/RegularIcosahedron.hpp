#ifndef _REGULARICOSAHEDRON_HPP_
#define _REGULARICOSAHEDRON_HPP_

#include "Object3D.hpp"
#include "IGenerator.hpp"

class RegularIcosahedron : public Object3D, public IGenerator
{

  int mRadius = 50;

public:

  explicit RegularIcosahedron(const char* name, int radius = 50) :
    Object3D(name), mRadius(radius)
  {
  }

  virtual ~RegularIcosahedron() = default;

  RegularIcosahedron(RegularIcosahedron const &) = delete;
  RegularIcosahedron(RegularIcosahedron &&) = delete;
  RegularIcosahedron& operator=(const RegularIcosahedron& v) = delete;
  RegularIcosahedron& operator=(RegularIcosahedron &&) = delete;

  virtual void Generate() override;

};

#endif
