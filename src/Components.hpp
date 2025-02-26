#pragma once

#include "IGenerator.hpp"
#include "Object3D.hpp"

#include <optional>
#include <iostream>

namespace Components
{

class Square : public Object3D, public IGenerator
{
  int mSize = 50;

public:

  Square(std::optional<int> size) :
    Object3D("")
  {
    if (size.has_value())
    {
      mSize = size.value();
    }
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

  Rectangle(std::optional<int> sizeX, std::optional<int> sizeY) :
    Object3D("")
  {
    if (sizeX.has_value())
    {
      mSizeX = sizeX.value();
    }

    if (sizeY.has_value())
    {
      mSizeY = sizeY.value();
    }

  }

  void Generate() override;

  virtual ~Rectangle() = default;

  Rectangle(Rectangle const &) = delete;
  Rectangle(Rectangle &&) = delete;
  Rectangle& operator=(const Rectangle&) = delete;
  Rectangle& operator=(Rectangle &&) = delete;

};


class SquareWithHolePart1 : public Object3D, public IGenerator
{
  int mSize1 = 50;
  int mSize2 = 20;
  int mSize3 = 20;

public:

  SquareWithHolePart1(
    const std::optional<int>& size1,
    const std::optional<int>& size2,
    const std::optional<int>& size3
    ) :
    Object3D("")
  {
    if (size1.has_value())
    {
      mSize1 = size1.value();
    }

    if (size2.has_value())
    {
      mSize2 = size2.value();
    }

    if (size3.has_value())
    {
      mSize3 = size3.value();
    }
  }

  void Generate() override;

  virtual ~SquareWithHolePart1() = default;

  SquareWithHolePart1(SquareWithHolePart1 const &) = delete;
  SquareWithHolePart1(SquareWithHolePart1 &&) = delete;
  SquareWithHolePart1& operator=(const SquareWithHolePart1&) = delete;
  SquareWithHolePart1& operator=(SquareWithHolePart1 &&) = delete;

};

class SquareWithHolePart2 : public Object3D, public IGenerator
{
  int mSize1 = 50;
  int mSize2 = 20;

public:

  SquareWithHolePart2(
    const std::optional<int>& size1,
    const std::optional<int>& size2
    ) :
    Object3D("")
  {
    if (size1.has_value())
    {
      mSize1 = size1.value();
    }

    if (size2.has_value())
    {
      mSize2 = size2.value();
    }
  }

  void Generate() override;

  virtual ~SquareWithHolePart2() = default;

  SquareWithHolePart2(SquareWithHolePart2 const &) = delete;
  SquareWithHolePart2(SquareWithHolePart2 &&) = delete;
  SquareWithHolePart2& operator=(const SquareWithHolePart2&) = delete;
  SquareWithHolePart2& operator=(SquareWithHolePart2 &&) = delete;

};

class Pyramid : public Object3D, public IGenerator
{
  int mSize1 = 50;
  int mSize2 = 20;

public:

  Pyramid(
    const std::optional<int>& size1,
    const std::optional<int>& size2
    ) :
    Object3D("")
  {
    if (size1.has_value())
    {
      mSize1 = size1.value();
    }

    if (size2.has_value())
    {
      mSize2 = size2.value();
    }
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

  Cone(
    const std::optional<int>& circleAmount,
    const std::optional<int>& circleRadius,
    const std::optional<int>& height
    ) :
    Object3D("")
  {
    if (circleAmount.has_value())
    {
      mCircleAmount = circleAmount.value();
    }

    if (circleRadius.has_value())
    {
      mCircleRadius = circleRadius.value();
    }

    if (height.has_value())
    {
      mHeight = height.value();
    }
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

  Cylinder(
    const std::optional<int>& circleAmount,
    const std::optional<int>& circleRadius,
    const std::optional<int>& height
    ) :
    Object3D("")
  {
    if (circleAmount.has_value())
    {
      mCircleAmount = circleAmount.value();
    }

    if (circleRadius.has_value())
    {
      mCircleRadius = circleRadius.value();
    }

    if (height.has_value())
    {
      mHeight = height.value();
    }
  }

  void Generate() override;

  virtual ~Cylinder() = default;

  Cylinder(const Cylinder&) = delete;
  Cylinder(Cylinder&&) = delete;
  Cylinder& operator=(const Cylinder&) = delete;
  Cylinder& operator=(Cylinder &&) = delete;

};

class CylinderWithTriangularFaces : public Object3D, public IGenerator
{
  int mCircleAmount = 3;
  int mCircleRadius = 50;
  int mHeight = 50;

public:

  CylinderWithTriangularFaces(
    const std::optional<int>& circleAmount,
    const std::optional<int>& circleRadius,
    const std::optional<int>& height
    ) :
    Object3D("")
  {
    if (circleAmount.has_value())
    {
      mCircleAmount = circleAmount.value();
    }

    if (circleRadius.has_value())
    {
      mCircleRadius = circleRadius.value();
    }

    if (height.has_value())
    {
      mHeight = height.value();
    }
  }

  void Generate() override;

  virtual ~CylinderWithTriangularFaces() = default;

  CylinderWithTriangularFaces(const CylinderWithTriangularFaces&) = delete;
  CylinderWithTriangularFaces(CylinderWithTriangularFaces&&) = delete;
  CylinderWithTriangularFaces& operator=(const CylinderWithTriangularFaces&) = delete;
  CylinderWithTriangularFaces& operator=(CylinderWithTriangularFaces &&) = delete;
};

class CSign : public Object3D, public IGenerator
{
  int mCircleAmount = 3;
  int mCircle1Radius = 50;
  int mCircle2Radius = 50;
  int mCircle1Offset = 0;
  int mCircle2Offset = 0;
  int mWidth = 10;

public:

  CSign(
    const std::optional<int>& circleAmount,
    const std::optional<int>& circle1Radius,
    const std::optional<int>& circle2Radius,
    const std::optional<int>& circle1Offset,
    const std::optional<int>& circle2Offset,
    const std::optional<int>& width
    ) :
    Object3D("")
  {
    if (circleAmount.has_value())
    {
      mCircleAmount = circleAmount.value();
    }

    if (circle1Radius.has_value())
    {
      mCircle1Radius = circle1Radius.value();
    }

    if (circle2Radius.has_value())
    {
      mCircle2Radius = circle2Radius.value();
    }

    if (circle1Offset.has_value())
    {
      mCircle1Offset = circle1Offset.value();
    }

    if (circle2Offset.has_value())
    {
      mCircle2Offset = circle2Offset.value();
    }

    if (width.has_value())
    {
      mWidth = width.value();
    }
  }

  void Generate() override;

  virtual ~CSign() = default;

  CSign(const CSign&) = delete;
  CSign(CSign&&) = delete;
  CSign& operator=(const CSign&) = delete;
  CSign& operator=(CSign &&) = delete;
};

} // namespace Components
