#ifndef _STAR_HPP_
#define _STAR_HPP_

#include "Object3D.hpp"
#include "IGenerator.hpp"

class Star : public Object3D, public IGenerator
{
  const int mDistance;
  const int mRadius;

public:

  explicit Star(const char* name, int distance, int radius) :
    Object3D(name), mDistance(distance), mRadius(radius)
  {
  }

  virtual ~Star() = default;

  Star(Star const &) = delete;
  Star(Star &&) = delete;
  Star& operator=(const Star& v) = delete;
  Star& operator=(Star &&) = delete;

  virtual void Generate() override;

};

#endif
