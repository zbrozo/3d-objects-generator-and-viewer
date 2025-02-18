#include "Tetrahedron.hpp"
#include "Components.hpp"
#include <cmath>

void Tetrahedron::Generate()
{
  Components::Cone tmp(3, mRadius, 0);
  tmp.Generate();

  auto vertices = tmp.GetVertices();
  const auto xLen = std::abs(vertices[0].getX() - vertices[1].getX());
  const auto yLen = std::abs(vertices[0].getY() - vertices[1].getY());
  const auto len = std::sqrt(std::pow(xLen, 2) + std::pow(yLen, 2));
  const auto height  = std::sqrt(std::pow(len * std::sqrt(3) / 2, 2) - std::pow(len / 3, 2));

  Components::Cone tetrahedron(3, mRadius, height);
  tetrahedron.Generate();

  mVertices = tetrahedron.GetVertices();
  mFaces = tetrahedron.GetFaces();

  mFaces.push_back(Face({0,2,1}));
}
