#pragma once

#include <vector>
#include <string>
#include <utility>

#include "Types.hpp"
#include "Faces.hpp"
#include "Vertices.hpp"
#include "Vectors.hpp"

class Object3D
{
public:

  Object3D(const char* name) :
    mName(name)
  {
  }

  virtual ~Object3D() = default;

  Object3D(Object3D const &) = delete;
  Object3D(Object3D &&) = delete;
  Object3D& operator=(Object3D const &) = delete;
  Object3D& operator=(Object3D &&) = delete;

  friend std::ostream& operator<<(std::ostream& os, const Object3D& object);
  
  std::string mName;
  Vertices mVertices;
  Faces mFaces;
  Vectors mNormalVectorsInFaces;
  Vectors mNormalVectorsInVertices;

  int GetFacesCount() const
  {
    return mFaces.size();
  }

  int GetVerticesCount() const
  {
    return mVertices.size();
  }
  
  void CreateNormalVectors();
  
  static std::pair<Face, Vertices> Merge(const Vertices& objectVertices,
                                         const Face& face,
                                         const Vertices& vertices);
};

