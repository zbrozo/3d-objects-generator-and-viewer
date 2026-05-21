#include <cmath>
#include <algorithm>
#include "RegularIcosahedron.hpp"
#include "Components.hpp"
#include "Tools.hpp"
#include "Rotation.hpp"

void RegularIcosahedron::Generate()
{
  Components::Cone tmpCone(5, mRadius, 0);
  tmpCone.Generate();

  auto faces = tmpCone.GetFaces();
  auto vertices = tmpCone.GetVertices();

  auto v0 = faces[0][0];
  auto v1 = faces[0][1];
  
  auto len = Tools::GetDistance(vertices[v0], vertices[v1]);
  auto height = std::sqrt(3.0) * len / 2.0;

  Components::Cylinder cylinder(5, mRadius, height);
  cylinder.SetTraingulated();
  cylinder.Generate();

  Vertices vertices2 = cylinder.GetVertices();
  Tools::Translate(vertices2, 0, 0, height/2);
  
  mVertices = vertices2;
  mFaces = cylinder.GetFaces();

  Components::Cone cone1(5, mRadius, mRadius/2);
  cone1.Generate();
  vertices2 = cone1.GetVertices();
  Tools::Translate(vertices2, 0, 0, height/2);
  Tools::Merge(mVertices, mFaces, vertices2, cone1.GetFaces());
    
  Components::Cone cone2(5, mRadius, -mRadius/2);
  cone2.Generate();
  vertices2 = cone2.GetVertices();
  Tools::Rotate(vertices2, 0, 0, 36);
  Tools::Translate(vertices2, 0, 0, -height/2);
  Tools::Merge(mVertices, mFaces, vertices2, cone2.GetFaces());
}
