#pragma once

#include "Object3D.hpp"
#include "Types.hpp"

namespace Tools
{
Object3D CreateNormalVectors(const Object3D& object, int normalLength);

void Translate(Vertices& vertices, int x, int y, int z);

void Transform(Vertices& vertices, const StringVector& commands);

void Rotate(Vertices& vertices, int degX, int degY, int degZ);
  
void Merge(Vertices& destVertices,
           Faces& destFaces,
           const Vertices& srcVertices,
           const Faces& srcFaces);

std::pair<Face, Vertices> Merge(const Vertices& objectVertices,
                                const Face& face,
                                const Vertices& vertices);

int GetDistance(Vertex v1, Vertex v2);

} // namespace Tools
