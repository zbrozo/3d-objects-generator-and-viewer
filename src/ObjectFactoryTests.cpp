#include "Components.hpp"
#include "ObjectFactories.hpp"
#include "ComponentFactories.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ObjectFactory_Suite)

BOOST_AUTO_TEST_CASE(cube_factory_test)
{
  ParamsMap paramsMap;
  CubeFactory factory;

  const auto object = factory.Create("cube", paramsMap);
  
  BOOST_CHECK_EQUAL("cube", object->mName);
  BOOST_CHECK_EQUAL(8, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(6, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(cube_ext_factory_test1)
{
  ParamsMap paramsMap;
  CubeExtFactory factory;
  ComponentFactories componentFactories;
  componentFactories[ObjectId::SquareHolePart1] = std::make_unique<Components::SquareWithHolePart1Factory>();
  componentFactories[ObjectId::SquareHolePart2] = std::make_unique<Components::SquareWithHolePart2Factory>();
  
  paramsMap[ParamsId::ComponentsList] = ComponentNamesVector{"SquareHolePart1", "SquareHolePart2"};
  paramsMap[ParamsId::Params] = ParamsVector{0, 0, 50}; // set translaction x, y, z

  factory.Init(componentFactories);
  const auto object = factory.Create("cube-ext", paramsMap);
  
  BOOST_CHECK_EQUAL("cube-ext_SquareHolePart1_SquareHolePart2_0_0_50", object->mName);
  BOOST_CHECK_EQUAL(40, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(48, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(cube_ext_factory_test2)
{
  ParamsMap paramsMap;
  CubeExtFactory factory;
  ComponentFactories componentFactories;
  componentFactories[ObjectId::SquareHolePart1] = std::make_unique<Components::SquareWithHolePart1Factory>();
  componentFactories[ObjectId::SquareHolePart2] = std::make_unique<Components::SquareWithHolePart2Factory>();
 
  paramsMap[ParamsId::ComponentsList] = ComponentNamesVector{"SquareHolePart1", "SquareHolePart2"};
  paramsMap[ParamsId::ComponentsParams] = ParamsVector{50, 20, 20};
  paramsMap[ParamsId::Params] = ParamsVector{0, 0, 50}; // set translation x, y, z

  factory.Init(componentFactories);
  const auto object = factory.Create("cube-ext", paramsMap);
  
  BOOST_CHECK_EQUAL("cube-ext_SquareHolePart1_SquareHolePart2_50_20_20_0_0_50", object->mName);
  BOOST_CHECK_EQUAL(40, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(48, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(thorus_factory_test)
{
  ParamsMap paramsMap;
  ThorusFactory factory;
  ComponentFactories componentFactories;

  paramsMap[ParamsId::AdditionalParams] = ParamsVector{6, 8};

  factory.Init(componentFactories);
  auto object = factory.Create("thorus", paramsMap);

  BOOST_CHECK_EQUAL("thorus_6_8", object->mName);
  BOOST_CHECK_EQUAL(48, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(48, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(composite_factory_test)
{
  ParamsMap paramsMap;
  CompositeFactory factory;
  ComponentFactories componentFactories;
  componentFactories[ObjectId::Taper] = std::make_unique<Components::TaperFactory>();
 
  paramsMap[ParamsId::ComponentsList0] = ComponentNamesVector{"Taper"};
  paramsMap[ParamsId::ComponentsList1] = ComponentNamesVector{"Taper"};
  paramsMap[ParamsId::ComponentsParams0] = ParamsVector{3,50,50};
  paramsMap[ParamsId::ComponentsParams1] = ParamsVector{3,50,-50};

  factory.Init(componentFactories);
  auto object = factory.Create("composite", paramsMap);

  BOOST_CHECK_EQUAL("composite_Taper_Taper_3_50_50_3_50_-50", object->mName);
  BOOST_CHECK_EQUAL(5, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(6, object->GetFacesCount());
}

BOOST_AUTO_TEST_SUITE_END()
