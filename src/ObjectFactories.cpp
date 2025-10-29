#include "ObjectFactories.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "Object3D.hpp"
#include "Tetrahedron.hpp"
#include "Thorus.hpp"
#include "Composite.hpp"
#include "Tetrahedron.hpp"
#include "RegularTetrahedron.hpp"
#include "FractalTetrahedron.hpp"
#include "Pentagram.hpp"

#include "Components.hpp"
#include "Params.hpp"
#include "FileLoader.hpp"
#include "FileFormatConverter.hpp"
#include "Types.hpp"

#include <cctype>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <iostream>

#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>

using namespace std::placeholders;

namespace
{

std::map<std::string, ObjectId> ComponentIdMap {
  {"square", ObjectId::Square},
  {"rectangle", ObjectId::Rectangle},
  {"trapeze", ObjectId::Trapeze},
  {"pyramid", ObjectId::Pyramid},
  {"cone", ObjectId::Cone},
  {"cylinder", ObjectId::Cylinder},
  {"triangulatedcylinder", ObjectId::TriangulatedCylinder},
  {"star", ObjectId::Star},
};

auto findParamsVector = [](const ParamsPair& params,  ParamsId id)
{
  return params.first == id;
};

auto getParam(const ParamsVector& values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<int>{values[index]};
  }

  return std::optional<int>();
}

auto getParam(const SinusParamsVector& values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<double>{values[index]};
  }

  return std::optional<double>();
}

} // namespace

std::unique_ptr<Object3D> CubeFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  const auto nameExt = CreateFullName(name, params);

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    return std::make_unique<Cube>(nameExt.c_str(), std::get<ParamsVector>(it->second).at(0));
  }

  return std::make_unique<Cube>(nameExt.c_str());
}

std::unique_ptr<Object3D> CubeExtFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  ParamsVector paramsVector;
  ParamsVector componentParamsVector;

  // find parameters

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::ComponentsParams)); it != params.end())
  {
    componentParamsVector = std::get<ParamsVector>(it->second);
  }

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::Params)); it != params.end())
  {
    paramsVector = std::get<ParamsVector>(it->second);
  }

  // create all the listed components

  auto components = std::make_unique<ComponentsVector>();
  const auto& componentNames =  std::get<ComponentNamesVector>(params.at(ParamsId::ComponentsList));

  for (auto name : componentNames)
  {
    boost::algorithm::to_lower(name);
    const auto id = ComponentIdMap[name];
    BOOST_LOG_TRIVIAL(trace) << "Found component: " << name << " " << std::to_string(static_cast<int>(id));
    components->push_back(std::move(GetComponentFactories().at(id)->Create(componentParamsVector)));
  }

  // join parameters with the components

  StringVector cmds;
  auto componentsWithParamsVector = std::make_unique<ComponentsWithParamsVector>();

  componentsWithParamsVector->push_back(
    ComponentsWithParamsPair(std::make_pair(paramsVector, cmds), std::move(components)));

  return std::make_unique<CubeExt>(
    CreateFullName(name, params).c_str(),
    std::move(componentsWithParamsVector));
}

std::unique_ptr<Object3D> ThorusFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  ParamsVector foundParams;
  SinusParamsVector foundSinusParams;
  StringVector founSinus;
  bool preferTriangles = false;

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    foundParams = std::get<ParamsVector>(params.at(ParamsId::AdditionalParams));
  }

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::SinusParams)); it != params.end())
  {
    foundSinusParams = std::get<SinusParamsVector>(params.at(ParamsId::SinusParams));
  }

  auto preferTrianglesIt = params.find(ParamsId::PreferTriangles);
  if (preferTrianglesIt != params.end())
  {
    preferTriangles =  std::get<int>(preferTrianglesIt->second);
  }

  return std::make_unique<Thorus>(
    CreateFullName(name, params).c_str(),
    getParam(foundParams, 0),
    getParam(foundParams, 1),
    getParam(foundParams, 2),
    getParam(foundParams, 3),
    getParam(foundParams, 4),
    getParam(foundParams, 5),
    getParam(foundParams, 6),

    getParam(foundSinusParams, 0),
    getParam(foundSinusParams, 1),
    getParam(foundSinusParams, 2),
    getParam(foundSinusParams, 3),
    getParam(foundSinusParams, 4),
    getParam(foundSinusParams, 5),
    getParam(foundSinusParams, 6),
    getParam(foundSinusParams, 7),
    getParam(foundSinusParams, 8),
    getParam(foundSinusParams, 9),
    getParam(foundSinusParams, 10),
    getParam(foundSinusParams, 11),
    preferTriangles);
}

std::unique_ptr<Object3D> CompositeFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  auto componentsWithParamsVector = std::make_unique<ComponentsWithParamsVector>();

  auto create = [&params, &componentsWithParamsVector, &name, this]
    (ParamsId listId, ParamsId paramsId, ParamsId mainParamsId, ParamsId transformCmdsId)
  {
    auto components = std::make_unique<ComponentsVector>();

    ParamsVector paramsVector;
    ParamsVector mainParamsVector;
    StringVector transformCmds;

    if (auto it = std::find_if(params.begin(), params.end(),
        std::bind(findParamsVector, _1,  paramsId)); it != params.end())
    {
      paramsVector = std::get<ParamsVector>(it->second);
    }

    if (auto it = std::find_if(params.begin(), params.end(),
        std::bind(findParamsVector, _1,  mainParamsId)); it != params.end())
    {
      mainParamsVector = std::get<ParamsVector>(it->second);
    }

    if (auto it = std::find_if(params.begin(), params.end(),
        std::bind(findParamsVector, _1,  transformCmdsId)); it != params.end())
    {
      transformCmds = std::get<StringVector>(it->second);
    }

    if (auto it = std::find_if(params.begin(), params.end(),
        std::bind(findParamsVector, _1,  listId)); it != params.end())
    {
      const auto& names = std::get<ComponentNamesVector>(it->second);

      for (auto name : names)
      {
        boost::algorithm::to_lower(name);

        if (ComponentIdMap.find(name) == ComponentIdMap.end())
        {
            FileLoader loader(name);
            auto buffer = loader.Load();

            FileFormatConverter converter;
            auto object = std::make_unique<Object3D>(converter.ConvertToObject(buffer));

            BOOST_LOG_TRIVIAL(trace) << "Loaded component: " << name;

            components->push_back(std::move(object));
        }
        else
        {
            const auto id = ComponentIdMap[name];

            BOOST_LOG_TRIVIAL(trace) << "Found component: " << name << " " << std::to_string(static_cast<int>(id));

            components->push_back(
              std::move(GetComponentFactories().at(id)->Create(paramsVector)));
        }
      }
    }

    componentsWithParamsVector->push_back(
      ComponentsWithParamsPair(std::make_pair(mainParamsVector, transformCmds), std::move(components)));
  };

  create(ParamsId::ComponentsList0, ParamsId::ComponentsParams0, ParamsId::Params0, ParamsId::TransformCmds0);
  create(ParamsId::ComponentsList1, ParamsId::ComponentsParams1, ParamsId::Params1, ParamsId::TransformCmds1);
  create(ParamsId::ComponentsList2, ParamsId::ComponentsParams2, ParamsId::Params2, ParamsId::TransformCmds2);
  create(ParamsId::ComponentsList3, ParamsId::ComponentsParams3, ParamsId::Params3, ParamsId::TransformCmds3);
  create(ParamsId::ComponentsList4, ParamsId::ComponentsParams4, ParamsId::Params4, ParamsId::TransformCmds4);
  create(ParamsId::ComponentsList5, ParamsId::ComponentsParams5, ParamsId::Params5, ParamsId::TransformCmds5);

  return std::make_unique<Composite>(
    CreateFullName(name, params).c_str(),
    std::move(componentsWithParamsVector));
}

std::unique_ptr<Object3D> TetrahedronFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  const auto nameExt = CreateFullName(name, params);

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    return std::make_unique<Tetrahedron>(
      nameExt.c_str(),
      std::get<ParamsVector>(it->second).at(0),
      std::get<ParamsVector>(it->second).at(1)
      );
  }
  return std::make_unique<Tetrahedron>(nameExt.c_str());
}

std::unique_ptr<Object3D> RegularTetrahedronFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  const auto nameExt = CreateFullName(name, params);

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    return std::make_unique<RegularTetrahedron>(
      nameExt.c_str(),
      std::get<ParamsVector>(it->second).at(0)
      );
  }

  return std::make_unique<RegularTetrahedron>(nameExt.c_str());
}

std::unique_ptr<Object3D> FractalTetrahedronFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  const auto nameExt = CreateFullName(name, params);

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    return std::make_unique<FractalTetrahedron>(
      nameExt.c_str(),
      std::get<ParamsVector>(it->second).at(0)
      );
  }

  return std::make_unique<FractalTetrahedron>(nameExt.c_str());
}

std::unique_ptr<Object3D> PentagramFactory::FactoryMethod(
  const std::string& name,
  const ParamsMap& params) const
{
  const auto nameExt = CreateFullName(name, params);

  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::AdditionalParams)); it != params.end())
  {
    return std::make_unique<Pentagram>(
      nameExt.c_str(),
      std::get<ParamsVector>(it->second).at(0)
      );
  }

  return std::make_unique<Pentagram>(nameExt.c_str());
}
