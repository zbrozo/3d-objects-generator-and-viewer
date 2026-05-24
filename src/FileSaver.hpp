#ifndef _FILESAVER_HPP_
#define _FILESAVER_HPP_

#include "BinaryBuffer.hpp"
#include <fstream>

class FileSaver
{
  std::string mName;
  std::ofstream mFile;
  
public:

  explicit FileSaver(const std::string& name)
    : mName(name), mFile(name, std::ios::out | std::ios::binary)
  {
  }
  
  void Save(const BinaryBuffer<uint16_t>& buffer);
  
  void Save(const char* buffer, size_t size);
};

#endif
