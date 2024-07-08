#include "Types.hpp"
#include "Vertex3D.hpp"
#include <type_traits>

template <typename Derived, typename Base1, typename Base2>
struct IsDerivedFromEither {
  static constexpr bool value =
    std::is_base_of_v<Base1, Derived>
    || std::is_base_of_v<Base2, Derived>;
};

template<class T>
class Rotation3D
{
  static_assert(IsDerivedFromEither<T, Vertex, Vector>::value,
    "Rotation can use only Vertex or Vector based types"
    );
  
public:
  
  T rotateX(T coord, int d);
  T rotateY(T coord, int d);
  T rotateZ(T coors, int d);
};

using VertexRotation = Rotation3D<Vertex>;
using VectorRotation = Rotation3D<Vector>;
