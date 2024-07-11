#pragma once

#include <type_traits>

template <typename T, typename R>
R swapByteOrder(T value)
{
  const char* bytes = reinterpret_cast<const char*>(&value);

  const unsigned char lower = bytes[0];
  const unsigned char higher = bytes[1];

  if constexpr (std::is_signed_v<T>) {
    return std::make_unsigned_t<T>( (lower << 8) | higher );
  } else {
    return std::make_signed_t<T>( (lower << 8) | higher );
  }
}
