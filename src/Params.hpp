#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>
#include <variant>

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
  SquareHolePart1,
  SquareHolePart2,
  Pyramid,
  Cone,
  Cylinder,
  CylinderWithTriangularFaces,
  CSign,
  Star,
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
  Script0,
  Script1,
  Script2,
  Script3,
  Script4,
  Script5,
  PreferTriangles,
  NormalLength
};

using IntVector = std::vector<int>;
using StringVector = std::vector<std::string>;

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

