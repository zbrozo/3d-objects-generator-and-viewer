#include "Components.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ComponentGeneration_Suite)

BOOST_AUTO_TEST_CASE(square_generation_test)
{
  Components::Square object(50);
  object.Generate();
  
  BOOST_CHECK_EQUAL("Square", object.GetName());
  BOOST_CHECK_EQUAL(4, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(1, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(rectangle_generation_test)
{
  Components::Rectangle object(50,30);
  object.Generate();

  BOOST_CHECK_EQUAL("Rectangle", object.GetName());
  BOOST_CHECK_EQUAL(4, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(1, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(pyramid_generation_test)
{
  Components::Pyramid object(50,30);
  object.Generate();
  
  BOOST_CHECK_EQUAL("Pyramid", object.GetName());
  BOOST_CHECK_EQUAL(5, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(4, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(cone_generation_test)
{
  Components::Cone object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL("Cone", object.GetName());
  BOOST_CHECK_EQUAL(11, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(10, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(cylinder_generation_test)
{
  Components::Cylinder object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL("Cylinder", object.GetName());
  BOOST_CHECK_EQUAL(20, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(10, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(triangulatedcylinder_generation_test)
{
  Components::TriangulatedCylinder object(10,50,50);
  object.Generate();
  
  BOOST_CHECK_EQUAL("TriangulatedCylinder", object.GetName());
  BOOST_CHECK_EQUAL(20, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(20, object.GetFacesCount());
}

BOOST_AUTO_TEST_CASE(star_generation_test)
{
  Components::Star object(5,100);
  object.Generate();
  
  BOOST_CHECK_EQUAL("Star", object.GetName());
  BOOST_CHECK_EQUAL(10, object.GetVerticesCount());
  BOOST_CHECK_EQUAL(5, object.GetFacesCount());
}

BOOST_AUTO_TEST_SUITE_END()
