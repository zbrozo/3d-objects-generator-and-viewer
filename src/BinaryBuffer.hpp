#pragma once

#include <stdexcept>
#include <ostream>
#include <vector>
#include <cstdint>

template <typename T>
class BinaryBuffer
{
  std::vector<T> buffer;
  
public:

  BinaryBuffer() = default;

  BinaryBuffer(const std::vector<T>& data)
  {
    buffer = data;
  }
  
  void Clear()
  {
    buffer.clear();
  }
  
  void Push(T value)
  {
    buffer.push_back(value);
  }

  T ReadWord(size_t& index) const
  {
    const auto value = ReadWord(std::move(index));
    
    index += 1;

    return value;
  }

  T ReadWord(size_t&& index) const
  {
    if (index >= buffer.size())
    {
      throw std::out_of_range("Reading binary buffer error");
    }

    return buffer[index];
  }

  const T* GetData() const
  {
    return buffer.data();
  }
  
  auto GetSize() const
  {
    return buffer.size();
  }

  auto GetSizeInBytes() const
  {
    return buffer.size() * sizeof(T);
  }
  
  
  /*
  friend std::ostream& operator<<(std::ostream& os, const BinaryBuffer<type>&
buffer)
  {
    const auto size = buffer.size();

    os << "Binary buffer: ";

    for (size_t i = 0; i < size; ++i)
    {
      int index = i;
      os << std::hex << "0x" << buffer.ReadWord(index) << " ";
    }

    os << std::endl;

    return os;
  }
  */
};
