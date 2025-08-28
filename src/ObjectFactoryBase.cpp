#include "ObjectFactoryBase.hpp"
#include "IGenerator.hpp"
#include "Components.hpp"
#include "ComponentFactories.hpp"
#include "Params.hpp"

#include <algorithm>
#include <optional>
#include <type_traits>
#include <variant>
#include <type_traits>

using namespace std::placeholders;

namespace
{

auto findParamsVector = [](const ParamsPair& params, ParamsId id) {
  return params.first == id;
};

template<typename T>
void appendParams (std::string& result, const T& params) {
  if constexpr (!std::is_same_v<T, int>)
  {
    for (auto value : params)
    {
      if constexpr (std::is_same_v<T, ParamsVector>) {
        result += "_" + std::to_string(value);
      }
      else if constexpr (std::is_same_v<T, SinusParamsVector>) {
        result += "_" + std::to_string(value);
      }
      else
        if constexpr (std::is_same_v<T, ComponentNamesVector>) {
          result += "_" + value;
        }
    }
  }
};

} // namespace

ObjectFactoryBase::ObjectFactoryBase()
{
}

std::unique_ptr<Object3D> ObjectFactoryBase::Create(
  const std::string& name,
  const ParamsMap& params) const
{
  auto object = FactoryMethod(name, params);

  int normalLength = 0;
  if (auto it = std::find_if(params.begin(), params.end(),
      std::bind(findParamsVector, _1,  ParamsId::NormalLength)); it != params.end())
  {
    normalLength = std::get<int>(params.at(ParamsId::NormalLength));
  }

  Generate(*object, normalLength);
  return object;
}

std::string ObjectFactoryBase::CreateFullName(const std::string& name, const ParamsMap &params) const
{
  std::string result = name;

  for (const auto& paramsVector : params)
  {
    std::visit(
      [&](auto&& arg){
        appendParams(result, arg);
      },
      paramsVector.second);
  }
  return result;
}

void ObjectFactoryBase::Generate(Object3D& object, int normalLength) const
{
  auto& generator = dynamic_cast<IGenerator&>(object);
  generator.Generate();

  object.CreateNormalVectors(normalLength);
}
