#include "Components.hpp"
#include "ObjectFactoryBase.hpp"
#include "Vertex3D.hpp"
#include <memory>
#define BOOST_TEST_MODULE tests
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "IGenerator.hpp"
#include "ObjectFactories.hpp"
#include "ComponentFactories.hpp"
#include "Object3D.hpp"
#include "Params.hpp"

BOOST_AUTO_TEST_SUITE(Basic_Suite)

BOOST_AUTO_TEST_CASE(vertex_add_operation_test)
{
  Vertex3D<int> vertex1 {0, 1, 2};
  Vertex3D<int> vertex2 {1, 1, 1};

  vertex1 += vertex2;

  BOOST_CHECK_EQUAL(vertex1, Vertex3D<int>(1,2,3));
  
  vertex1 = vertex1 + vertex2;

  BOOST_CHECK_EQUAL(vertex1, Vertex3D<int>(2,3,4));
}

BOOST_DATA_TEST_CASE(vector_crossproduct_test,
  boost::unit_test::data::make({
      Vector3D<int>({10, 5, 10}),
      Vector3D<int>({200, 0, 0}),
      Vector3D<int>({0, 0, 0})})
  ^ boost::unit_test::data::make({
      Vector3D<int>({5, 10, 5}),
      Vector3D<int>({0, 200, 0}),
      Vector3D<int>({0, 0, 0})})
  ^ boost::unit_test::data::make({
      Vector3D<int>({-75, 0, 75}),
      Vector3D<int>({0, 0, 40000}),
      Vector3D<int>({0, 0, 0})}),
  firstVector, secondVector, resultVector)    
{
  const auto result = firstVector.calculateCrossProduct(secondVector);
  BOOST_CHECK_EQUAL(result, resultVector);
}

BOOST_AUTO_TEST_CASE(vector_normalize_test)
{
  Vector3D<int> vector {{0,0,0}, {10, 10, 10}};
  const auto result = vector.normalize();
  BOOST_CHECK_EQUAL(result.length(), 64);
  BOOST_CHECK_EQUAL(result, Vector3D<int>(Vertex3D<int>(37, 37, 37)));
}

BOOST_AUTO_TEST_CASE(vector_compare_test)
{
  const Vector3D<int> vector1 {{0,0,0}, {10, 10, 10}};
  const Vector3D<int> vector2 {{0,0,0}, {10, 10, 10}};
  BOOST_CHECK_EQUAL(true, vector1 == vector2);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ComponentGeneration_Suite)

BOOST_AUTO_TEST_CASE(square_generation_test)
{
  Components::Square object(50);
  object.Generate();
  
  BOOST_CHECK_EQUAL(4, object.GetVerticesQuantity());
  BOOST_CHECK_EQUAL(1, object.GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(rectangle_generation_test)
{
  Components::Rectangle object(50,30);
  object.Generate();
  
  BOOST_CHECK_EQUAL(4, object.GetVerticesQuantity());
  BOOST_CHECK_EQUAL(1, object.GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(squarewithhole1_generation_test)
{
  Components::SquareWithHolePart1 object(50,30,20);
  object.Generate();
  
  BOOST_CHECK_EQUAL(8, object.GetVerticesQuantity());
  BOOST_CHECK_EQUAL(4, object.GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(squarewithhole2_generation_test)
{
  Components::SquareWithHolePart2 object(50,30);
  object.Generate();
  
  BOOST_CHECK_EQUAL(8, object.GetVerticesQuantity());
  BOOST_CHECK_EQUAL(4, object.GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(pyramid_generation_test)
{
  Components::Pyramid object(50,30);
  object.Generate();
  
  BOOST_CHECK_EQUAL(5, object.GetVerticesQuantity());
  BOOST_CHECK_EQUAL(4, object.GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(taper_generation_test)
{
  Components::Taper object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL(11, object.GetVerticesQuantity());
  BOOST_CHECK_EQUAL(10, object.GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cylinder_generation_test)
{
  Components::Cylinder object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL(20, object.GetVerticesQuantity());
  BOOST_CHECK_EQUAL(10, object.GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cylindertriangles_generation_test)
{
  Components::CylinderTriangles object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL(20, object.GetVerticesQuantity());
  BOOST_CHECK_EQUAL(20, object.GetFacesQuantity());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ComponentFactories_Suite)

BOOST_AUTO_TEST_CASE(square_factory_test)
{
  ParamsVector params;
  Components::SquareFactory factory;
  const auto object = factory.Create("", params);
  BOOST_CHECK_EQUAL(4, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(1, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(rectangle_factory_test)
{
  ParamsVector params;
  Components::RectangleFactory factory;
  const auto object = factory.Create("", params);
  BOOST_CHECK_EQUAL(4, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(1, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(squarewithhole1_factory_test)
{
  ParamsVector params;
  Components::SquareWithHolePart1Factory factory;
  const auto object = factory.Create("", params);
  BOOST_CHECK_EQUAL(8, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(4, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(squarewithhole2_factory_test)
{
  ParamsVector params;
  Components::SquareWithHolePart2Factory factory;
  const auto object = factory.Create("", params);
  BOOST_CHECK_EQUAL(8, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(4, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(pyramid_factory_test)
{
  ParamsVector params;
  Components::PyramidFactory factory;
  const auto object = factory.Create("", params);
  BOOST_CHECK_EQUAL(5, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(4, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(taper_factory_test)
{
  ParamsVector params;
  Components::TaperFactory factory;
  const auto object = factory.Create("", params);
  BOOST_CHECK_EQUAL(4, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(3, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cylinder_factory_test)
{
  ParamsVector params;
  Components::CylinderFactory factory;
  const auto object = factory.Create("", params);
  BOOST_CHECK_EQUAL(6, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(3, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cylindertriangles_factory_test)
{
  ParamsVector params;
  Components::CylinderTrianglesFactory factory;
  const auto object = factory.Create("", params);
  BOOST_CHECK_EQUAL(6, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(6, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ObjectFactory_Suite)

BOOST_AUTO_TEST_CASE(cube_factory_test)
{
  ParamsMap paramsMap;
  CubeFactory factory;

  const auto object = factory.Create("cube", paramsMap);
  
  BOOST_CHECK_EQUAL("cube", object->mName);
  BOOST_CHECK_EQUAL(8, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(6, object->GetFacesQuantity());
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
  BOOST_CHECK_EQUAL(40, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
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
  BOOST_CHECK_EQUAL(40, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
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
  BOOST_CHECK_EQUAL(48, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
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
  BOOST_CHECK_EQUAL(5, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(6, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_SUITE_END()
