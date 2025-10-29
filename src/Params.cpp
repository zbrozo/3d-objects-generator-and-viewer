#include "Params.hpp"

template<typename R, typename T>
R GetObligatory(std::vector<T> values, uint32_t index)
{
  if (values.size() <= index)
  {
    throw std::out_of_range("Parameter not exists");
  }

  if (std::is_unsigned_v<R>)
  {
    if (0 > values[index])
    {
      throw std::out_of_range("Parameter is negative");
    }
  }
  
  return values[index];
}

template<typename R, typename T>
std::optional<R> GetOptional(std::vector<T> values, uint32_t index)
{
  if (values.size() > index)
  {
    return std::optional<R>{values[index]};
  }

  return std::optional<R>();
}

int GetObligatoryInt(ParamsVector values, uint32_t index)
{
  return GetObligatory<int, int>(values, index);
}

uint16_t GetObligatoryUnsignedInt(ParamsVector values, uint32_t index)
{
  return GetObligatory<uint16_t, int>(values, index);
}

std::optional<int> GetOptionalInt(ParamsVector values, uint32_t index)
{
  return GetOptional<int, int>(values, index);
}

std::optional<uint16_t> GetOptionalUnsignedInt(ParamsVector values, uint32_t index)
{
  return GetOptional<uint16_t, int>(values, index);
}

std::optional<double> GetOptionalDouble(SinusParamsVector values, uint32_t index)
{
  return GetOptional<double, double>(values, index);
}
