#include "FractalTetrahedron.hpp"
#include "RegularTetrahedron.hpp"

#include <cmath>
#include <algorithm>

void FractalTetrahedron::Generate()
{
  auto Translate = [](Vertices& vertices, int x, int y, int z) {
    std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(),
      [&](const Vertex& vertex)
      {
        return Vertex(vertex.getX() + x, vertex.getY() + y, vertex.getZ() + z);
      });
  };

  RegularTetrahedron tmp("tetrahedron", mRadius);
  tmp.Generate();

  Vertices vertices = tmp.GetVertices();

  const auto xLen = std::abs(vertices[0].getX() - vertices[1].getX());
  const auto yLen = std::abs(vertices[0].getY() - vertices[1].getY());
  const auto len = std::sqrt(std::pow(xLen, 2) + std::pow(yLen, 2));
  const auto figureHeight  = std::sqrt(std::pow(len * std::sqrt(3.0) / 2.0, 2) - std::pow(len / 3.0, 2));

  Translate(vertices, -xLen, -mRadius, -figureHeight);
  Merge(vertices, tmp.GetFaces());

  vertices = tmp.GetVertices();
  Translate(vertices, xLen, -mRadius, -figureHeight);
  Merge(vertices, tmp.GetFaces());

  vertices = tmp.GetVertices();
  Translate(vertices, 0, yLen-mRadius, -figureHeight);
  Merge(vertices, tmp.GetFaces());
  
  vertices = tmp.GetVertices();
  Translate(vertices, 0, -mRadius+(yLen-mRadius), 0);
  Merge(vertices, tmp.GetFaces());
}
