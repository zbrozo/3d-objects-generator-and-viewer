#include "Components.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ComponentGeneration_Suite)

BOOST_AUTO_TEST_CASE(square_generation_test)
{
  Components::Square object(50);
  object.Generate();
  
  BOOST_CHECK_EQUAL(4, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(1, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(rectangle_generation_test)
{
  Components::Rectangle object(50,30);
  object.Generate();
  
  BOOST_CHECK_EQUAL(4, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(1, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(squarewithhole1_generation_test)
{
  Components::SquareWithHolePart1 object(50,30,20);
  object.Generate();
  
  BOOST_CHECK_EQUAL(8, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(4, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(squarewithhole2_generation_test)
{
  Components::SquareWithHolePart2 object(50,30);
  object.Generate();
  
  BOOST_CHECK_EQUAL(8, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(4, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(pyramid_generation_test)
{
  Components::Pyramid object(50,30);
  object.Generate();
  
  BOOST_CHECK_EQUAL(5, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(4, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(cone_generation_test)
{
  Components::Cone object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL(11, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(10, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(cylinder_generation_test)
{
  Components::Cylinder object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL(20, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(10, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(cylinderwithtriangularfaces_generation_test)
{
  Components::CylinderWithTriangularFaces object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL(20, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(20, object.GetFacesCount());
}

BOOST_AUTO_TEST_SUITE_END()
