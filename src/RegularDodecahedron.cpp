#include <cmath>
#include <algorithm>
#include "RegularDodecahedron.hpp"
#include "RegularIcosahedron.hpp"
#include "Components.hpp"
#include "Tools.hpp"

void RegularDodecahedron::Generate()
{
  RegularIcosahedron icosahedron("", 100);
  icosahedron.Generate();

  const auto& vertices = icosahedron.GetVertices();
}
