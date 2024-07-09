#include "Vector3D.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

BOOST_AUTO_TEST_SUITE(Vector_Suite)

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

BOOST_AUTO_TEST_SUITE_END()
