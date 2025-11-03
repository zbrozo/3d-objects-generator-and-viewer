#include "Components.hpp"
#include "Rotation.hpp"
#include "Tools.hpp"
#include "Object3D.hpp"

#include <cmath>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <boost/log/trivial.hpp>

namespace
{
/*
auto CreateSideVertices(Vertices& vertices)
{
  std::vector<Vertices> allVertices;

  const size_t facesCount = 4;

  for (size_t i = 0; i < facesCount; ++i)
  {
    const auto rotatedVertices = vertices.Rotate(0, 0, i * 90);
    allVertices.push_back(rotatedVertices);
  }

  return allVertices;
}


auto CreateSideFaces(const std::vector<Vertices>& allVertices)
{
  Faces faces;
  Vertices vertices;

  for(const auto& tmpVertices : allVertices)
  {
    Face face{0,1,2,3};
    const auto [resultFace, resultVertices] = Tools::Merge(vertices, face, tmpVertices);
    vertices = resultVertices;
    faces.push_back(resultFace);
  }

  return std::make_pair(faces, vertices);
}
*/

Vertices CreateCircleVerticesExt(size_t count, size_t amount, int radius, int degree = 0)
{
  Vertex vertex(0, radius, 0);
  VertexRotation rotation;

  const int degStep = 360U / amount;

  Vertices circle;

  for (size_t i = 0; i < count; i++)
  {
    constexpr int scaleValue = 10;

    const Vertex v  = rotation.rotateZ(vertex * scaleValue, degree) / scaleValue;
    circle.push_back(v);

    degree += degStep;
  }

  return circle;
}

Vertices CreateCircleVertices(size_t amount, int radius, int degree = 0) {
  return CreateCircleVerticesExt(amount, amount , radius, degree);
}

} // namespace

namespace Components
{

void Square::Generate()
{
  Vertices vertices {
    {1, 1, 0},
    {-1, 1, 0},
    {-1, -1, 0},
    {1, -1, 0},
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(),
    [&](const Vertex& vertex)
    {
      return vertex * mSide / 2;
    });

  mFaces.push_back({0,1,2,3});
  mVertices = vertices;
}

void Rectangle::Generate()
{
  Vertices vertices {
    {1, 1, 0},
    {-1, 1, 0},
    {-1, -1, 0},
    {1, -1, 0},
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(),
    [&](const Vertex& vertex)
    {
      return Vertex(
        vertex.getX() * mSideX / 2,
        vertex.getY() * mSideY / 2,
        vertex.getZ());
    });

  mFaces.push_back({0,1,2,3});
  mVertices = vertices;
}

void Trapeze::Generate()
{
  Vertices vertices {
    {1, 1, 0},
    {-1, 1, 0},
    {-1, -1, 0},
    {1, -1, 0},
  };

  vertices[0] = Vertex(vertices[0].getX() * mTop /2, vertices[0].getY() * mHeight / 2, vertices[0].getZ());
  vertices[1] = Vertex(vertices[1].getX() * mTop /2, vertices[1].getY() * mHeight / 2, vertices[1].getZ());
  vertices[2] = Vertex(vertices[2].getX() * mBottom /2, vertices[2].getY() * mHeight / 2, vertices[2].getZ());
  vertices[3] = Vertex(vertices[3].getX() * mBottom /2, vertices[3].getY() * mHeight / 2, vertices[3].getZ());

  mFaces.push_back({0,1,2,3});
  mVertices = vertices;
}

void Pyramid::Generate()
{
  Vertices vertices {
    {1, 1, 0},
    {-1, 1, 0},
    {-1, -1, 0},
    {1, -1, 0},
    {0, 0, 0}
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(),
    [&](const Vertex& vertex)
    {
      return vertex * mSide;
    });

  vertices[4] = Vertex(
    vertices[4].getX(),
    vertices[4].getY(),
    vertices[4].getZ() + mHeight
    );

  mVertices = vertices;

  mFaces.push_back({0,1,4});
  mFaces.push_back({1,2,4});
  mFaces.push_back({2,3,4});
  mFaces.push_back({3,0,4});
}

void Cone::Generate()
{
  Vertices vertices = CreateCircleVertices(mCircleAmount, mCircleRadius);
  mVertices = vertices;

  mVertices.push_back(Vertex(0, 0, mHeight));

  const uint16_t last = mVertices.size() - 1;
  uint16_t nr = 0;

  if (mHeight >= 0)
  {
    for (;nr < mVertices.size()-2; ++nr)
    {
      mFaces.push_back({nr, uint16_t(nr + 1), last});
    }
    mFaces.push_back({nr, 0, last});
  }
  else
  {
    for (;nr < mVertices.size()-2; ++nr)
    {
      mFaces.push_back({uint16_t(nr + 1), nr, last});
    }
    mFaces.push_back({0, nr, last});
  }
}

void Cylinder::Generate()
{
  Vertices vertices = CreateCircleVertices(mCircleAmount, mCircleRadius);
  Vertices vertices2{vertices};

  std::transform(vertices2.cbegin(), vertices2.cend(), vertices2.begin(),
    [&](const Vertex& vertex)
    {
      return Vertex(vertex.getX(), vertex.getY(), vertex.getZ() - mHeight);
    });

  mVertices.insert(mVertices.end(), vertices.cbegin(), vertices.cend());
  mVertices.insert(mVertices.end(), vertices2.cbegin(), vertices2.cend());

  const auto size = vertices.size();

  uint16_t nr = 0;
  for (; nr < size - 1; ++nr)
  {
    mFaces.push_back(
      {
        nr,
        uint16_t(nr + size),
        uint16_t(nr + size + 1),
        uint16_t(nr + 1)
      });
  }

  mFaces.push_back(
    {
      nr,
      uint16_t(nr + size),
      uint16_t(size),
      uint16_t(0)
    });

}

void TriangulatedCylinder::Generate()
{
  Vertices vertices = CreateCircleVertices(mCircleAmount, mCircleRadius);
  Vertices vertices2 = CreateCircleVertices(mCircleAmount, mCircleRadius, 360 / mCircleAmount / 2);

  std::transform(vertices2.cbegin(), vertices2.cend(), vertices2.begin(),
    [&](const Vertex& vertex)
    {
      return Vertex(vertex.getX(), vertex.getY(), vertex.getZ() - mHeight);
    });

  mVertices.insert(mVertices.end(), vertices.cbegin(), vertices.cend());
  mVertices.insert(mVertices.end(), vertices2.cbegin(), vertices2.cend());

  const auto size = vertices.size();

  uint16_t nr = 0;

  for (; nr < size - 1; ++nr)
  {
    mFaces.push_back(
      {
        uint16_t(nr + 1),
        uint16_t(nr),
        uint16_t(nr + size),
      });

    mFaces.push_back(
      {
        uint16_t(nr + size),
        uint16_t(nr + size + 1),
        uint16_t(nr + 1),
      });
  }

  mFaces.push_back(
    {
      uint16_t(0),
      uint16_t(nr),
      uint16_t(nr + size),
    });

  mFaces.push_back(
    {
      uint16_t(nr + size),
      uint16_t(size),
      uint16_t(0),
    });
}

void Star::Generate()
{
  auto FindIntersectionPoint = [](Vertex v1begin, Vertex v1end, Vertex v2begin, Vertex v2end) {

    double a1 = 0;
    double b1 = 0;
    double a2 = 0;
    double b2 = 0;

    double d1y = v1end.getY() - v1begin.getY();
    double d1x = v1end.getX() - v1begin.getX();
    double d2y = v2end.getY() - v2begin.getY();
    double d2x = v2end.getX() - v2begin.getX();

    if (d1x != 0)
    {
      a1 = d1y / d1x;
    }

    b1 = v1begin.getY() - a1 * v1begin.getX();

    if (d2x != 0)
    {
      a2 = d2y / d2x;
    }

    b2 = v2begin.getY() - a2 * v2begin.getX();

    const int x = (b2 - b1) / (a1 - a2);
    const int y = a1 * x + b1;

    return Vertex(x, y, 0);
  };

  mVertices = CreateCircleVerticesExt(mCircleAmount, mCircleAmount, mCircleRadius);

  for (size_t i = 0; i < mCircleAmount; i++)
  {
    const int nr = static_cast<int>(i);

    auto p1s = (nr - 1 < 0) ? (nr - 1 + mCircleAmount) : (nr - 1);
    auto p1e = (nr + 1 >= mCircleAmount) ? (nr + 1 - mCircleAmount) : (nr + 1);
    auto p2s = nr;
    auto p2e = (nr + 2 >= mCircleAmount) ? (nr + 2 - mCircleAmount) : (nr + 2);

    const auto v = FindIntersectionPoint(mVertices[p1s], mVertices[p1e], mVertices[p2s], mVertices[p2e]);
    mVertices.push_back(v);
  }

  Face face;
  for (size_t i = 0; i < mCircleAmount; i++)
  {
    face.push_back(i);
    face.push_back(i+mCircleAmount);
  }

  mFaces.push_back(face);
}

} // namespace
