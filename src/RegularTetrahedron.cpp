#include "RegularTetrahedron.hpp"
#include "Components.hpp"
#include <cmath>
#include <algorithm>

void RegularTetrahedron::Generate()
{
  Components::Cone tmp(3, mRadius, 0);
  tmp.Generate();

  auto vertices = tmp.GetVertices();
  const auto xLen = std::abs(vertices[0].getX() - vertices[1].getX());
  const auto yLen = std::abs(vertices[0].getY() - vertices[1].getY());
  const auto len = std::sqrt(std::pow(xLen, 2) + std::pow(yLen, 2));
  const auto height = std::sqrt(6.0) * len / 3.0;

  Components::Cone tetrahedron(3, mRadius, height);
  tetrahedron.Generate();
  
  mVertices = tetrahedron.GetVertices();
  mFaces = tetrahedron.GetFaces();

  std::transform(mVertices.cbegin(), mVertices.cend(), mVertices.begin(),
    [&](const Vertex& vertex ){ return vertex + Vertex(0, 0, -height/2); });
  
  mFaces.push_back(Face({0,2,1}));
}
