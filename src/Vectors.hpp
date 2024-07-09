#pragma once

#include <vector>
#include <ostream>
#include <iterator>

#include "Types.hpp"

class Vectors : private std::vector<Vector>
{
  using vector = std::vector<Vector>;
  
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
  
  Vectors()
  {
  }
  
  Vectors(std::initializer_list<Vertex> vectors)
  {
    insert(end(), vectors.begin(), vectors.end());
  }
  
  ~Vectors() = default;
  
  Vectors(Vectors const &) = default;
  Vectors(Vectors&&) = default;
  Vectors& operator=(const Vectors&) = default;
  Vectors& operator=(Vectors &&) = default;
  
  friend std::ostream& operator<<(std::ostream& os, const Vectors& vertices);
};

