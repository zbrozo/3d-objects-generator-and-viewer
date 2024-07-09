#pragma once

#include <vector>
#include <ostream>
#include <iterator>

#include "Types.hpp"

class Vertices : private std::vector<Vertex>
{
  using vector = std::vector<Vertex>;
  
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
  using vector::rbegin;
  using vector::rend;
  
  Vertices()
  {
  }
  
  Vertices(std::initializer_list<Vertex> vertices)
  {
    insert(end(), vertices.begin(), vertices.end());
  }
  
  ~Vertices() = default;
  
  Vertices(Vertices const &) = default;
  Vertices(Vertices&&) = default;
  Vertices& operator=(const Vertices&) = default;
  Vertices& operator=(Vertices &&) = default;
  
  Vertices& operator+=(const Vertex& vertex);
  
  friend std::ostream& operator<<(std::ostream& os, const Vertices& vertices);
  
  Vertices Rotate(int degX, int degY, int degZ) const;
};

