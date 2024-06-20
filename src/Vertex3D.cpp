#include "Vertex3D.hpp"
//#include "Rotation.hpp"

template<class T>
Vertex3D<T> Vertex3D<T>::operator+(const Vertex3D<T>& v) const
{
  return Vertex3D<T>(mX + v.mX, mY + v.mY, mZ + v.mZ);
}

template<class T>
bool Vertex3D<T>::operator==(const Vertex3D<T>& v) const
{
  return (mX == v.mX && mY == v.mY && mZ == v.mZ);
}

template<typename T>
Vertex3D<T> Vertex3D<T>::operator*(T value) const
{
  return Vertex3D<T>(mX * value, mY * value, mZ * value);
}

template<typename T>
Vertex3D<T> Vertex3D<T>::operator/(T value) const
{
  Vertex3D<T> vertex(mX / value, mY / value, mZ / value);

  auto rounding = [value](T pos, T& result)
  {
    if (abs(pos % value) >= (value / 2))
    {
      result += result < 0 ? -1 : 1;
    }
  };

  rounding(mX, vertex.mX);
  rounding(mY, vertex.mY);
  rounding(mZ, vertex.mZ);

  return vertex;
}

template<typename T>
std::string Vertex3D<T>::ToString() const
{
  return std::to_string(mX) + ", " + std::to_string(mY) + ", " + std::to_string(mZ);
}

template class Vertex3D<short>;

/*
Vertex Vertex::Rotate(int degX, int degY, int degZ) const
{
  Rotation rotation;

  Vertex v = *this;
  
  if (degX)
    {
      v = rotation.rotateX(v, degX);
    }
  
  if (degY)
    {
      v = rotation.rotateY(v, degY);
    }
  
  if (degZ)
    {
      v = rotation.rotateZ(v, degZ);
    }

  return v;
}
*/