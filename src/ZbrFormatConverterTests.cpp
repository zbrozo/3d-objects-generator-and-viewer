#include "Object3D.hpp"
#include "Object3DBuilder.hpp"
#include "ZbrFormatConverter.hpp"
#include "BinaryBuffer.hpp"
#include "SwapByteOrder.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ZbrFormatConverter_Suite)

BOOST_AUTO_TEST_CASE(zbr_format_converter_test)
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
  
  ZbrFormatConverter converter;
  auto buffer = converter.ConvertFromObject(builder);
  
  BOOST_CHECK_EQUAL(16, buffer.GetSize());
  
  BOOST_CHECK_EQUAL(1, swapBytes(buffer.ReadWord(0)));
  BOOST_CHECK_EQUAL(1, swapBytes(buffer.ReadWord(1)));

  BOOST_CHECK_EQUAL(2, swapBytes(buffer.ReadWord(2)));
  BOOST_CHECK_EQUAL(3, swapBytes(buffer.ReadWord(3)));
  BOOST_CHECK_EQUAL(4, swapBytes(buffer.ReadWord(4)));

  BOOST_CHECK_EQUAL(10, swapBytes(buffer.ReadWord(5)));
  BOOST_CHECK_EQUAL(11, swapBytes(buffer.ReadWord(6)));
  BOOST_CHECK_EQUAL(12, swapBytes(buffer.ReadWord(7)));

  BOOST_CHECK_EQUAL(0, swapBytes(buffer.ReadWord(8)));
  BOOST_CHECK_EQUAL(3, swapBytes(buffer.ReadWord(9)));
  
  BOOST_CHECK_EQUAL(101*8, swapBytes(buffer.ReadWord(10)));
  BOOST_CHECK_EQUAL(102*8, swapBytes(buffer.ReadWord(11)));
  BOOST_CHECK_EQUAL(103*8, swapBytes(buffer.ReadWord(12)));

  BOOST_CHECK_EQUAL(10, swapBytes(buffer.ReadWord(13)));
  BOOST_CHECK_EQUAL(11, swapBytes(buffer.ReadWord(14)));
  BOOST_CHECK_EQUAL(12, swapBytes(buffer.ReadWord(15)));
  
}

BOOST_AUTO_TEST_SUITE_END()
