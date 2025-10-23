#include "Types.hpp"
#include "Vectors.hpp"
#include "Tools.hpp"
#include "ObjectBuilder.hpp"

#include <algorithm>
#include <cmath>
#include <boost/log/trivial.hpp>

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

namespace Tools
{

Object3D CreateNormalVectors(const Object3D& object,
                             int normalLength)
{
  BOOST_LOG_TRIVIAL(trace) << __FUNCTION__;

  ObjectBuilder builder(object);
  FaceNumbersInVertices facesAssignedToVertex = PrepareFacesAssignedToVertices(builder.GetVertices(), builder.GetFaces());
  builder.SetNormalVectorsInFaces(CalculateNormalVectorToFaces(builder.GetVertices(), builder.GetFaces(), normalLength));
  Vectors vectorsInVertices = CalculateVectorsInVertices(facesAssignedToVertex, builder.GetNormalVectorsInFaces());
  builder.SetNormalVectorsInVertices(NormalizeVectorsInVertices(vectorsInVertices, normalLength));
  return builder;
}

void Translate(Vertices& vertices,
               int x, int y, int z)
{
  std::transform(
    vertices.cbegin(),
    vertices.cend(),
    vertices.begin(),
    [&](const Vertex& vertex){
      return Vertex(
        vertex.getX() + x,
        vertex.getY() + y,
        vertex.getZ() + z
        );
    });
}

void Transform(Vertices& vertices,
               StringVector& commands)
{
  for (const std::string& cmd : commands)
  {
    const auto found = cmd.find('=', 0);
    if (found != std::string::npos)
    {
      const std::string name = cmd.substr(0, found);
      const int value = std::stoi(cmd.substr(found + 1));

      if (name == "rx")
      {
        vertices = vertices.Rotate(value, 0, 0);
      }
      else if (name == "ry")
      {
        vertices = vertices.Rotate(0, value, 0);
      }
      else if (name == "rz")
      {
        vertices = vertices.Rotate(0, 0, value);
      }
      else if (name == "tx")
      {
        vertices += Vertex(value, 0, 0);
      }
      else if (name == "ty")
      {
        vertices += Vertex(0, value, 0);
      }
      else if (name == "tz")
      {
        vertices += Vertex(0, 0, value);
      }
    }
  }
}

void Merge(Vertices& destVertices,
           Faces& destFaces,
           const Vertices& srcVertices,
           const Faces& srcFaces)
{
  for (auto face : srcFaces)
  {
    auto r = Merge(
      destVertices,
      face,
      srcVertices);

    destFaces.push_back(r.first);
    destVertices = r.second;
  }
}

std::pair<Face, Vertices> Merge(const Vertices& objectVertices,
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

}
