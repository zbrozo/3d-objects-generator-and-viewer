#pragma once
#include "BinaryBuffer.hpp"
#include <fstream>

class FileLoader
{
  std::string mName;
  std::ifstream mFile;
  
public:

  FileLoader(const std::string& name)
    : mName(name), mFile(name, std::ios::out | std::ios::binary)
  {
  }
  
  BinaryBuffer<uint16_t> Load();
};
