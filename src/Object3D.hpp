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
  std::string mName;

protected:

  Vertices mVertices;
  Faces mFaces;
  Vectors mNormalVectorsInFaces;
  Vectors mNormalVectorsInVertices;

public:

  Object3D(const std::string& name) :
    mName(name)
  {
  }

  virtual ~Object3D() = default;

  Object3D(Object3D const &) = default;
  Object3D(Object3D &&) = default;
  Object3D& operator=(Object3D const &) = default;
  Object3D& operator=(Object3D &&) = default;

  friend std::ostream& operator<<(std::ostream& os, const Object3D& object);

  const std::string& GetName() const noexcept(true)
  {
    return mName;
  }

  const Vertices& GetVertices() const noexcept(true)
  {
    return mVertices;
  }

  const Faces& GetFaces() const noexcept(true)
  {
    return mFaces;
  }

  const Vectors& GetNormalVectorsInFaces() const noexcept(true)
  {
    return mNormalVectorsInFaces;
  }

  const Vectors& GetNormalVectorsInVertices() const noexcept(true)
  {
    return mNormalVectorsInVertices;
  }

  int GetFacesCount() const noexcept(true)
  {
    return mFaces.size();
  }

  int GetVerticesCount() const noexcept(true)
  {
    return mVertices.size();
  }

};
