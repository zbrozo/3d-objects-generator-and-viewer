#include "Composite.hpp"
#include "IGenerator.hpp"

#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>

#include <optional>
#include <iostream>

namespace
{

auto getParam(const std::vector<int>& values, unsigned int index)
{
  if (values.size() > index)
  {
    return std::optional<int>{values[index]};
  }

  return std::optional<int>();
}

void RotateSide(
  int degx, int degy, int degz,
  const Faces& faces,
  const Vertices& vertices,
  Faces& objectFaces,
  Vertices& objectVertices)
{
  const auto rotatedVertices = vertices.Rotate(degx, degy, degz);

  for (const auto& face : faces)
  {
    const auto [resultFace, resultVertices] = Object3D::Merge(objectVertices, face, rotatedVertices);
    objectVertices = resultVertices;
    objectFaces.push_back(resultFace);
  }
}

} // namespace

void Composite::Generate()
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;

  for (const auto& object : *mComponents)
  {
    auto params = object.first.first;
    auto cmds = object.first.second;

    auto& components = *object.second;

    auto param0 = getParam(params, 0);
    auto param1 = getParam(params, 1);
    auto param2 = getParam(params, 2);
    auto param3 = getParam(params, 3);
    auto param4 = getParam(params, 4);
    auto param5 = getParam(params, 5);
    auto param6 = getParam(params, 6);
    auto param7 = getParam(params, 7);
    auto param8 = getParam(params, 8);

    int beforeRotationTransitionX = param0.has_value() ? param0.value() : 0;
    int beforeRotationTransitionY = param1.has_value() ? param1.value() : 0;
    int beforeRotationTransitionZ = param2.has_value() ? param2.value() : 0;

    int degX = param3.has_value() ? param3.value() : 0;
    int degY = param4.has_value() ? param4.value() : 0;
    int degZ = param5.has_value() ? param5.value() : 0;

    int afterRotationTransitionX = param6.has_value() ? param6.value() : 0;
    int afterRotationTransitionY = param7.has_value() ? param7.value() : 0;
    int afterRotationTransitionZ = param8.has_value() ? param8.value() : 0;

    Faces objectFaces;
    Vertices objectVertices;

    //boost::char_separator<char> sep(",;:");
    //boost::tokenizer<boost::char_separator<char>> tokens(script, sep);

    for (auto cmd : cmds)
    {
      std::cout << cmd << std::endl;
    }

    for (const auto& component : components)
    {
      Vertices vertices{component->GetVertices()};
      vertices += Vertex(beforeRotationTransitionX, beforeRotationTransitionY, beforeRotationTransitionZ);

      RotateSide(degX, degY, degZ, component->GetFaces(), vertices, objectFaces, objectVertices);

      objectVertices += Vertex(afterRotationTransitionX, afterRotationTransitionY, afterRotationTransitionZ);
    }

    Merge(objectVertices, objectFaces);
  }
}
