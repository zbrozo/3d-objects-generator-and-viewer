#include <cmath>
#include <algorithm>
#include "RegularDodecahedron.hpp"
#include "RegularIcosahedron.hpp"
#include "Components.hpp"
#include "Tools.hpp"

namespace
{  

Vertex GetMiddle(const Vertices& vertices, const Face& face)
{
  const int x = (
    vertices[face[0]].getX()
    + vertices[face[1]].getX()
    + vertices[face[2]].getX())
    / 3;
  const int y = (vertices[face[0]].getY()
    + vertices[face[1]].getY()
    + vertices[face[2]].getY())
    / 3;
  const int z = (
    vertices[face[0]].getZ()
    + vertices[face[1]].getZ()
    + vertices[face[2]].getZ())
    / 3;
    
  return Vertex(x, y, z);
}

}

void RegularDodecahedron::Generate()
{
  RegularIcosahedron icosahedron("", 100);
  icosahedron.Generate();

  const auto& icosahedronVertices = icosahedron.GetVertices();
  const auto& icosahedronFaces = icosahedron.GetFaces();

  constexpr size_t facesCount = 12;
  constexpr size_t verticesInFaceCount = 5;
  
  const uint16_t f[facesCount][verticesInFaceCount] = {
    { 10, 11, 12, 13, 14 },
    { 19, 18, 17, 16, 15 },

    { 0, 1, 2, 11, 10 },
    { 2, 3, 4, 12, 11 },
    { 4, 5, 6, 13, 12 },
    { 6, 7, 8, 14, 13 },
    { 8, 9, 0, 10, 14 },

    { 15, 16, 3, 2, 1 },
    { 16, 17, 5, 4, 3 }, 
    { 17, 18, 7, 6, 5 }, 
    { 18, 19, 9, 8, 7 }, 
    { 19, 15, 1, 0, 9 }, 
  };

  for (size_t i = 0; i < facesCount; i++)
  {
    Face face;
    Vertices vertices;
    
    for (size_t v = 0; v < verticesInFaceCount; v++)
    {
      vertices.push_back(GetMiddle(icosahedronVertices, icosahedronFaces[f[i][v]]));
      face.push_back(v);
    }

    Faces faces;
    faces.push_back(face);
    
    Tools::Merge(mVertices, mFaces, vertices, faces);
  }
}
