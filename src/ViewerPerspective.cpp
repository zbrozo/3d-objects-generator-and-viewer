#include "ViewerPerspective.hpp"
#include "Vertices.hpp"

Vertices CalculateVerticesPerspective(const Vertices& vertices, const int* zoom)
{
  Vertices vertices2d;
  
  for (const auto& vertex : vertices)
  {
    const auto v = CalculatePerspective<Vertex>(vertex, *zoom);
    vertices2d.push_back(v);
  }
  
  return vertices2d;
}
