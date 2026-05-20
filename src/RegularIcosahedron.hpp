#ifndef _REGULARICOSAHEDRON_HPP_
#define _REGULARICOSAHEDRON_HPP_

#include "Object3D.hpp"
#include "IGenerator.hpp"

class RegularIcosaHedron : public Object3D, public IGenerator
{

  int mRadius = 50;

public:

  explicit RegularIcosaHedron(const char* name, int radius = 50) :
    Object3D(name), mRadius(radius)
  {
  }

  virtual ~RegularIcosaHedron() = default;

  RegularIcosaHedron(RegularIcosaHedron const &) = delete;
  RegularIcosaHedron(RegularIcosaHedron &&) = delete;
  RegularIcosaHedron& operator=(const RegularIcosaHedron& v) = delete;
  RegularIcosaHedron& operator=(RegularIcosaHedron &&) = delete;

  virtual void Generate() override;

};

#endif
