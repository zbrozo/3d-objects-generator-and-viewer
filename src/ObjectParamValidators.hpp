#ifndef _OBJECT_PARAM_VALIDATORS_
#define _OBJECT_PARAM_VALIDATORS_

#include <optional>
#include <functional>
#include <stdexcept>

template<class T>
void SetParam(
  T& destParam,
  const std::optional<T>& srcParam,
  std::function<void(T)>(validator) = nullptr)
{
  if (srcParam.has_value())
  {
    if (validator != nullptr)
    {
      validator(srcParam.value());
    }

    destParam = srcParam.value();
  }
};

template<class T>
void Validator(T param, std::optional<T> valueMin, std::optional<T> valueMax)
{
  if (valueMin.has_value())
  {
    if (param < valueMin.value())
    {
      throw std::out_of_range("Too less value");
    }
  }

  if (valueMax.has_value())
  {
    if (param > valueMax.value())
    {
      throw std::out_of_range("Too big value");
    }
  }
};

#endif
