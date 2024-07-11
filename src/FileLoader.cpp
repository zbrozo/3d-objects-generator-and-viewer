#include "FileLoader.hpp"

#include <boost/log/trivial.hpp>

#include <fstream>

BinaryBuffer<uint16_t> FileLoader::Load()
{
  BinaryBuffer<uint16_t> buffer;

  if (!mFile)
  {
    BOOST_LOG_TRIVIAL(error) << "File is not opened (" << mName << ")";
    return buffer;
  }

  while(true)
  {
    uint16_t value = 0;

    mFile.read(reinterpret_cast<char*>(&value), 2);

    if (mFile.eof())
    {
      break;
    }
    
    buffer.Push(value);
  }
  
  return buffer;
}

