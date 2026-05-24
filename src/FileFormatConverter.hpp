#ifndef _FILEFORMATCONVERTER_HPP_
#define _FILEFORMATCONVERTER_HPP_

#include "BinaryBuffer.hpp"

#include <cstdint>
#include <sstream>

class Object3D;

class FileFormatConverter
{
public:

  BinaryBuffer<uint16_t> Convert(const Object3D& object);

  void Convert(std::stringstream& str, const Object3D& object);

  Object3D Convert(const BinaryBuffer<uint16_t>& buffer);
};

#endif

