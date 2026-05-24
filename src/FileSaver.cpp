#include "FileSaver.hpp"

#include <boost/log/trivial.hpp>

#include <fstream>

void FileSaver::Save(const BinaryBuffer<uint16_t>& buffer)
{
  if (!mFile)
  {
    BOOST_LOG_TRIVIAL(error) << "File is not opened (" << mName << ")";
    return;
  }
  
  mFile.write(reinterpret_cast<const char*>(buffer.GetData()), buffer.GetSizeInBytes());
}

void FileSaver::Save(const char* buffer, size_t size)
{
  if (!mFile)
  {
    BOOST_LOG_TRIVIAL(error) << "File is not opened (" << mName << ")";
    return;
  }
  
  mFile.write(reinterpret_cast<const char*>(buffer), size);
}

