#pragma once
#include <vector>

class Vertices;
class Faces;

using FaceNumbers = std::vector<int>;

FaceNumbers GetVisibleFaceNumbers(const Vertices& vertices2d, const Faces &faces);
FaceNumbers GetInvisibleFaceNumbers(const Vertices& vertices2d, const Faces &faces);

