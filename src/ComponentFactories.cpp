#include "ComponentFactories.hpp"
#include "Components.hpp"
#include "Object3D.hpp"
#include "Params.hpp"

#include <memory>
#include <optional>
#include <algorithm>

#include <boost/log/trivial.hpp>
#include <stdexcept>

using namespace std::placeholders;

namespace
{

auto findParamsVector = [](const std::pair<ParamsId, ParamsVector> &params, ParamsId id)
{
  return params.first == id;
};

size_t getObligatoryUnsignedParam(std::vector<int> values, unsigned int index)
{
  if (values.size() <= index)
  {
    throw std::out_of_range("Parameter not exists");
  }

  if (0 > values[index])
  {
    throw std::out_of_range("Parameter is negative");
  }

  return values[index];
}

int getObligatorySignedParam(std::vector<int> values, unsigned int index)
{
  if (values.size() <= index)
  {
    throw std::out_of_range("Parameter not exists");
  }

  return values[index];
}

auto getParam(std::vector<int> values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<int>{values[index]};
  }

  return std::optional<int>();
}

} // namespace

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
