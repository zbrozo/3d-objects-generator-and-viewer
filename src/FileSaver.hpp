#pragma once
#include "BinaryBuffer.hpp"
#include <fstream>

class FileSaver
{
  std::string mName;
  std::ofstream mFile;
  
public:

  FileSaver(const std::string& name)
    : mName(name), mFile(name, std::ios::out | std::ios::binary)
  {
  }
  
  void Save(const BinaryBuffer<uint16_t>& buffer);

};
