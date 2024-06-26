#include "Vertex3D.hpp"
#define BOOST_TEST_MODULE tests
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "IGenerator.hpp"
#include "ObjectFactories.hpp"
#include "Object3D.hpp"
#include "Params.hpp"

BOOST_AUTO_TEST_SUITE(Basic_Suite)

BOOST_AUTO_TEST_CASE(vertex_add_operations_test)
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

BOOST_AUTO_TEST_SUITE(ObjectFactory_Suite)

BOOST_AUTO_TEST_CASE(cube_factory_test)
{
  CubeFactory factory;
  ParamsMap paramsMap;

  const auto object = factory.Create("cube", paramsMap);
  
  BOOST_CHECK_EQUAL("cube", object->mName);
  BOOST_CHECK_EQUAL(8, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(6, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cube_ext_factory_test1)
{
  CubeExtFactory factory;
  ParamsMap paramsMap;

  paramsMap[ParamsId::ComponentsList] = ComponentNamesVector{"SquareHolePart1", "SquareHolePart2"};
  paramsMap[ParamsId::Params] = ParamsVector{0, 0, 50}; // x, y, z translation

  const auto object = factory.Create("cube-ext", paramsMap);
  
  BOOST_CHECK_EQUAL("cube-ext_SquareHolePart1_SquareHolePart2_0_0_50", object->mName);
  BOOST_CHECK_EQUAL(40, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(cube_ext_factory_test2)
{
  CubeExtFactory factory;
  ParamsMap paramsMap;

  paramsMap[ParamsId::ComponentsList] = ComponentNamesVector{"SquareHolePart1", "SquareHolePart2"};
  paramsMap[ParamsId::ComponentsParams] = ParamsVector{50, 20, 20};
  paramsMap[ParamsId::Params] = ParamsVector{0, 0, 50}; // x, y, z translation
  
  const auto object = factory.Create("cube-ext", paramsMap);
  
  BOOST_CHECK_EQUAL("cube-ext_SquareHolePart1_SquareHolePart2_50_20_20_0_0_50", object->mName);
  BOOST_CHECK_EQUAL(40, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(thorus_factory_test)
{
  ThorusFactory factory;
  ParamsMap paramsMap;

  paramsMap[ParamsId::AdditionalParams] = ParamsVector{6, 8};

  auto object = factory.Create("thorus", paramsMap);

  BOOST_CHECK_EQUAL("thorus_6_8", object->mName);
  BOOST_CHECK_EQUAL(48, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(48, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_CASE(taper_factory_test)
{
  CompositeFactory factory;
  ParamsMap paramsMap;

  paramsMap[ParamsId::ComponentsList0] = ComponentNamesVector{"Taper"};
  paramsMap[ParamsId::ComponentsList1] = ComponentNamesVector{"Taper"};
  paramsMap[ParamsId::ComponentsParams0] = ParamsVector{3,50,50};
  paramsMap[ParamsId::ComponentsParams1] = ParamsVector{3,50,-50};

  auto object = factory.Create("composite", paramsMap);

  BOOST_CHECK_EQUAL("composite_Taper_Taper_3_50_50_3_50_-50", object->mName);
  BOOST_CHECK_EQUAL(5, object->GetVerticesQuantity());
  BOOST_CHECK_EQUAL(6, object->GetFacesQuantity());
}

BOOST_AUTO_TEST_SUITE_END()
