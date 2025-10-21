#include "Components.hpp"
#include "Pentagram.hpp"
#include <cmath>
#include <algorithm>

void Pentagram::Generate()
{
  const size_t circleCornerCount = 5;
  const size_t circleRadius = 72;

  auto Translate = [](Vertices& vertices, int x, int y, int z) {
    std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(),
      [&](const Vertex& vertex)
      {
        return Vertex(vertex.getX() + x, vertex.getY() + y, vertex.getZ() + z);
      });
  };

  Components::Star star(circleCornerCount, circleRadius);
  star.Generate();

  for (Face f : star.GetFaces())
  {
    std::reverse(f.begin(), f.end());
    mFaces.push_back(f);
  }

  for (Face f : star.GetFaces())
  {
    for (auto& value : f)
    {
      value += 2 * circleCornerCount;
    }
    mFaces.push_back(f);
  }

  for (size_t i = 0; i < circleCornerCount; i++)
  {
    if (i == 0)
    {
      Face face;
      face.push_back(2 * circleCornerCount - 1);
      face.push_back(0);
      face.push_back(2 * circleCornerCount);
      face.push_back(4 * circleCornerCount - 1);
      mFaces.push_back(face);
    }
    else
    {
      Face face;
      face.push_back(i + circleCornerCount - 1);
      face.push_back(i);
      face.push_back(i + 2 * circleCornerCount);
      face.push_back(i + 3 * circleCornerCount - 1);
      mFaces.push_back(face);
    }

    Face face;
    face.push_back(i);
    face.push_back(i + circleCornerCount);
    face.push_back(i + 3 * circleCornerCount);
    face.push_back(i + 2 * circleCornerCount);
    mFaces.push_back(face);
  }

  for (size_t i = 0; i < circleCornerCount - 1; i++)
  {
    if (i == 0)
    {
      Face face;
      face.push_back(circleCornerCount);
      face.push_back(2 * circleCornerCount - 1);
      face.push_back(4 * circleCornerCount - 1);
      face.push_back(3 * circleCornerCount);
      mFaces.push_back(face);
    }

    Face face;
    face.push_back(i + circleCornerCount);
    face.push_back(i + 3*circleCornerCount);
    face.push_back(i + 3*circleCornerCount + 1);
    face.push_back(i + circleCornerCount + 1);
    mFaces.push_back(face);
  }

  Vertices tmp = star.GetVertices();
  Translate(tmp, 0, 0, -mDistance/2);
  mVertices = tmp;
  Translate(tmp, 0, 0, mDistance);
  mVertices.insert(mVertices.end(), tmp.cbegin(), tmp.cend());
}
