#include "ComponentFactoryBase.hpp"
#include "IGenerator.hpp"
#include "Object3D.hpp"

std::unique_ptr<Object3D> ComponentFactoryBase::Create(
  const ParamsVector& params, bool triangulated) const
{
  auto object = FactoryMethod(params);
  Generate(*object, triangulated);
  return object;
}

void ComponentFactoryBase::Generate(Object3D& object, bool triangulated) const
{
  auto& generator = dynamic_cast<IGenerator&>(object);

  if (triangulated)
  {
    generator.SetTraingulated();
  }
  
  generator.Generate();
}
