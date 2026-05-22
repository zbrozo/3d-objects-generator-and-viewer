#include "Exception.hpp"

Exception::Exception(const std::string& description, const char* filename, int line)
{
  mMsg = description + " [file: " + filename + " line: " + std::to_string(line) + "]";
}


const char* Exception::what() const noexcept
{
  return mMsg.c_str();
}
