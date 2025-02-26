#include "ComponentFactoryBase.hpp"
#include "Components.hpp"

class Object3D;

namespace Components
{

class SquareFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

class RectangleFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

class SquareWithHolePart1Factory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

class SquareWithHolePart2Factory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

class PyramidFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

class ConeFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

class CylinderFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

class CylinderWithTriangularFacesFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

class CSignFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsVector& params) const override;
};

} // namespace
