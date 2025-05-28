#include "ViewerSortingFaces.hpp"

#include "Vertices.hpp"
#include "Faces.hpp"

#include <algorithm>

namespace {

FaceNumbers PrepareVisibleFaceNumbers(const Vertices& vertices2d, const Faces &faces)
{
  FaceNumbers faceNumbers;

  unsigned int faceNr = 0;

  for (const auto& face : faces)
  {
    if (!face.IsVisible(vertices2d))
    {
      ++faceNr;
      continue;
    }

    faceNumbers.push_back(faceNr);

    ++faceNr;
  }

  return faceNumbers;
}

FaceNumbers PrepareInvisibleFaceNumbers(const Vertices& vertices2d, const Faces &faces)
{
  FaceNumbers faceNumbers;

  unsigned int faceNr = 0;

  for (const auto& face : faces)
  {
    if (face.IsVisible(vertices2d))
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

FaceNumbers GetVisibleFaceNumbers(const Vertices& vertices2d, const Faces &faces)
{
  FaceNumbers faceNumbers = PrepareVisibleFaceNumbers(vertices2d, faces);

  std::sort(faceNumbers.begin(), faceNumbers.end(),
    [&vertices2d, &faces](int first, int second)
    {
      const Vertex v1 = faces[first].GetCenter(vertices2d);
      const Vertex v2 = faces[second].GetCenter(vertices2d);
      return v1.getZ() > v2.getZ();
    });

  return faceNumbers;
}

FaceNumbers GetInvisibleFaceNumbers(const Vertices& vertices2d, const Faces &faces)
{
  FaceNumbers faceNumbers = PrepareInvisibleFaceNumbers(vertices2d, faces);
  
  std::sort(faceNumbers.begin(), faceNumbers.end(),
    [&vertices2d, &faces](int first, int second)
    {
      const Vertex v1 = faces[first].GetCenter(vertices2d);
      const Vertex v2 = faces[second].GetCenter(vertices2d);
      return v1.getZ() > v2.getZ();
    });

  return faceNumbers;
}

