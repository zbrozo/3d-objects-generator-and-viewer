#include "Vertex3D.hpp"
#include "Rotation.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Vertex_Suite)

BOOST_AUTO_TEST_CASE(vertex_add_operation_test)
{
  Vertex3D<int> vertex1 {0, 1, 2};
  Vertex3D<int> vertex2 {1, 1, 1};

  vertex1 += vertex2;

  BOOST_CHECK_EQUAL(vertex1, Vertex3D<int>(1,2,3));
  
  vertex1 = vertex1 + vertex2;

  BOOST_CHECK_EQUAL(vertex1, Vertex3D<int>(2,3,4));
}

BOOST_AUTO_TEST_CASE(vertex_rotationx_test)
{
  Vertex3D<int> vertex {0, 50, 0};
  Rotation3D<Vertex> rotation;
  
  const int scale = 10; 
  
  const auto vertex1 = rotation.rotateX(vertex * scale, 90) / scale;
  const auto vertex2 = rotation.rotateX(vertex * scale, 180) / scale;
  const auto vertex3 = rotation.rotateX(vertex * scale, 270) / scale;
  const auto vertex4 = rotation.rotateX(vertex * scale, 360) / scale;
  
  BOOST_CHECK_EQUAL(0, vertex1.getY());
  BOOST_CHECK_EQUAL(50, vertex1.getZ());
  BOOST_CHECK_EQUAL(-50, vertex2.getY());
  BOOST_CHECK_EQUAL(0, vertex2.getZ());
  BOOST_CHECK_EQUAL(0, vertex3.getY());
  BOOST_CHECK_EQUAL(-50, vertex3.getZ());
  BOOST_CHECK_EQUAL(50, vertex4.getY());
  BOOST_CHECK_EQUAL(0, vertex4.getZ());
}

BOOST_AUTO_TEST_CASE(vertex_rotationy_test)
{
  Vertex3D<int> vertex {50, 0, 0};
  Rotation3D<Vertex> rotation;
  
  const int scale = 10; 
  
  const auto vertex1 = rotation.rotateY(vertex * scale, 90) / scale;
  const auto vertex2 = rotation.rotateY(vertex * scale, 180) / scale;
  const auto vertex3 = rotation.rotateY(vertex * scale, 270) / scale;
  const auto vertex4 = rotation.rotateY(vertex * scale, 360) / scale;
  
  BOOST_CHECK_EQUAL(0, vertex1.getX());
  BOOST_CHECK_EQUAL(-50, vertex1.getZ());
  BOOST_CHECK_EQUAL(-50, vertex2.getX());
  BOOST_CHECK_EQUAL(0, vertex2.getZ());
  BOOST_CHECK_EQUAL(0, vertex3.getX());
  BOOST_CHECK_EQUAL(50, vertex3.getZ());
  BOOST_CHECK_EQUAL(50, vertex4.getX());
  BOOST_CHECK_EQUAL(0, vertex4.getZ());
}

BOOST_AUTO_TEST_CASE(vertex_rotationz_test)
{
  Vertex3D<int> vertex {0, 50, 0};
  Rotation3D<Vertex> rotation;
  
  const int scale = 10; 
  
  const auto vertex1 = rotation.rotateZ(vertex * scale, 90) / scale;
  const auto vertex2 = rotation.rotateZ(vertex * scale, 180) / scale;
  const auto vertex3 = rotation.rotateZ(vertex * scale, 270) / scale;
  const auto vertex4 = rotation.rotateZ(vertex * scale, 360) / scale;
  
  BOOST_CHECK_EQUAL(-50, vertex1.getX());
  BOOST_CHECK_EQUAL(0, vertex1.getY());
  BOOST_CHECK_EQUAL(0, vertex2.getX());
  BOOST_CHECK_EQUAL(-50, vertex2.getY());
  BOOST_CHECK_EQUAL(50, vertex3.getX());
  BOOST_CHECK_EQUAL(0, vertex3.getY());
  BOOST_CHECK_EQUAL(0, vertex4.getX());
  BOOST_CHECK_EQUAL(50, vertex4.getY());
}

BOOST_AUTO_TEST_SUITE_END()
