#ifndef _OBJECT_BUILDER_HPP_
#define _OBJECT_BUILDER_HPP_

#include "Object3D.hpp"

class ObjectBuilder : public Object3D
{
public:

  ObjectBuilder() : Object3D("")
  {
  }

  ~ObjectBuilder() = default;

  ObjectBuilder(const ObjectBuilder&) = delete;
  ObjectBuilder(ObjectBuilder&&) = delete;
  ObjectBuilder& operator=(const ObjectBuilder&) = delete;
  ObjectBuilder& operator=(ObjectBuilder&&) = delete;

  explicit ObjectBuilder(const Object3D& object) :
    Object3D(object)
  {
  }

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
};

#endif
