#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <variant>

#include "Types.hpp"

enum class ObjectId {
  None = 0,
  Cube,
  CubeExt,
  Thorus,
  Tetrahedron,
  RegularTetrahedron,
  FractalTetrahedron,
  Composite,
  Square,
  Rectangle,
  Trapeze,
  //SquareHolePart1,
  //SquareHolePart2,
  Pyramid,
  Cone,
  Cylinder,
  TriangulatedCylinder,
  CSign,
  Star,
  Pentagram,
};

enum class ParamsId {
  AdditionalParams,
  ComponentsList,
  ComponentsParams,
  SinusParams,
  Params,
  ComponentsList0,
  ComponentsList1,
  ComponentsList2,
  ComponentsList3,
  ComponentsList4,
  ComponentsList5,
  ComponentsParams0,
  ComponentsParams1,
  ComponentsParams2,
  ComponentsParams3,
  ComponentsParams4,
  ComponentsParams5,
  Params0,
  Params1,
  Params2,
  Params3,
  Params4,
  Params5,
  TransformCmds0,
  TransformCmds1,
  TransformCmds2,
  TransformCmds3,
  TransformCmds4,
  TransformCmds5,
  PreferTriangles,
  NormalLength
};

using ParamsVector = std::vector<int>;
using SinusParamsVector = std::vector<double>;
using ComponentNamesVector = std::vector<std::string>;

using ParamsPair = std::pair<ParamsId, std::variant<IntVector, StringVector, SinusParamsVector, int>>;
using ParamsMap = std::map<ParamsId, std::variant<IntVector, StringVector, SinusParamsVector, int>>;

class Object3D;
using ComponentsVector = std::vector<std::unique_ptr<Object3D>>;
using ComponentTransformParamsPair = std::pair<ParamsVector, StringVector>;
using ComponentsWithParamsPair = std::pair<ComponentTransformParamsPair, std::unique_ptr<ComponentsVector>>;
using ComponentsWithParamsVector = std::vector<ComponentsWithParamsPair>;

