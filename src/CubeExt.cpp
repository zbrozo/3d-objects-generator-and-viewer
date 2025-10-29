#include "CubeExt.hpp"
#include "IGenerator.hpp"
#include "Params.hpp"
#include "Tools.hpp"

#include <boost/log/trivial.hpp>

void CubeExt::Generate()
{
  for (auto& pair : *mObjects)
  {
    const auto& params = pair.first.first;

    auto translationX = getObligatorySignedParam(params, 0);
    auto translationY = getObligatorySignedParam(params, 1);
    auto translationZ = getObligatorySignedParam(params, 2);

    BOOST_LOG_TRIVIAL(debug) << "Component vertices translation: " << translationX << " "  << translationY << " " << translationZ << std::endl;

    for (auto& object : *pair.second)
    {
      Vertices vertices = object->GetVertices();

      Tools::Translate(vertices, translationX, translationY, translationZ);

      const auto [resultFaces, resultVertices] = CreateCube(
        object->GetFaces(),
        vertices);

      Tools::Merge(mVertices, mFaces, resultVertices, resultFaces);
    }
  }
}
