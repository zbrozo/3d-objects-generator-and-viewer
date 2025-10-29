#ifndef _COMPONENTS_HPP_
#define _COMPONENTS_HPP_

#include "IGenerator.hpp"
#include "Object3D.hpp"
#include "ObjectParamValidators.hpp"

#include <cstdint>

namespace Components
{

class Square : public Object3D, public IGenerator
{
  const int mSide;

public:

  explicit Square(int side) :
    Object3D("Square"), mSide(side)
  {
  }

  void Generate() override;

  virtual ~Square() = default;

  Square(Square const &) = delete;
  Square(Square &&) = delete;
  Square& operator=(const Square&) = delete;
  Square& operator=(Square &&) = delete;
};

class Rectangle : public Object3D, public IGenerator
{
  const int mSideX;
  const int mSideY;

public:

  explicit Rectangle(int sideX, int sideY) :
    Object3D("Rectangle"), mSideX(sideX), mSideY(sideY)
  {
  }

  void Generate() override;

  virtual ~Rectangle() = default;

  Rectangle(Rectangle const &) = delete;
  Rectangle(Rectangle &&) = delete;
  Rectangle& operator=(const Rectangle&) = delete;
  Rectangle& operator=(Rectangle &&) = delete;
};

class Trapeze : public Object3D, public IGenerator
{
  const int mTop;
  const int mBottom;
  const int mHeight;

public:

  explicit Trapeze(int top, int bottom, int height) :
    Object3D("Trapeze"), mTop(top), mBottom(bottom), mHeight(height)
  {
  }

  void Generate() override;

  virtual ~Trapeze() = default;

  Trapeze(Trapeze const &) = delete;
  Trapeze(Trapeze &&) = delete;
  Trapeze& operator=(const Trapeze&) = delete;
  Trapeze& operator=(Trapeze &&) = delete;
};

class Pyramid : public Object3D, public IGenerator
{
  const int mSide;
  const int mHeight;

public:

  explicit Pyramid(int side, int height) :
    Object3D("Pyramid"), mSide(side), mHeight(height)
  {
  }

  void Generate() override;

  virtual ~Pyramid() = default;

  Pyramid(Pyramid const &) = delete;
  Pyramid(Pyramid &&) = delete;
  Pyramid& operator=(const Pyramid&) = delete;
  Pyramid& operator=(Pyramid &&) = delete;

};

class Cone : public Object3D, public IGenerator
{
  const uint16_t mCircleAmount;
  const int mCircleRadius;
  const int mHeight;

public:

  explicit Cone(uint16_t circleAmount, int circleRadius, int height) :
    Object3D("Cone"), mCircleAmount(circleAmount), mCircleRadius(circleRadius), mHeight(height)
  {
  }

  void Generate() override;

  virtual ~Cone() = default;

  Cone(Cone const &) = delete;
  Cone(Cone &&) = delete;
  Cone& operator=(const Cone&) = delete;
  Cone& operator=(Cone &&) = delete;
};

class Cylinder : public Object3D, public IGenerator
{
  const uint16_t mCircleAmount;
  const int mCircleRadius;
  const int mHeight;

public:

  explicit Cylinder(uint16_t circleAmount, int circleRadius, int height) :
    Object3D("Cylinder"), mCircleAmount(circleAmount), mCircleRadius(circleRadius), mHeight(height)
  {
  }

  void Generate() override;

  virtual ~Cylinder() = default;

  Cylinder(const Cylinder&) = delete;
  Cylinder(Cylinder&&) = delete;
  Cylinder& operator=(const Cylinder&) = delete;
  Cylinder& operator=(Cylinder &&) = delete;

};

class TriangulatedCylinder : public Object3D, public IGenerator
{
  const uint16_t mCircleAmount;
  const int mCircleRadius;
  const int mHeight;

public:

  explicit TriangulatedCylinder(uint16_t circleAmount, int circleRadius, int height) :
    Object3D("TriangulatedCylinder"), mCircleAmount(circleAmount), mCircleRadius(circleRadius), mHeight(height)
  {
  }

  void Generate() override;

  virtual ~TriangulatedCylinder() = default;

  TriangulatedCylinder(const TriangulatedCylinder&) = delete;
  TriangulatedCylinder(TriangulatedCylinder&&) = delete;
  TriangulatedCylinder& operator=(const TriangulatedCylinder&) = delete;
  TriangulatedCylinder& operator=(TriangulatedCylinder&&) = delete;
};

class Star : public Object3D, public IGenerator
{
  const uint16_t mCircleAmount;
  const int mCircleRadius;

public:

  explicit Star(uint16_t circleAmount, int circleRadius) :
    Object3D("Star"), mCircleAmount(circleAmount), mCircleRadius(circleRadius)
  {
  }

  void Generate() override;

  virtual ~Star() = default;

  Star(const Star&) = delete;
  Star(Star&&) = delete;
  Star& operator=(const Star&) = delete;
  Star& operator=(Star &&) = delete;
};

} // namespace Components

#endif
