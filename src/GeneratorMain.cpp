#include "IGenerator.hpp"
#include "Face.hpp"
#include "Object3D.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "Tetrahedron.hpp"
#include "Thorus.hpp"
#include "Pentagram.hpp"
#include "ObjectFactories.hpp"
#include "ComponentFactories.hpp"
#include "FileSaver.hpp"
#include "Params.hpp"
#include "FileFormatConverter.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <array>
#include <map>
#include <memory>
#include <utility>

#include <boost/program_options.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace po = boost::program_options;

std::map<std::string, ObjectId> ObjectIdMap {
  {"cube", ObjectId::Cube},
  {"cube-ext", ObjectId::CubeExt},
  {"thorus", ObjectId::Thorus},
  {"composite", ObjectId::Composite},
  {"tetrahedron", ObjectId::Tetrahedron},
  {"regulartetrahedron", ObjectId::RegularTetrahedron},
  {"fractaltetrahedron", ObjectId::FractalTetrahedron},
  {"pentagram", ObjectId::Pentagram}
};

using ObjectFactoryMap = std::map<ObjectId, std::unique_ptr<ObjectFactoryBase>>;

void InitObjectFactoryMap(ObjectFactoryMap& objectFactoryMap)
{
  objectFactoryMap[ObjectId::Cube] = std::make_unique<CubeFactory>();
  objectFactoryMap[ObjectId::CubeExt] = std::make_unique<CubeExtFactory>();
  objectFactoryMap[ObjectId::Thorus] = std::make_unique<ThorusFactory>();
  objectFactoryMap[ObjectId::Composite] = std::make_unique<CompositeFactory>();
  objectFactoryMap[ObjectId::Tetrahedron] = std::make_unique<TetrahedronFactory>();
  objectFactoryMap[ObjectId::RegularTetrahedron] = std::make_unique<RegularTetrahedronFactory>();
  objectFactoryMap[ObjectId::FractalTetrahedron] = std::make_unique<FractalTetrahedronFactory>();
  objectFactoryMap[ObjectId::Pentagram] = std::make_unique<PentagramFactory>();
}

void InitComponentFactoryMap(ComponentFactories& componentFactories)
{
  componentFactories[ObjectId::Square] = std::make_unique<Components::SquareFactory>();
  componentFactories[ObjectId::Rectangle] = std::make_unique<Components::RectangleFactory>();
  componentFactories[ObjectId::Trapeze] = std::make_unique<Components::TrapezeFactory>();
  componentFactories[ObjectId::Pyramid] = std::make_unique<Components::PyramidFactory>();
  componentFactories[ObjectId::Cone] = std::make_unique<Components::ConeFactory>();
  componentFactories[ObjectId::Cylinder] = std::make_unique<Components::CylinderFactory>();
  componentFactories[ObjectId::TriangulatedCylinder] = std::make_unique<Components::TriangulatedCylinderFactory>();
  componentFactories[ObjectId::Star] = std::make_unique<Components::StarFactory>();
}

const auto& GetFactory(const std::string& name, const ObjectFactoryMap& objectFactoryMap)
{
  const auto it = ObjectIdMap.find(name);
  if (it == ObjectIdMap.end())
  {
      throw std::out_of_range("3d object id not found");
  }

  const auto creatorIt = objectFactoryMap.find(it->second);
  if (creatorIt == objectFactoryMap.end())
  {
    throw std::out_of_range("3d object factory not found");
  }

  return creatorIt->second;
}

template<typename T>
void AddParams(
  const po::variables_map& options,
  const std::string& name,
  const ParamsId param,
  ParamsMap& paramsMap)
{
  if (!options[name].empty())
  {
    const auto& list = options[name].as<T>();
    paramsMap[param] = list;
  }
};

void PrintParamsHelp()
{
  std::cout << "Possible 3d objects to use:" << std::endl;
  std::for_each(ObjectIdMap.begin(), ObjectIdMap.end(),
    [](std::pair<std::string, ObjectId> item)
      {
        std::cout << item.first;
      });

  std::cout << std::endl;
}

auto ReadGeneratorParams(int argc, char *argv[], po::options_description& desc)
{
  po::variables_map vm;

  po::positional_options_description p;
  p.add("a", -1);

  po::store(po::command_line_parser(argc, argv)
    .style(po::command_line_style::unix_style ^ po::command_line_style::allow_short)
    .options(desc)
    .positional(p)
    .run(), vm);

  po::notify(vm);

  return vm;
}

void SetLogging(bool verbose)
{
  boost::log::trivial::severity_level logLevel =
    verbose
    ? boost::log::trivial::debug
    : boost::log::trivial::error;

  auto logFilter = boost::log::filter(boost::log::trivial::severity >= logLevel);
  boost::log::core::get()->set_filter(logFilter);
}

int main(int argc, char* argv[])
{
  po::options_description optionsDesc("generator <options>\n");
  optionsDesc.add_options()
    ("help", "produce help message")
    ("v", "debug")
    ("o", po::value<std::string>(), "output file name")
    ("n", po::value<std::string>(), "main object name")
    ("a", po::value<ParamsVector>(), "main object params")
    ("t", po::value<ParamsVector>()->multitoken(), "transform params")
    ("s", po::value<SinusParamsVector>()->multitoken(), "sinus params")
    ("c", po::value<ComponentNamesVector>()->multitoken(), "component name")
    ("p", po::value<ParamsVector>()->multitoken(), "component params")
    ("3", "prefer triangle faces over rectangles")
    ("l", po::value<int>(), "normal vector length")
    ("c0", po::value<ComponentNamesVector>()->multitoken(), "name of component 0")
    ("c1", po::value<ComponentNamesVector>()->multitoken(), "name of component 1")
    ("c2", po::value<ComponentNamesVector>()->multitoken(), "name of component 2")
    ("c3", po::value<ComponentNamesVector>()->multitoken(), "name of component 3")
    ("c4", po::value<ComponentNamesVector>()->multitoken(), "name of component 4")
    ("c5", po::value<ComponentNamesVector>()->multitoken(), "name of component 5")
    ("p0", po::value<ParamsVector>()->multitoken(), "params for component 0")
    ("p1", po::value<ParamsVector>()->multitoken(), "params for component 1")
    ("p2", po::value<ParamsVector>()->multitoken(), "params for component 2")
    ("p3", po::value<ParamsVector>()->multitoken(), "params for component 3")
    ("p4", po::value<ParamsVector>()->multitoken(), "params for component 4")
    ("p5", po::value<ParamsVector>()->multitoken(), "params for component 5")
    ("t0", po::value<StringVector>()->multitoken(), "transform component 0")
    ("t1", po::value<StringVector>()->multitoken(), "transform component 1")
    ("t2", po::value<StringVector>()->multitoken(), "transform component 2")
    ("t3", po::value<StringVector>()->multitoken(), "transform component 3")
    ("t4", po::value<StringVector>()->multitoken(), "transform component 4")
    ("t5", po::value<StringVector>()->multitoken(), "transform component 5")
    ;

  const po::variables_map& options = ReadGeneratorParams(argc, argv, optionsDesc);

  if (options.count("help"))
  {
    std::cout << optionsDesc << std::endl;
    return 1;
  }

  const auto verbose = options.count("v");
  const auto preferTriangles = options.count("3");

  std::string name;
  if (options.count("n"))
  {
    name = options["n"].as<std::string>();
  }
  else
  {
    name = "composite";
  }

  int normalLength = 0;
  if (options.count("l"))
  {
    normalLength = options["l"].as<int>();
  }

  std::string outputName;
  if (options.count("o"))
  {
    outputName = options["o"].as<std::string>();
  }

  ParamsMap paramsMap;
  AddParams<ComponentNamesVector>(options, "c", ParamsId::ComponentsList, paramsMap);
  AddParams<ParamsVector>(options, "p", ParamsId::ComponentsParams, paramsMap);
  AddParams<ParamsVector>(options, "t", ParamsId::Params, paramsMap);
  AddParams<ParamsVector>(options, "a", ParamsId::AdditionalParams, paramsMap);
  AddParams<SinusParamsVector>(options, "s", ParamsId::SinusParams, paramsMap);

  AddParams<ComponentNamesVector>(options, "c0", ParamsId::ComponentsList0, paramsMap);
  AddParams<ComponentNamesVector>(options, "c1", ParamsId::ComponentsList1, paramsMap);
  AddParams<ComponentNamesVector>(options, "c2", ParamsId::ComponentsList2, paramsMap);
  AddParams<ComponentNamesVector>(options, "c3", ParamsId::ComponentsList3, paramsMap);
  AddParams<ComponentNamesVector>(options, "c4", ParamsId::ComponentsList4, paramsMap);
  AddParams<ComponentNamesVector>(options, "c5", ParamsId::ComponentsList5, paramsMap);

  AddParams<ParamsVector>(options, "p0", ParamsId::ComponentsParams0, paramsMap);
  AddParams<ParamsVector>(options, "p1", ParamsId::ComponentsParams1, paramsMap);
  AddParams<ParamsVector>(options, "p2", ParamsId::ComponentsParams2, paramsMap);
  AddParams<ParamsVector>(options, "p3", ParamsId::ComponentsParams3, paramsMap);
  AddParams<ParamsVector>(options, "p4", ParamsId::ComponentsParams4, paramsMap);
  AddParams<ParamsVector>(options, "p5", ParamsId::ComponentsParams5, paramsMap);

  AddParams<StringVector>(options, "t0", ParamsId::TransformCmds0, paramsMap);
  AddParams<StringVector>(options, "t1", ParamsId::TransformCmds1, paramsMap);
  AddParams<StringVector>(options, "t2", ParamsId::TransformCmds2, paramsMap);
  AddParams<StringVector>(options, "t3", ParamsId::TransformCmds3, paramsMap);
  AddParams<StringVector>(options, "t4", ParamsId::TransformCmds4, paramsMap);
  AddParams<StringVector>(options, "t5", ParamsId::TransformCmds5, paramsMap);

  paramsMap[ParamsId::PreferTriangles] = preferTriangles ? true : false;
  paramsMap[ParamsId::NormalLength] = normalLength;

  SetLogging(verbose);

  try {
    BOOST_LOG_TRIVIAL(debug) << "Creating: " << name;

    ObjectFactoryMap objectFactoryMap;
    InitObjectFactoryMap(objectFactoryMap);

    ComponentFactories componentFactoryMap;
    InitComponentFactoryMap(componentFactoryMap);

    const auto& factory = GetFactory(name, objectFactoryMap);

    factory->Init(componentFactoryMap);

    const auto object3d = factory->Create(name, paramsMap);

    FileFormatConverter converter;
    auto buffer = converter.ConvertFromObject(*object3d);

    const std::string fileName = outputName.empty() ? object3d->GetName() : outputName;

    FileSaver file(fileName);
    file.Save(buffer);

    BOOST_LOG_TRIVIAL(debug) << *object3d;

  } catch (const std::out_of_range& ex) {
    BOOST_LOG_TRIVIAL(error) << ex.what();
    return 1;
  } catch (const std::bad_cast& ex) {
    BOOST_LOG_TRIVIAL(error) << ex.what();
    return 1;
  }

  return 0;

}
