#ifndef _EXCEPTION_HPP_
#include <exception>
#include <string>

class Exception : public std::exception
{
public:
  Exception(const std::string& description, const char* filename, int line);

  virtual const char* what() const noexcept;

private:
  std::string mMsg;
};

#endif
