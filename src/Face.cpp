#include "Vertices.hpp"
#include "Face.hpp"
#include "Types.hpp"
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <iostream>

#define MIN_FACES 3

Vector Face::CalculateNormalVector(const Vertices& vertices, int normalLength) const
{
  if (this->size() < MIN_FACES)
  {
    throw std::out_of_range("Vertex numbers in a face error");
  }

  const auto n1 = this->at(0);
  const auto n2 = this->at(1);
  const auto n3 = this->at(2);

  auto v1 = Vector(Vertex(
      vertices[n2].getX() - vertices[n1].getX(),
      vertices[n2].getY() - vertices[n1].getY(),
      vertices[n2].getZ() - vertices[n1].getZ()));

  auto v2 = Vector(Vertex(
      vertices[n3].getX() - vertices[n2].getX(),
      vertices[n3].getY() - vertices[n2].getY(),
      vertices[n3].getZ() - vertices[n2].getZ()));

  return v1.calculateCrossProduct(v2).normalize(normalLength);
}

Vertex Face::GetCenter(const Vertices& vertices) const
{
  if (size() < MIN_FACES)
  {
    throw std::out_of_range("Vertex numbers in a face error");
  }

  const size_t s = size();

  int x = 0;
  int y = 0;
  int z = 0;

  for (unsigned int i = 0; i < s; ++i)
  {
    const auto nr = at(i);
    x += vertices[nr].getX();
    y += vertices[nr].getY();
    z += vertices[nr].getZ();
  }

  x /= static_cast<int>(s);
  y /= static_cast<int>(s);
  z /= static_cast<int>(s);

  return Vertex(x, y, z);
}

bool Face::IsVisible(const Vertices& vertices) const
{
  if (this->size() < MIN_FACES)
  {
    throw std::out_of_range("Vertex numbers in a face error");
  }

  auto n0 = this->at(0);
  auto n1 = this->at(1);
  auto n2 = this->at(2);

  const auto v1 = Vector(Vertex(
      vertices[n1].getX() - vertices[n0].getX(),
      vertices[n1].getY() - vertices[n0].getY(),
      0));

  const auto v2 = Vector(Vertex(
      vertices[n2].getX() - vertices[n1].getX(),
      vertices[n2].getY() - vertices[n1].getY(),
      0));

  // cross product w Z (jest większy niż short bo liczony po perspektywie)
  const int32_t result = v1.getX() * v2.getY() - v1.getY() * v2.getX();
  return (result <= 0);
}

std::ostream& operator<<(std::ostream& os, const Face& face)
{
  os << "[";
  const auto size = face.size();
  for (size_t i = 0; i < size; ++i)
  {
    os << std::to_string(face.at(i)) << ((i != size - 1) ? ", " : "");
  }
  os << "]";
  return os;
}
