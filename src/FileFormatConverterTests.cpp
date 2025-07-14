#include "Object3D.hpp"
#include "Object3DBuilder.hpp"
#include "FileFormatConverter.hpp"
#include "BinaryBuffer.hpp"
#include "SwapByteOrder.hpp"

#include <boost/test/unit_test.hpp>
#include <cstdint>

BOOST_AUTO_TEST_SUITE(FileFormatConverter_Suite)

BOOST_AUTO_TEST_CASE(file_format_convert_to_buffer_test)
{
  auto swapBytes = swapByteOrder<uint16_t, int>;
  
  Vertices vertices{{2,3,4}};
  Faces faces{{101,102,103}};
  Vectors normals{{10,11,12}};
  
  Object3DBuilder builder;
  builder.SetVertices(vertices);
  builder.SetNormalVectorsInVertices(normals);
  builder.SetFaces(faces);
  builder.SetNormalVectorsInFaces(normals);
  
  FileFormatConverter converter;
  auto buffer = converter.ConvertFromObject(builder);
  
  BOOST_CHECK_EQUAL(15, buffer.GetSize());
  
  BOOST_CHECK_EQUAL(1, swapBytes(buffer.ReadWord(0)));
  BOOST_CHECK_EQUAL(1, swapBytes(buffer.ReadWord(1)));

  BOOST_CHECK_EQUAL(2, swapBytes(buffer.ReadWord(2)));
  BOOST_CHECK_EQUAL(3, swapBytes(buffer.ReadWord(3)));
  BOOST_CHECK_EQUAL(4, swapBytes(buffer.ReadWord(4)));

  BOOST_CHECK_EQUAL(10, swapBytes(buffer.ReadWord(5)));
  BOOST_CHECK_EQUAL(11, swapBytes(buffer.ReadWord(6)));
  BOOST_CHECK_EQUAL(12, swapBytes(buffer.ReadWord(7)));

  BOOST_CHECK_EQUAL(3, swapBytes(buffer.ReadWord(8)));

  BOOST_CHECK_EQUAL(101, swapBytes(buffer.ReadWord(9)));
  BOOST_CHECK_EQUAL(102, swapBytes(buffer.ReadWord(10)));
  BOOST_CHECK_EQUAL(103, swapBytes(buffer.ReadWord(11)));

  BOOST_CHECK_EQUAL(10, swapBytes(buffer.ReadWord(12)));
  BOOST_CHECK_EQUAL(11, swapBytes(buffer.ReadWord(13)));
  BOOST_CHECK_EQUAL(12, swapBytes(buffer.ReadWord(14)));
}

BOOST_AUTO_TEST_CASE(file_format_convert_from_buffer_test)
{
  std::vector<uint16_t> data = {1, 1, 2, 3, 4, 10, 11, 12, 3, 101, 102, 103, 10, 11, 12};
  
  for (auto& value : data)
  {
    auto swapBytes = swapByteOrder<int, uint16_t>;
    value = swapBytes(value);
  }
  
  BinaryBuffer buffer(data);

  FileFormatConverter converter;
  auto object = converter.ConvertToObject(buffer);

  auto vertices = object.GetVertices();
  auto faces = object.GetFaces();
  auto verticesNormals = object.GetNormalVectorsInVertices();
  auto facesNormals = object.GetNormalVectorsInVertices();
  
  BOOST_CHECK_EQUAL(1, vertices.size());
  BOOST_CHECK_EQUAL(1, faces.size());
  
  BOOST_CHECK_EQUAL(2, vertices[0].getX());
  BOOST_CHECK_EQUAL(3, vertices[0].getY());
  BOOST_CHECK_EQUAL(4, vertices[0].getZ());

  BOOST_CHECK_EQUAL(10, verticesNormals[0].getX());
  BOOST_CHECK_EQUAL(11, verticesNormals[0].getY());
  BOOST_CHECK_EQUAL(12, verticesNormals[0].getZ());

  BOOST_CHECK_EQUAL(3, faces[0].size());
  BOOST_CHECK_EQUAL(101, faces[0][0]);
  BOOST_CHECK_EQUAL(102, faces[0][1]);
  BOOST_CHECK_EQUAL(103, faces[0][2]);
  
  BOOST_CHECK_EQUAL(10, facesNormals[0].getX());
  BOOST_CHECK_EQUAL(11, facesNormals[0].getY());
  BOOST_CHECK_EQUAL(12, facesNormals[0].getZ());
}

BOOST_AUTO_TEST_SUITE_END()
