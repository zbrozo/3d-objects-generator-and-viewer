#include "Tetrahedron.hpp"
#include "Components.hpp"
#include <cmath>

void Tetrahedron::Generate()
{
  Components::Cone tetrahedron(3, mRadius, mHeight);
  tetrahedron.Generate();

  mVertices = tetrahedron.GetVertices();
  mFaces = tetrahedron.GetFaces();

  mFaces.push_back(Face({0,2,1}));
}
