#include "ObjectParamValidators.hpp"

#include <stdexcept>

void IntValidator(int param, std::optional<int> valueMin, std::optional<int> valueMax)
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
