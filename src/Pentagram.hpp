#pragma once

#include "Object3D.hpp"
#include "IGenerator.hpp"

class Pentagram : public Object3D, public IGenerator
{
  const int mDistance;
  const int mRadius;
public:

  explicit Pentagram(const char* name, int distance, int radius) :
    Object3D(name), mDistance(distance), mRadius(radius)
  {
  }

  virtual ~Pentagram() = default;

  Pentagram(Pentagram const &) = delete;
  Pentagram(Pentagram &&) = delete;
  Pentagram& operator=(const Pentagram& v) = delete;
  Pentagram& operator=(Pentagram &&) = delete;

  virtual void Generate() override;

};
