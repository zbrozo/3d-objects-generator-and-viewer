#include "IGenerator.hpp"
#include "Face.hpp"
#include "Object3D.hpp"
#include "Cube.hpp"
#include "CubeExt.hpp"
#include "Tetrahedron.hpp"
#include "Thorus.hpp"
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
  {"fractaltetrahedron", ObjectId::FractalTetrahedron}
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
}

void InitComponentFactoryMap(ComponentFactories& componentFactories)
{
  componentFactories[ObjectId::Square] = std::make_unique<Components::SquareFactory>();
  componentFactories[ObjectId::Rectangle] = std::make_unique<Components::RectangleFactory>();
  componentFactories[ObjectId::SquareHolePart1] = std::make_unique<Components::SquareWithHolePart1Factory>();
  componentFactories[ObjectId::SquareHolePart2] = std::make_unique<Components::SquareWithHolePart2Factory>();
  componentFactories[ObjectId::Pyramid] = std::make_unique<Components::PyramidFactory>();
  componentFactories[ObjectId::Cone] = std::make_unique<Components::ConeFactory>();
  componentFactories[ObjectId::Cylinder] = std::make_unique<Components::CylinderFactory>();
  componentFactories[ObjectId::CylinderWithTriangularFaces] = std::make_unique<Components::CylinderWithTriangularFacesFactory>();
  componentFactories[ObjectId::CSign] = std::make_unique<Components::CSignFactory>();
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
  boost::log::trivial::severity_level logLevel = (verbose ?
    boost::log::trivial::debug : boost::log::trivial::error);

  auto logFilter = boost::log::filter(boost::log::trivial::severity >= logLevel);
  boost::log::core::get()->set_filter(logFilter);
}

int main(int argc, char* argv[])
{
  po::options_description optionsDesc("generator <type> [params]\n");
  optionsDesc.add_options()
    ("help", "produce help message")
    ("v", "debug")
    ("o", po::value<std::string>(), "output file name")
    ("t", po::value<std::string>(), "main object type")
    ("f", po::value<ParamsVector>()->multitoken(), "translation and rotation params")
    ("s", po::value<SinusParamsVector>()->multitoken(), "sinus params")
    ("c", po::value<ComponentNamesVector>()->multitoken(), "component name")
    ("p", po::value<ParamsVector>()->multitoken(), "component params")
    ("a", po::value<ParamsVector>(), "main object params")
    ("c0", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c1", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c2", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c3", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c4", po::value<ComponentNamesVector>()->multitoken(), "")
    ("c5", po::value<ComponentNamesVector>()->multitoken(), "")
    ("p0", po::value<ParamsVector>()->multitoken(), "")
    ("p1", po::value<ParamsVector>()->multitoken(), "")
    ("p2", po::value<ParamsVector>()->multitoken(), "")
    ("p3", po::value<ParamsVector>()->multitoken(), "")
    ("p4", po::value<ParamsVector>()->multitoken(), "")
    ("p5", po::value<ParamsVector>()->multitoken(), "")
    ("f0", po::value<ParamsVector>()->multitoken(), "")
    ("f1", po::value<ParamsVector>()->multitoken(), "")
    ("f2", po::value<ParamsVector>()->multitoken(), "")
    ("f3", po::value<ParamsVector>()->multitoken(), "")
    ("f4", po::value<ParamsVector>()->multitoken(), "")
    ("f5", po::value<ParamsVector>()->multitoken(), "")
    ("3", "prefer triangle faces over rectangles")
    ("n", po::value<int>(), "normal vector length")
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
  if (options.count("t"))
  {
    name = options["t"].as<std::string>();
  }
  else
  {
    std::cout << optionsDesc << std::endl;
    return 1;
  }

  int normalLength = 0;
  if (options.count("n"))
  {
    normalLength = options["n"].as<int>();
  }
  
  std::string outputName;
  if (options.count("o"))
  {
    outputName = options["o"].as<std::string>();
  }

  ParamsMap paramsMap;
  AddParams<ComponentNamesVector>(options, "c", ParamsId::ComponentsList, paramsMap);
  AddParams<ParamsVector>(options, "p", ParamsId::ComponentsParams, paramsMap);
  AddParams<ParamsVector>(options, "f", ParamsId::Params, paramsMap);
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

  AddParams<ParamsVector>(options, "f0", ParamsId::Params0, paramsMap);
  AddParams<ParamsVector>(options, "f1", ParamsId::Params1, paramsMap);
  AddParams<ParamsVector>(options, "f2", ParamsId::Params2, paramsMap);
  AddParams<ParamsVector>(options, "f3", ParamsId::Params3, paramsMap);
  AddParams<ParamsVector>(options, "f4", ParamsId::Params4, paramsMap);
  AddParams<ParamsVector>(options, "f5", ParamsId::Params5, paramsMap);

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
