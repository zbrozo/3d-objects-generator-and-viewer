#include "Vectors.hpp"
#include "Rotation.hpp"

std::ostream& operator<<(std::ostream& os, const Vectors& vectors)
{
  for (const auto& v : vectors)
  {
    os << v;
  }

  os << std::endl;

  return os;
}

