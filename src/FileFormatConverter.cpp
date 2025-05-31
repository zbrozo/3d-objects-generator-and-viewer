#include "FileFormatConverter.hpp"
#include "BinaryBuffer.hpp"
#include "Object3D.hpp"
#include "Object3DBuilder.hpp"
#include "SwapByteOrder.hpp"

#include <boost/log/trivial.hpp>

#include <algorithm>
#include <type_traits>

BinaryBuffer<uint16_t> FileFormatConverter::ConvertFromObject(const Object3D& object)
{
  auto swapBytes = swapByteOrder<int, uint16_t>;

  BinaryBuffer<uint16_t> buffer;

  BOOST_LOG_TRIVIAL(debug) << "vertices = " + std::to_string(object.GetVerticesCount());
  BOOST_LOG_TRIVIAL(debug) << "faces = " + std::to_string(object.GetFacesCount());

  buffer.Push(swapBytes(object.GetVerticesCount()));
  buffer.Push(swapBytes(object.GetFacesCount()));
  
  for (auto it = object.GetVertices().rbegin(); it != object.GetVertices().rend(); ++it)
  {
    auto value = *it;
    buffer.Push(swapBytes(value.getX()));
    buffer.Push(swapBytes(value.getY()));
    buffer.Push(swapBytes(value.getZ()));
  }

  for (auto it = object.GetNormalVectorsInVertices().rbegin(); it != object.GetNormalVectorsInVertices().rend(); ++it)
  {
    auto value = *it;
    buffer.Push(swapBytes(value.getX()));
    buffer.Push(swapBytes(value.getY()));
    buffer.Push(swapBytes(value.getZ()));
  }

  for(auto face : object.GetFaces())
  {
    buffer.Push(static_cast<uint16_t>(0));
    
    buffer.Push(swapBytes(static_cast<int16_t>(face.size())));
    for (auto number : face)
    {
      buffer.Push(swapBytes(number * 8)); // multiplied by 8 because of later usage in renderer code
    }
  }

  for (auto it = object.GetNormalVectorsInFaces().rbegin(); it != object.GetNormalVectorsInFaces().rend(); ++it)
  {
    auto value = *it;
    buffer.Push(swapBytes(value.getX()));
    buffer.Push(swapBytes(value.getY()));
    buffer.Push(swapBytes(value.getZ()));    
  }
  
  return buffer;
}

Object3D FileFormatConverter::ConvertToObject(const BinaryBuffer<uint16_t>& buffer)
{
  auto swapBytes = swapByteOrder<uint16_t, int>;

  Object3DBuilder builder;

  size_t offset = 0;

  const auto verticesCount = swapBytes(buffer.ReadWord(offset));
  const auto facesCount = swapBytes(buffer.ReadWord(offset));

  BOOST_LOG_TRIVIAL(debug) << "vertices = " + std::to_string(verticesCount);
  BOOST_LOG_TRIVIAL(debug) << "faces = " + std::to_string(facesCount);
  
  Vertices vertices;
  for (int i = 0; i < verticesCount; i++)
  {
    const auto x = swapBytes(buffer.ReadWord(offset));
    const auto y = swapBytes(buffer.ReadWord(offset));
    const auto z = swapBytes(buffer.ReadWord(offset));
    const Vertex vertex(x,y,z);
    vertices.push_back(vertex);
  }

  Vectors normalVectorsInVertices;
  for (int i = 0; i < verticesCount; i++)
  {
    const auto x = swapBytes(buffer.ReadWord(offset));
    const auto y = swapBytes(buffer.ReadWord(offset));
    const auto z = swapBytes(buffer.ReadWord(offset));
    const Vector vector({x,y,z});
    normalVectorsInVertices.push_back(vector);
  }

  Faces faces;
  for (int i = 0; i < facesCount; i++)
  {
    buffer.ReadWord(offset); // not used
    const auto faceSize = swapBytes(buffer.ReadWord(offset));
    
    Face face;
    for (int faceNr = 0; faceNr < faceSize; faceNr++)
    {
      const auto vertexNr = swapBytes(buffer.ReadWord(offset)) / 8;
      face.push_back(vertexNr);
    }
    faces.push_back(face);
  }

  Vectors normalVectorsInFaces;
  for (int i = 0; i < facesCount; i++)
  {
    const auto x = swapBytes(buffer.ReadWord(offset));
    const auto y = swapBytes(buffer.ReadWord(offset));
    const auto z = swapBytes(buffer.ReadWord(offset));
    const Vector vector({x,y,z});
    normalVectorsInFaces.push_back(vector);
  }

  std::reverse(vertices.begin(), vertices.end());
  std::reverse(normalVectorsInVertices.begin(), normalVectorsInVertices.end());
  std::reverse(normalVectorsInFaces.begin(), normalVectorsInFaces.end());

  builder.SetVertices(vertices);
  builder.SetFaces(faces);
  builder.SetNormalVectorsInVertices(normalVectorsInVertices);
  builder.SetNormalVectorsInFaces(normalVectorsInFaces);
  
  return builder;
};
