#include "Components.hpp"
#include "Rotation.hpp"
#include <algorithm>
#include <exception>

#include <cstdint>
#include <boost/log/trivial.hpp>
#include <cmath>
#include <stdexcept>

namespace
{

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
    const auto [resultFace, resultVertices] = Object3D::Merge(vertices, face, tmpVertices);
    vertices = resultVertices;
    faces.push_back(resultFace);
  }

  return std::make_pair(faces, vertices);
}

Vertices CreateCircleVerticesExt(int count, int amount, int radius, int degree = 0)
{
  Vertex vertex(0, radius, 0);
  VertexRotation rotation;

  const int degStep = 360 / amount;

  Vertices circle;

  for (int i = 0; i < count; i++)
  {
    constexpr int scaleValue = 10;

    const Vertex v  = rotation.rotateZ(vertex * scaleValue, degree) / scaleValue;
    circle.push_back(v);

    degree += degStep;
  }

  return circle;
}

Vertices CreateCircleVertices(int amount, int radius, int degree = 0) {
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
      return vertex * mSize;
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
        vertex.getX() * mSizeX,
        vertex.getY() * mSizeY,
        vertex.getZ());
    });

  mFaces.push_back({0,1,2,3});
  mVertices = vertices;
}

void SquareWithHolePart1::Generate()
{
  Vertices vertices {
    {1, 1, 0},
    {-1, 1, 0},
    {-1, 1, 0},
    {1, 1, 0},
  };

  Vertices verticesModify {
    {-1, -1, 0},
    {1, -1, 0},
    {1, -1, -1},
    {-1, -1, -1},
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(), [&](const Vertex& vertex){
    return vertex * mSize1;
  });

  std::transform(verticesModify.cbegin(), verticesModify.cend(), verticesModify.begin(), [&](const Vertex& vertex){
    return Vertex(vertex.getX() * mSize2, vertex.getY() * mSize2, vertex.getZ() * mSize3);
  });

  for (size_t i = 0; i < vertices.size(); i++)
  {
    auto& v1 = vertices.at(i);
    const auto& v2 = verticesModify.at(i);
    v1 = v1 + v2;
  }

  const auto allVertices = CreateSideVertices(vertices);
  const auto facesWithVertices = CreateSideFaces(allVertices);

  mFaces = facesWithVertices.first;
  mVertices = facesWithVertices.second;
}

void SquareWithHolePart2::Generate()
{
  Vertices vertices {
    {1, 1, 0},
    {-1, 1, 0},
    {-1, 1, 0},
    {1, 1, 0},
  };

  Vertices verticesModify {
    {0, 0, 0},
    {0, 0, 0},
    {1, -1, 0},
    {-1, -1, 0},
  };

  std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(), [&](const Vertex& vertex){
    return vertex * mSize1;
  });

  std::transform(verticesModify.cbegin(), verticesModify.cend(), verticesModify.begin(), [&](const Vertex& vertex){
    return Vertex(vertex.getX() * mSize2, vertex.getY() * mSize2, vertex.getZ());
  });

  for (size_t i = 0; i < vertices.size(); i++)
  {
    auto& v1 = vertices.at(i);
    const auto& v2 = verticesModify.at(i);
    v1 = v1 + v2;
  }

  const auto allVertices = CreateSideVertices(vertices);
  const auto facesWithVertices = CreateSideFaces(allVertices);

  mFaces = facesWithVertices.first;
  mVertices = facesWithVertices.second;
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
      return vertex * mSize1;
    });

  vertices[4] = Vertex(
    vertices[4].getX(),
    vertices[4].getY(),
    vertices[4].getZ() + mSize2
    );

  mVertices = vertices;

  mFaces.push_back({0,1,4});
  mFaces.push_back({1,2,4});
  mFaces.push_back({2,3,4});
  mFaces.push_back({3,0,4});
}

void Taper::Generate()
{

  Vertices vertices = CreateCircleVertices(mCircleAmount, mCircleRadius);
  vertices.push_back(Vertex(0, 0, mHeight));

  mVertices = vertices;

  unsigned short last = vertices.size() - 1;
  unsigned short nr = 0;

  if (mHeight >= 0)
  {
    for (;nr < vertices.size()-2; ++nr)
    {
      mFaces.push_back({nr, static_cast<unsigned short>(nr + 1), last});
    }
    mFaces.push_back({nr, 0, last});
  }
  else
  {
    for (;nr < vertices.size()-2; ++nr)
    {
      mFaces.push_back({static_cast<unsigned short>(nr + 1), nr, last});
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

  unsigned short nr = 0;
  for (; nr < size - 1; ++nr)
  {
    mFaces.push_back(
      {
        nr,
        static_cast<unsigned short>(nr + size),
        static_cast<unsigned short>(nr + size + 1),
        static_cast<unsigned short>(nr + 1)
      });
  }

  mFaces.push_back(
    {
      nr,
      static_cast<unsigned short>(nr + size),
      static_cast<unsigned short>(size),
      static_cast<unsigned short>(0)
    });

}

void CylinderTriangles::Generate()
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

  unsigned short nr = 0;

  for (; nr < size - 1; ++nr)
  {
    mFaces.push_back(
      {
        static_cast<unsigned short>(nr + 1),
        static_cast<unsigned short>(nr),
        static_cast<unsigned short>(nr + size),
      });

    mFaces.push_back(
      {
        static_cast<unsigned short>(nr + size),
        static_cast<unsigned short>(nr + size + 1),
        static_cast<unsigned short>(nr + 1),
      });
  }

  mFaces.push_back(
    {
      static_cast<unsigned short>(0),
      static_cast<unsigned short>(nr),
      static_cast<unsigned short>(nr + size),
    });

  mFaces.push_back(
    {
      static_cast<unsigned short>(nr + size),
      static_cast<unsigned short>(size),
      static_cast<unsigned short>(0),
    });
}

void CSign::Generate()
{
  auto Translate = [](Vertices& vertices, int x, int y, int z) {
    std::transform(vertices.cbegin(), vertices.cend(), vertices.begin(),
      [&](const Vertex& vertex)
      {
        return Vertex(vertex.getX() + x, vertex.getY() + y, vertex.getZ() + z);
      });
  };

  Vertices vertices1 = CreateCircleVerticesExt(mCircleAmount/2 + 1, mCircleAmount, mCircle1Radius);
  Vertices vertices2 = vertices1;
  Vertices vertices3 = CreateCircleVerticesExt(mCircleAmount/2 + 1, mCircleAmount, mCircle2Radius);
  Vertices vertices4 = vertices3;

  Translate(vertices1, mCircle1Offset, 0, mWidth);
  Translate(vertices2, mCircle1Offset, 0, -mWidth);
  Translate(vertices3, mCircle2Offset, 0, mWidth);
  Translate(vertices4, mCircle2Offset, 0, -mWidth);

  mVertices.insert(mVertices.end(), vertices1.cbegin(), vertices1.cend());
  mVertices.insert(mVertices.end(), vertices2.cbegin(), vertices2.cend());
  mVertices.insert(mVertices.end(), vertices3.cbegin(), vertices3.cend());
  mVertices.insert(mVertices.end(), vertices4.cbegin(), vertices4.cend());

  const auto size = vertices1.size();

  unsigned short nr = 0;

  for (; nr < size - 1; ++nr)
  {
    mFaces.push_back(
      {
        static_cast<unsigned short>(nr + 1),
        static_cast<unsigned short>(nr),
        static_cast<unsigned short>(nr + size),
        static_cast<unsigned short>(nr + size + 1)
      });
    mFaces.push_back(
      {
        static_cast<unsigned short>(nr + 2*size),
        static_cast<unsigned short>(nr + 2*size + 1),
        static_cast<unsigned short>(nr + 2*size + size + 1),
        static_cast<unsigned short>(nr + 2*size + size)
      });
    mFaces.push_back(
      {
        static_cast<unsigned short>(nr + 2*size),
        static_cast<unsigned short>(nr),
        static_cast<unsigned short>(nr + 1),
        static_cast<unsigned short>(nr + 2*size + 1)
      });
    mFaces.push_back(
      {
        static_cast<unsigned short>(nr + size),
        static_cast<unsigned short>(nr + 3*size),
        static_cast<unsigned short>(nr + 3*size + 1),
        static_cast<unsigned short>(nr + size + 1)
      });
  }

  mFaces.push_back(
    {
      static_cast<unsigned short>(size),
      static_cast<unsigned short>(0),
      static_cast<unsigned short>(2*size),
      static_cast<unsigned short>(3*size)
    });
  mFaces.push_back(
    {
      uint16_t(size-1),
      uint16_t(2*size-1),
      uint16_t(4*size-1),
      uint16_t(3*size-1)
    });
}

} // namespace
