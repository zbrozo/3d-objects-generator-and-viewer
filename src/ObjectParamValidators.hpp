#ifndef _OBJECT_PARAM_VALIDATORS_
#define _OBJECT_PARAM_VALIDATORS_

#include <optional>
#include <functional>

template<class T>
void SetParam(
  T& destParam,
  const std::optional<T>& srcParam,
  std::function<bool(T)>(validator))
{
  if (srcParam.has_value() && validator(srcParam.value()))
  {
    destParam = srcParam.value();
  }
};

bool IntValidator(int param, std::optional<int> valueMin, std::optional<int> valueMax);

#endif
