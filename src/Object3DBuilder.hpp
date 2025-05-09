#pragma once
#include "Object3D.hpp"

class Object3DBuilder : public Object3D
{
public:

  Object3DBuilder() : Object3D("")
  {
  }

  ~Object3DBuilder() = default;
  
  Object3DBuilder(const Object3DBuilder&) = delete;
  Object3DBuilder(Object3DBuilder&&) = delete;
  Object3DBuilder& operator=(const Object3DBuilder&) = delete;
  Object3DBuilder& operator=(Object3DBuilder&&) = delete;
    
  void SetVertices(const Vertices& vertices)
  {
    mVertices = vertices;
  }

  void SetFaces(const Faces& faces)
  {
    mFaces = faces;
  }

  void SetNormalVectorsInVertices(const Vectors& vectors)
  {
    mNormalVectorsInVertices = vectors;
  }

  void SetNormalVectorsInFaces(const Vectors& vectors)
  {
    mNormalVectorsInFaces = vectors;
  }

  //Object3D GetObject3D() const
  //{
  // return *this;
  //}
  
};
