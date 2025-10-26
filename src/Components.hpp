#ifndef _COMPONENTS_HPP_
#define _COMPONENTS_HPP_

#include "IGenerator.hpp"
#include "Object3D.hpp"
#include "ObjectParamValidators.hpp"

#include <optional>
#include <iostream>

namespace Components
{

class Square : public Object3D, public IGenerator
{
  int mSize = 50;

public:

  explicit Square(std::optional<int> size) :
    Object3D("Square")
  {
    SetParam<int>(mSize, size);
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
  int mSizeX = 50;
  int mSizeY = 50;

public:

  explicit Rectangle(std::optional<int> sizeX, std::optional<int> sizeY) :
    Object3D("Rectangle")
  {
    SetParam<int>(mSizeX, sizeX);
    SetParam<int>(mSizeY, sizeY);
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
  int mTop = 50;
  int mBottom = 50;
  int mHeight = 50;

public:

  explicit Trapeze(std::optional<int> top, std::optional<int> bottom, std::optional<int> height) :
    Object3D("Trapeze")
  {
    SetParam<int>(mTop, top);
    SetParam<int>(mBottom, bottom);
    SetParam<int>(mHeight, height);
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
  int mSize1 = 50;
  int mSize2 = 20;

public:

  explicit Pyramid(
    const std::optional<int>& size1,
    const std::optional<int>& size2
    ) :
    Object3D("Pyramid")
  {
    SetParam<int>(mSize1, size1);
    SetParam<int>(mSize2, size2);
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
  int mCircleAmount = 3;
  int mCircleRadius = 50;
  int mHeight = 50;

public:

  explicit Cone(
    const std::optional<int>& circleAmount,
    const std::optional<int>& circleRadius,
    const std::optional<int>& height
    ) :
    Object3D("Cone")
  {
    SetParam<int>(mCircleAmount, circleAmount);
    SetParam<int>(mCircleRadius, circleRadius);
    SetParam<int>(mHeight, height);
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
  int mCircleAmount = 3;
  int mCircleRadius = 50;
  int mHeight = 50;

public:

  explicit Cylinder(
    const std::optional<int>& circleAmount,
    const std::optional<int>& circleRadius,
    const std::optional<int>& height
    ) :
    Object3D("Cylinder")
  {
    SetParam<int>(mCircleAmount, circleAmount);
    SetParam<int>(mCircleRadius, circleRadius);
    SetParam<int>(mHeight, height);
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
  int mCircleAmount = 3;
  int mCircleRadius = 50;
  int mHeight = 50;

public:

  explicit TriangulatedCylinder(
    const std::optional<int>& circleAmount,
    const std::optional<int>& circleRadius,
    const std::optional<int>& height
    ) :
    Object3D("TriangulatedCylinder")
  {
    SetParam<int>(mCircleAmount, circleAmount);
    SetParam<int>(mCircleRadius, circleRadius);
    SetParam<int>(mHeight, height);
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
  int mCircleAmount = 5;
  int mCircleRadius = 50;

public:

  explicit Star(
    const std::optional<int>& circleAmount,
    const std::optional<int>& circleRadius
    ) :
    Object3D("Star")
  {
    SetParam<int>(mCircleAmount, circleAmount);
    SetParam<int>(mCircleRadius, circleRadius);
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
