#include "Exceptions.hpp"
#include "Exception.hpp"

MissingParameterException::MissingParameterException(const char* filename, int line) :
  Exception("Missing parameter", filename, line)
{
}
