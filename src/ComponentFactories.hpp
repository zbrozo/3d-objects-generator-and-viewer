#include "ComponentFactoryBase.hpp"
#include "Components.hpp"
#include "Params.hpp"
#include "Object3D.hpp"

namespace Components
{

class SquareFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const ParamsVector& params) const override;
};

class RectangleFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const ParamsVector& params) const override;
};

class TrapezeFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const ParamsVector& params) const override;
};

class PyramidFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const ParamsVector& params) const override;
};

class ConeFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const ParamsVector& params) const override;
};

class CylinderFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const ParamsVector& params) const override;
};

class TriangulatedCylinderFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const ParamsVector& params) const override;
};

class StarFactory : public ComponentFactoryBase
{
public:
  std::unique_ptr<Object3D> FactoryMethod(
    const ParamsVector& params) const override;
};

} // namespace
