#include "ViewerSortingFaces.hpp"

#include "Vertices.hpp"
#include "Faces.hpp"

#include <algorithm>

namespace {

FaceNumbers PrepareVisibleFaceNumbers(const Vertices& vertices, const Faces &faces)
{
  FaceNumbers faceNumbers;

  unsigned int faceNr = 0;

  for (const auto& face : faces)
  {
    if (!face.IsVisible(vertices))
    {
      ++faceNr;
      continue;
    }

    faceNumbers.push_back(faceNr);

    ++faceNr;
  }

  return faceNumbers;
}

FaceNumbers PrepareInvisibleFaceNumbers(const Vertices& vertices, const Faces &faces)
{
  FaceNumbers faceNumbers;

  unsigned int faceNr = 0;

  for (const auto& face : faces)
  {
    if (face.IsVisible(vertices))
    {
      ++faceNr;
      continue;
    }

    faceNumbers.push_back(faceNr);

    ++faceNr;
  }

  return faceNumbers;
}


} // namespace

FaceNumbers GetVisibleFaceNumbers(const Vertices& vertices, const Faces &faces)
{
  FaceNumbers faceNumbers = PrepareVisibleFaceNumbers(vertices, faces);

  std::sort(faceNumbers.begin(), faceNumbers.end(),
    [&vertices, &faces](int first, int second)
    {
      const Vertex v1 = faces[first].GetCenter(vertices);
      const Vertex v2 = faces[second].GetCenter(vertices);
      return v1.getZ() > v2.getZ();
    });

  return faceNumbers;
}

FaceNumbers GetInvisibleFaceNumbers(const Vertices& vertices, const Faces &faces)
{
  FaceNumbers faceNumbers = PrepareInvisibleFaceNumbers(vertices, faces);

  std::sort(faceNumbers.begin(), faceNumbers.end(),
    [&vertices, &faces](int first, int second)
    {
      const Vertex v1 = faces[first].GetCenter(vertices);
      const Vertex v2 = faces[second].GetCenter(vertices);
      return v1.getZ() < v2.getZ();
    });

  return faceNumbers;
}

