#include <cmath>
#include <algorithm>
#include "RegularIcosahedron.hpp"
#include "Components.hpp"

void RegularIcosahedron::Generate()
{
  Components::Cone cone(5, mRadius, 0);
  cone.Generate();

  auto faces = cone.GetFaces();
  auto vertices = cone.GetVertices();

  auto v0 = faces[0][0];
  auto v1 = faces[0][1];
  
  auto len = std::sqrt(
    std::pow(
      std::abs(vertices[v0].getX() - vertices[v1].getX()),
      2)
    + 
    std::pow(
      std::abs(vertices[v0].getY() - vertices[v1].getY()),
      2)
    +
    std::pow(
      std::abs(vertices[v0].getZ() - vertices[v1].getZ()),
      2)
    );

  int height = (std::sqrt(3.0)/2.0) * len;

  Components::Cylinder cylinder(5, mRadius, height/2);
  cylinder.Generate();

  mVertices = cylinder.GetVertices();
  mFaces = cylinder.GetFaces();
  
   // auto vertices = cone.GetVertices();
  // const auto xLen = std::abs(vertices[0].getX() - vertices[1].getX());
  // const auto yLen = std::abs(vertices[0].getY() - vertices[1].getY());
  // const auto len = std::sqrt(std::pow(xLen, 2) + std::pow(yLen, 2));
  // const auto height = std::sqrt(6.0) * len / 3.0;

  // Components::Cone tetrahedron(3, mRadius, height);
  // tetrahedron.Generate();
  
  // mVertices = tetrahedron.GetVertices();
  // mFaces = tetrahedron.GetFaces();

  // std::transform(mVertices.cbegin(), mVertices.cend(), mVertices.begin(),
  //   [&](const Vertex& vertex ){ return vertex + Vertex(0, 0, -height/2); });
  
  // mFaces.push_back(Face({0,2,1}));
}
