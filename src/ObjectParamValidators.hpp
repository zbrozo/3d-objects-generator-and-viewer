#ifndef _OBJECT_PARAM_VALIDATORS_
#define _OBJECT_PARAM_VALIDATORS_

#include <optional>
#include <functional>

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

void IntValidator(int param, std::optional<int> valueMin, std::optional<int> valueMax);

#endif
