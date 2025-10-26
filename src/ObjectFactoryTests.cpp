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

  BOOST_CHECK_EQUAL("cube", object->GetName());
  BOOST_CHECK_EQUAL(8, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(6, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(thorus_factory_test)
{
  ParamsMap paramsMap;
  ThorusFactory factory;
  ComponentFactories componentFactories;

  paramsMap[ParamsId::AdditionalParams] = ParamsVector{6, 8};

  factory.Init(componentFactories);
  auto object = factory.Create("thorus", paramsMap);

  BOOST_CHECK_EQUAL("thorus_6_8", object->GetName());
  BOOST_CHECK_EQUAL(48, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(48, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(composite_factory_test)
{
  ParamsMap paramsMap;
  CompositeFactory factory;
  ComponentFactories componentFactories;
  componentFactories[ObjectId::Cone] = std::make_unique<Components::ConeFactory>();

  paramsMap[ParamsId::ComponentsList0] = ComponentNamesVector{"Cone"};
  paramsMap[ParamsId::ComponentsList1] = ComponentNamesVector{"Cone"};
  paramsMap[ParamsId::ComponentsParams0] = ParamsVector{3,50,50};
  paramsMap[ParamsId::ComponentsParams1] = ParamsVector{3,50,-50};

  factory.Init(componentFactories);
  auto object = factory.Create("composite", paramsMap);

  BOOST_CHECK_EQUAL("composite_Cone_Cone_3_50_50_3_50_-50", object->GetName());
  BOOST_CHECK_EQUAL(5, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(6, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(tetrahedron_factory_test)
{
  ParamsMap paramsMap;
  TetrahedronFactory factory;
  ComponentFactories componentFactories;

  paramsMap[ParamsId::AdditionalParams] = ParamsVector{50, 68};

  factory.Init(componentFactories);
  auto object = factory.Create("tetrahedron", paramsMap);

  BOOST_CHECK_EQUAL("tetrahedron_50_68", object->GetName());
  BOOST_CHECK_EQUAL(4, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(4, object->GetFacesCount());
  BOOST_CHECK_EQUAL(68, object->GetVertices()[3].getZ());
}

BOOST_AUTO_TEST_CASE(regulartetrahedron_factory_test)
{
  ParamsMap paramsMap;
  RegularTetrahedronFactory factory;
  ComponentFactories componentFactories;

  factory.Init(componentFactories);
  auto object = factory.Create("regulartetrahedron", paramsMap);

  BOOST_CHECK_EQUAL("regulartetrahedron", object->GetName());
  BOOST_CHECK_EQUAL(4, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(4, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(fractaltetrahedron_factory_test)
{
  ParamsMap paramsMap;
  FractalTetrahedronFactory factory;
  ComponentFactories componentFactories;

  factory.Init(componentFactories);
  auto object = factory.Create("fractaltetrahedron", paramsMap);

  BOOST_CHECK_EQUAL("fractaltetrahedron", object->GetName());
  BOOST_CHECK_EQUAL(10, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(16, object->GetFacesCount());
}

BOOST_AUTO_TEST_CASE(pentagram_factory_test)
{
  ParamsMap paramsMap;
  PentagramFactory factory;
  ComponentFactories componentFactories;

  paramsMap[ParamsId::AdditionalParams] = ParamsVector{20};

  factory.Init(componentFactories);
  auto object = factory.Create("pentagram", paramsMap);

  BOOST_CHECK_EQUAL("pentagram_20", object->GetName());
  BOOST_CHECK_EQUAL(20, object->GetVerticesCount());
  BOOST_CHECK_EQUAL(25, object->GetFacesCount());
}

BOOST_AUTO_TEST_SUITE_END()
