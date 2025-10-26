#pragma once

#include "Object3D.hpp"
#include "IGenerator.hpp"

class Pentagram : public Object3D, public IGenerator
{
  int mDistance = 0;

public:

  explicit Pentagram(const char* name, int distance = 0) :
    Object3D(name), mDistance(distance)
  {
  }

  virtual ~Pentagram() = default;

  Pentagram(Pentagram const &) = delete;
  Pentagram(Pentagram &&) = delete;
  Pentagram& operator=(const Pentagram& v) = delete;
  Pentagram& operator=(Pentagram &&) = delete;

  virtual void Generate() override;

};
