#pragma once

#include <stdexcept>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>

#include "ComponentFactoryBase.hpp"
#include "Params.hpp"

class Object3D;

using ComponentFactories = std::map<ObjectId, std::unique_ptr<ComponentFactoryBase>>;

class ObjectFactoryBase
{
  const ComponentFactories* mComponentFactories = nullptr;

public:

  ObjectFactoryBase();
  virtual ~ObjectFactoryBase() = default;

  ObjectFactoryBase(const ObjectFactoryBase&) = delete;
  ObjectFactoryBase(ObjectFactoryBase&&) = delete;
  ObjectFactoryBase& operator=(const ObjectFactoryBase&) = delete;
  ObjectFactoryBase& operator=(ObjectFactoryBase&&) = delete;

  void Init(const ComponentFactories& componentFactories)
  {
    mComponentFactories = &componentFactories;
  }

  std::unique_ptr<Object3D> Create(
    const std::string& name,
    const ParamsMap& params) const;

  const ComponentFactories& GetComponentFactories() const
  {
    return *mComponentFactories;
  }

protected:

  virtual std::unique_ptr<Object3D> FactoryMethod(
    const std::string& name,
    const ParamsMap& params) const = 0;

  void Generate(Object3D& object) const;

  std::string CreateFullName(
    const std::string& name,
    const ParamsMap& params) const;
};
