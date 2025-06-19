#pragma once

#include <vector>
#include <string>
#include <ostream>
#include "Types.hpp"

class Vertices;

class Face : private std::vector<unsigned short>
{
  using vector = std::vector<unsigned short>;
  
public:

  using vector::push_back;
  using vector::operator[];
  using vector::size;
  using vector::at;
  using vector::insert;
  using vector::begin;
  using vector::end;
  using vector::cbegin;
  using vector::cend;
  
  Face() = default;
  
  Face(std::initializer_list<unsigned short> init)
  {
    insert(end(), init.begin(), init.end());
  }

  Face(Face const &) = default;
  Face(Face &&) = default;
  Face& operator=(const Face& v) = default;
  Face& operator=(Face &&) = default;

  friend std::ostream& operator<<(std::ostream& os, const Face& face);
  
  Vector CalculateNormalVector(const Vertices& vertices, int normalLength) const;
  Vertex GetCenter(const Vertices& vertices) const;
  bool IsVisible(const Vertices& vertices) const;
};


