#include "Params.hpp"
#include "Types.hpp"
#include "Rotation.hpp"
#include "Thorus.hpp"
#include "ObjectParamValidators.hpp"

#include <algorithm>
#include <iostream>

namespace {

template <typename T> constexpr auto pi = T(3.14159265);

auto getRadian(double deg) { return deg * pi<double> / 180.0; }

Face CreateFace(int face1, int face2, int face3)
{
  Face face;
  face.push_back(face1);
  face.push_back(face2);
  face.push_back(face3);
  return face;
}

Face CreateFace(int face1, int face2, int face3, int face4)
{
  Face face;
  face.push_back(face1);
  face.push_back(face2);
  face.push_back(face3);
  face.push_back(face4);
  return face;
}

Faces CreateFacesInCircle(
  bool preferTriangles,
  int ringIndex,
  int circleSize,
  int begin,
  int count,
  bool last = false)
{
  if (begin + count > circleSize)
  {
    // error
    return Faces();
  }

  Faces faces;

  for (int rowIndex = 0; rowIndex < count; rowIndex++)
  {
    int faceNr1 = 0;
    int faceNr2 = 0;
    int faceNr3 = 0;
    int faceNr4 = 0;

    const int pos = ringIndex * circleSize + begin;
    const int next = last ? begin : (pos + circleSize);

    if ((begin + count) == circleSize &&
      (begin + rowIndex) == (circleSize - 1))
    {
      faceNr1 = pos - begin;
      faceNr2 = pos + rowIndex;
      faceNr3 = next + rowIndex;
      faceNr4 = next - begin;
    }
    else
    {
      faceNr1 = pos + rowIndex + 1;
      faceNr2 = pos + rowIndex;
      faceNr3 = next + rowIndex;
      faceNr4 = next + rowIndex + 1;
    }

    if (preferTriangles)
    {
      faces.push_back(CreateFace(faceNr1, faceNr2, faceNr3));
      faces.push_back(CreateFace(faceNr1, faceNr3, faceNr4));
    }
    else
    {
      faces.push_back(CreateFace(faceNr1, faceNr2, faceNr3, faceNr4));
    }
  }

  return faces;
}

} // namespace

Vertices Thorus::CreateCircleVertices()
{
  Vertex vertex(0, 0, mCircleRadius);
  VertexRotation rotation;

  const auto degStep = 360.0 / mCircleAmount;
  int degree = 0;

  Vertices circle;

  // obrót w X punktu aby utworzyć "okrąg"
  for (int i = 0; i < mCircleAmount; i++)
  {
    const int d = degree;
    circle.push_back(rotation.rotateX(vertex, d));
    degree += degStep;
  }

  return circle;
}

Vertices Thorus::CreateRingVertices(Vertices circle)
{
  Vertices vertices;
  VertexRotation rotation;

  const auto degStep = 360.0 / mRingAmount;

  const int count = (mRingAmount == mRingAmount2) ?  mRingAmount : (mRingAmount2 + 1);

  // obrót w Z okręgu tworzy torus
  for (int i = 0; i < count; i++)
  {
    Vertices transformedCircle = circle;

    std::transform(transformedCircle.cbegin(), transformedCircle.cend(), transformedCircle.begin(),
      [&](const Vertex& vertex){ 
        Vertex v = rotation.rotateX(vertex, mCircleRotStartDeg + mCircleRotStepDeg * i); 
        v = v + Vertex(0, mCircleOffset, 0);
        return v;
      });

    transformedCircle = ApplySinusToCircle(transformedCircle, i);

    for (const auto& v : transformedCircle)
    {
      const auto degree = degStep * i;
      const int d = degree;
      vertices.push_back(rotation.rotateZ(v, d));
    }
  }

  return vertices;
}

Faces Thorus::CreateFacesInRing(int begin, int count)
{
  const bool ringIsClosed = mRingAmount == mRingAmount2;

  Faces facesInRing;
  for (int ringIndex = 0; ringIndex < mRingAmount2; ++ringIndex)
  {
    const bool lastElementInRing = ringIsClosed && (ringIndex == (mRingAmount - 1));
    
    Faces faces = CreateFacesInCircle(mPreferTriangles, ringIndex, mCircleAmount, begin, count, lastElementInRing);

    for (const auto& f : faces)
    {
      facesInRing.push_back(f);
    }
  }

  return facesInRing;
}

Vertices Thorus::ApplySinusToCircle(const Vertices& vertices, int index)
{
  Vertices resultVertices;

  auto calcTranslation = [&](double m, double amp)
  {
    const auto translation = 360.0 / mRingAmount * m;
    return sin(getRadian(translation * index)) * amp;
  };

  const auto translationX = calcTranslation(mCircleSinusStepX, mCircleSinusAmpX);
  const auto translationY = calcTranslation(mCircleSinusStepY, mCircleSinusAmpY);
  const auto translationZ = calcTranslation(mCircleSinusStepZ, mCircleSinusAmpZ);

  for (auto& v : vertices)
  {
    resultVertices.push_back(Vertex(
        v.getX() + translationX,
        v.getY() + translationY,
        v.getZ() + translationZ)
      );
  }

  return resultVertices;
}

Vertices Thorus::ApplySinusToRing(const Vertices& vertices)
{
  Vertices resultVertices;

  double addX = 0;
  double addY = 0;
  double addZ = 0;

  int i = 0;
  for (auto& v : vertices)
  {
    auto calcTranslation = [&](double m, double amp){
      const auto deg = 360.0 / mCircleAmount * m;
      return sin(getRadian(deg)) * amp;
    };

    const auto translationX = calcTranslation(addX, mRingSinusAmpX);
    const auto translationY = calcTranslation(addY, mRingSinusAmpY);
    const auto translationZ = calcTranslation(addZ, mRingSinusAmpZ);

    resultVertices.push_back(Vertex(
        v.getX() + translationX,
        v.getY() + translationY,
        v.getZ() + translationZ)
      );

    ++i;

    if (i == mCircleAmount)
    {
      addX += mRingSinusStepX;
      addY += mRingSinusStepY;
      addZ += mRingSinusStepZ;
      i = 0;
    }
  }

  return resultVertices;
}

Thorus::Thorus(
  const char* name,
  std::optional<int> circleAmount,
  std::optional<int> ringAmount,
  std::optional<int> circleRadius,
  std::optional<int> circleOffset,
  std::optional<int> ringAmount2,
  std::optional<int> circleRotStartDeg,
  std::optional<int> circleRotStepDeg,
  std::optional<double> circleSinusStepX,
  std::optional<double> circleSinusAmpX,
  std::optional<double> circleSinusStepY,
  std::optional<double> circleSinusAmpY,
  std::optional<double> circleSinusStepZ,
  std::optional<double> circleSinusAmpZ,
  std::optional<double> ringSinusStepX,
  std::optional<double> ringSinusAmpX,
  std::optional<double> ringSinusStepY,
  std::optional<double> ringSinusAmpY,
  std::optional<double> ringSinusStepZ,
  std::optional<double> ringSinusAmpZ,
  bool preferTriangles
  ) :
  Object3D(name),
  mPreferTriangles(preferTriangles)
{
  SetParam<int>(mCircleAmount, circleAmount, std::bind(IntValidator, std::placeholders::_1, 3, std::nullopt));
  SetParam<int>(mRingAmount, ringAmount, std::bind(IntValidator, std::placeholders::_1, 3, std::nullopt));
  SetParam<int>(mCircleRadius, circleRadius, std::bind(IntValidator, std::placeholders::_1, std::nullopt, std::nullopt));
  SetParam<int>(mCircleOffset, circleOffset, std::bind(IntValidator, std::placeholders::_1, std::nullopt, std::nullopt));
  SetParam<int>(mRingAmount2, ringAmount2, std::bind(IntValidator, std::placeholders::_1, 0, mRingAmount));
  SetParam<int>(mCircleRotStartDeg, circleRotStartDeg);
  SetParam<int>(mCircleRotStepDeg, circleRotStepDeg);

  // Sinus transformation parameters
  SetParam<double>(mCircleSinusStepX, circleSinusStepX);
  SetParam<double>(mCircleSinusStepY, circleSinusStepY);
  SetParam<double>(mCircleSinusStepZ, circleSinusStepZ);
  SetParam<double>(mCircleSinusAmpX, circleSinusAmpX);
  SetParam<double>(mCircleSinusAmpY, circleSinusAmpY);
  SetParam<double>(mCircleSinusAmpZ, circleSinusAmpZ);
  SetParam<double>(mRingSinusStepX, ringSinusStepX);
  SetParam<double>(mRingSinusStepY, ringSinusStepY);
  SetParam<double>(mRingSinusStepZ, ringSinusStepZ);
  SetParam<double>(mRingSinusAmpX, ringSinusAmpX);
  SetParam<double>(mRingSinusAmpY, ringSinusAmpY);
  SetParam<double>(mRingSinusAmpZ, ringSinusAmpZ);
}

void Thorus::Generate()
{
  if (0 == mRingAmount2)
  {
    mRingAmount2 = mRingAmount;
  }

  Vertices circle { CreateCircleVertices() };

  mVertices = ApplySinusToRing(CreateRingVertices(circle));
  
  /// --- Faces ---
  
  if (mCircleAmount == 3)
  {
    auto faces = CreateFacesInRing(0, mCircleAmount);

    for (const auto& face : faces)
    {
      mFaces.push_back(face);
    }
  }
  else if (mCircleAmount > 3)
  {
    auto internalFaces = CreateFacesInRing(0, mCircleAmount/2);

    for (const auto& face : internalFaces)
    {
      mFaces.push_back(face);
    }

    auto externalFaces = CreateFacesInRing(mCircleAmount/2, mCircleAmount/2);
    
    for (const auto& face : externalFaces)
    {
      mFaces.push_back(face);
    }
  }
  
  // optional add closing faces 
  if (mRingAmount != mRingAmount2)
  {
    Face face1;
    for (int i = 0; i < mCircleAmount; i++)
    {
      face1.push_back(i);
    }

    Face face2;
    for (int i = mCircleAmount - 1; i >= 0; --i)
    {
      face2.push_back(mCircleAmount * mRingAmount2 +  i);
    }

    mFaces.push_back(face1);
    mFaces.push_back(face2);
  }
}
