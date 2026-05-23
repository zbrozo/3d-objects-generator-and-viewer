#ifndef _EXCEPTIONS_HPP_
#define _EXCEPTIONS_HPP_

#include "Exception.hpp"

class MissingParameterException : public Exception
{
public:
  explicit MissingParameterException(const char* filename, int line);

};

#endif

