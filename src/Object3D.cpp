#include <iostream>
#include "Object3D.hpp"

std::ostream& operator<<(std::ostream& os, const Object3D& object)
{
  os << "Type: " << object.mName << "\n";
  os << "Vertices:" << "\n";
  os << object.mVertices;
  os << "Faces:" << "\n";
  os << object.mFaces;
  os << "Face normals:" << "\n";
  os << object.mNormalVectorsInFaces;
  os << "Vertice normals:" << "\n";
  os << object.mNormalVectorsInVertices;
  return os;
}
