#ifndef _THORUS_HPP_
#define _THORUS_HPP_

#include "Object3D.hpp"
#include "IGenerator.hpp"
#include <optional>

class Thorus : public Object3D, public IGenerator
{
  int mCircleAmount = 0;
  int mRingAmount = 0;
  int mCircleRadius = 0;
  int mCircleOffset = 0;

  int mRingAmount2 = 0;
  int mCircleRotStartDeg = 0;
  int mCircleRotStepDeg = 0;

  double mCircleSinusStepX = 0.0;
  double mCircleSinusAmpX = 0.0;
  double mCircleSinusStepY = 0.0;
  double mCircleSinusAmpY = 0.0;
  double mCircleSinusStepZ = 0.0;
  double mCircleSinusAmpZ = 0.0;
  double mRingSinusStepX = 0.0;
  double mRingSinusAmpX = 0.0;
  double mRingSinusStepY = 0.0;
  double mRingSinusAmpY = 0.0;
  double mRingSinusStepZ = 0.0;
  double mRingSinusAmpZ = 0.0;
  bool mPreferTriangles = false;

public:

  Thorus(
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
    );

  virtual ~Thorus() = default;

  Thorus(Thorus const &) = delete;
  Thorus(Thorus &&) = delete;
  Thorus& operator=(const Thorus& v) = delete;
  Thorus& operator=(Thorus &&) = delete;

  virtual void Generate() override;

private:

  Vertices CreateCircleVertices();
  Vertices CreateRingVertices(Vertices circle);
  Faces CreateFacesInRing(int begin, int count);
  
  Vertices ApplySinusToRing(const Vertices& vertices);
  Vertices ApplySinusToCircle(const Vertices& vertices, int index);

};

#endif
