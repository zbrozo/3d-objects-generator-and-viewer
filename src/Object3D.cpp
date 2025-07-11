#include <iostream>
#include <algorithm>
#include <cmath>

#include <boost/log/trivial.hpp>

#include "Types.hpp"
#include "Vectors.hpp"
#include "Object3D.hpp"

using FaceNumbers = std::vector<unsigned short>;
using FaceNumbersInVertices = std::vector<FaceNumbers>;

namespace
{

auto PrepareFacesAssignedToVertices(
  const Vertices& vertices,
  const Faces& faces)
{
  BOOST_LOG_TRIVIAL(trace) << __FUNCTION__;

  FaceNumbersInVertices result;

  for(unsigned int i = 0; i < vertices.size(); i++)
  {
    FaceNumbers foundFaceNumbers;

    unsigned short faceNr = 0;

    for (auto face : faces)
    {
      if (std::find(face.begin(), face.end(), i) != face.end())
      {
        foundFaceNumbers.push_back(faceNr);
      }

      ++faceNr;
    }

    result.push_back(foundFaceNumbers);
  }

  return result;
}

auto CalculateNormalVectorToFaces(
  const Vertices& vertices,
  const Faces& faces,
  int normalLength
  )
{
  BOOST_LOG_TRIVIAL(trace) << __FUNCTION__;

  Vectors normalVectors;

  for(auto face : faces)
  {
    const auto vector = face.CalculateNormalVector(vertices, normalLength);
    normalVectors.push_back(vector);
  }

  return normalVectors;
}

auto CalculateVectorsInVertices(
  const FaceNumbersInVertices& vertexInFaceDependency,
  const Vectors& normalFaceVectors
  )
{
  BOOST_LOG_TRIVIAL(trace) << __FUNCTION__;

  Vectors vectorsInVertices;

  for(auto faces : vertexInFaceDependency)
  {
    Vertex vertex;

    for(auto faceNr : faces)
    {
      vertex += {normalFaceVectors[faceNr].getX(),
          normalFaceVectors[faceNr].getY(),
          normalFaceVectors[faceNr].getZ()
          };
    }

    const short count = faces.size();

    if (faces.size() != 0)
    {
      vertex = vertex / count;
    }

    vectorsInVertices.push_back(Vector(vertex));
  }

  return vectorsInVertices;
}

auto NormalizeVectorsInVertices(const Vectors& vectorsInVertices, int normalLength)
{
  BOOST_LOG_TRIVIAL(trace) << __FUNCTION__;

  Vectors normalizedVectorsInVertices;

  for (auto vector : vectorsInVertices)
  {
    normalizedVectorsInVertices.push_back(vector.normalize(normalLength));
  }

  return normalizedVectorsInVertices;
}

} // namespace

void Object3D::CreateNormalVectors(int normalLength)
{
  BOOST_LOG_TRIVIAL(trace) << __FUNCTION__;

  FaceNumbersInVertices facesAssignedToVertex = PrepareFacesAssignedToVertices(mVertices, mFaces);

  mNormalVectorsInFaces = CalculateNormalVectorToFaces(mVertices, mFaces, normalLength);

  Vectors vectorsInVertices = CalculateVectorsInVertices(facesAssignedToVertex, mNormalVectorsInFaces);

  mNormalVectorsInVertices = NormalizeVectorsInVertices(vectorsInVertices, normalLength);
}

void Object3D::Translate(int x, int y, int z)
{
  std::transform(
    mVertices.cbegin(),
    mVertices.cend(),
    mVertices.begin(),
    [&](const Vertex& vertex){
      return Vertex(
        vertex.getX() + x,
        vertex.getY() + y,
        vertex.getZ() + z
        );
    });
}

void Object3D::Merge(const Vertices& vertices, const Faces& faces)
{
  for (auto face : faces)
  {
    auto r = Object3D::Merge(
      mVertices,
      face,
      vertices);

    mFaces.push_back(r.first);
    mVertices = r.second;
  }
}

std::pair<Face, Vertices> Object3D::Merge(const Vertices& objectVertices,
  const Face& face,
  const Vertices& vertices)
{
  BOOST_LOG_TRIVIAL(trace) << __FUNCTION__;

  Face resultFace;
  Vertices resultVertices = objectVertices;

  for (size_t i = 0; i < face.size(); ++i)
  {
    auto vertexNr = face[i];
    Vertex vertex = vertices[vertexNr];

    int foundNr = 0;

    auto found = std::find_if(resultVertices.begin(), resultVertices.end(), [&](const Vertex& v){
      const short vertexRange = 0;

      if ((vertex.getX() >= v.getX() - vertexRange && vertex.getX() <= v.getX() + vertexRange)
        && (vertex.getY() >= v.getY() - vertexRange && vertex.getY() <= v.getY() + vertexRange)
        && (vertex.getZ() >= v.getZ() - vertexRange && vertex.getZ() <= v.getZ() + vertexRange))
      {
        return true;
      }

      ++foundNr;
      return false;
    });

    if (found != resultVertices.end())
    {
      resultFace.push_back(foundNr);
    }
    else
    {
      const short nr = resultVertices.size();

      resultFace.push_back(nr);
      resultVertices.push_back(vertex);
    }
  }

  return std::make_pair(resultFace, resultVertices);
}

std::ostream& operator<<(std::ostream& os, const Object3D& object)
{
  os << "Type: " << object.mName << "\n";
  os << "Vertices:" << "\n";
  os << object.mVertices;
  os << "Faces:" << "\n";
  os << object.mFaces;
  os << "Face normals:" << "\n";
  os << object.mNormalVectorsInFaces;
  os << "Vertice normals:" << "\n";
  os << object.mNormalVectorsInVertices;
  return os;
}
