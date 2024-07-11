#pragma once

#include "BinaryBuffer.hpp"
#include <cstdint>

class Object3D;

class ZbrFormatConverter
{
public:
  
  BinaryBuffer<uint16_t> ConvertFromObject(const Object3D& object);
  Object3D ConvertToObject(const BinaryBuffer<uint16_t>& buffer);
};
