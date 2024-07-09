#pragma once
#include <vector>
#include "Face.hpp"

class Faces : private std::vector<Face>
{
  using vector = std::vector<Face>;
  
public:
  
  using vector::push_back;
  using vector::operator[];
  using vector::size;
  using vector::at;
  using vector::begin;
  using vector::end;
  using vector::cbegin;
  using vector::cend;
  
  Faces()
  {
  }
  
  Faces(std::initializer_list<Face> init)
  {
    insert(end(), init.begin(), init.end());
  }

  virtual ~Faces() = default;
  
  Faces(Faces const &) = default;
  Faces(Faces&&) = default;
  Faces& operator=(const Faces&) = default;
  Faces& operator=(Faces &&) = default;
  
  friend std::ostream& operator<<(std::ostream& os, const Faces& faces);
  
};
