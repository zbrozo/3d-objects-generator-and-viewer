#include "Params.hpp"

#include <stdexcept>

size_t getObligatoryUnsignedParam(ParamsVector values, unsigned int index)
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

int getObligatorySignedParam(ParamsVector values, unsigned int index)
{
  if (values.size() <= index)
  {
    throw std::out_of_range("Parameter not exists");
  }

  return values[index];
}

std::optional<int> getOptionalParam(ParamsVector values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<int>{values[index]};
  }

  return std::optional<int>();
}

std::optional<double> getOptionalParam(const SinusParamsVector& values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<double>{values[index]};
  }

  return std::optional<double>();
}
