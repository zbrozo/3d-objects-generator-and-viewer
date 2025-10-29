#include "CubeExt.hpp"
#include "IGenerator.hpp"
#include "Tools.hpp"

#include <boost/log/trivial.hpp>

namespace
{

auto getParam(std::vector<int> values, unsigned int index)
{
  if (values.size() > index)
  {
    return values[index];
  }

  return 0;
}

} // namespace

void CubeExt::Generate()
{
  for (auto& pair : *mObjects)
  {
    const auto& params = pair.first.first;

    auto translationX = getParam(params, 0);
    auto translationY = getParam(params, 1);
    auto translationZ = getParam(params, 2);

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
