#include "ComponentFactories.hpp"

namespace Components
{

std::unique_ptr<Object3D> SquareFactory::FactoryMethod(
  const ParamsVector& params) const
{
  const auto side = getObligatorySignedParam(params, 0);
  return std::make_unique<Components::Square>(side);
}

std::unique_ptr<Object3D> RectangleFactory::FactoryMethod(
  const ParamsVector& params) const
{
  const auto sideX = getObligatorySignedParam(params, 0);
  const auto sideY = getObligatorySignedParam(params, 1);
  return std::make_unique<Components::Rectangle>(sideX, sideY);
}

std::unique_ptr<Object3D> TrapezeFactory::FactoryMethod(
  const ParamsVector& params) const
{
  const auto top = getObligatorySignedParam(params, 0);
  const auto bottom = getObligatorySignedParam(params, 1);
  const auto height = getObligatorySignedParam(params, 2);
  return std::make_unique<Components::Trapeze>(top, bottom, height);
}

std::unique_ptr<Object3D> PyramidFactory::FactoryMethod(
  const ParamsVector& params) const
{
  const auto param0 = getObligatorySignedParam(params, 0);
  const auto param1 = getObligatorySignedParam(params, 1);
  return std::make_unique<Components::Pyramid>(param0, param1);
}

std::unique_ptr<Object3D> ConeFactory::FactoryMethod(
  const ParamsVector& params) const
{
  const auto param0 = getObligatoryUnsignedParam(params, 0);
  const auto param1 = getObligatorySignedParam(params, 1);
  const auto param2 = getObligatorySignedParam(params, 2);
  return std::make_unique<Components::Cone>(param0, param1, param2);
}

std::unique_ptr<Object3D> CylinderFactory::FactoryMethod(
  const ParamsVector& params) const
{
  const auto param0 = getObligatoryUnsignedParam(params, 0);
  const auto param1 = getObligatorySignedParam(params, 1);
  const auto param2 = getObligatorySignedParam(params, 2);
  return std::make_unique<Components::Cylinder>(param0, param1, param2);
}

std::unique_ptr<Object3D> TriangulatedCylinderFactory::FactoryMethod(
  const ParamsVector& params) const
{
  const auto param0 = getObligatoryUnsignedParam(params, 0);
  const auto param1 = getObligatorySignedParam(params, 1);
  const auto param2 = getObligatorySignedParam(params, 2);
  return std::make_unique<Components::TriangulatedCylinder>(param0, param1, param2);
}

std::unique_ptr<Object3D> StarFactory::FactoryMethod(
  const ParamsVector& params) const
{
  const auto param0 = getObligatoryUnsignedParam(params, 0);
  const auto param1 = getObligatorySignedParam(params, 1);
  return std::make_unique<Components::Star>(param0, param1);
}

} // namespace Components
