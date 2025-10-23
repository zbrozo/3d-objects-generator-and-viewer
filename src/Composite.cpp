#include "Composite.hpp"
#include "IGenerator.hpp"
#include "Tools.hpp"

#include <boost/log/trivial.hpp>

#include <optional>
#include <iostream>

void Composite::Generate()
{
  BOOST_LOG_TRIVIAL(debug) << __FUNCTION__;

  for (const auto& object : *mComponents)
  {
    auto params = object.first.first;
    auto cmds = object.first.second;

    auto& components = *object.second;

    Faces objectFaces;
    Vertices objectVertices;

    for (const auto& component : components)
    {
      Vertices vertices{component->GetVertices()};

      Tools::Transform(vertices, cmds);

      for (const auto& face : component->GetFaces())
      {
        const auto [resultFace, resultVertices] = Tools::Merge(objectVertices, face, vertices);
        objectVertices = resultVertices;
        objectFaces.push_back(resultFace);
      }
    }

    Tools::Merge(mVertices, mFaces, objectVertices, objectFaces);
  }
}
