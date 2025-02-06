#pragma once

#include "Types.hpp"
#include "Vectors.hpp"

constexpr int maxColorNumber = 64;
constexpr int maxLightValue = 64;

struct SDL_Color;

void PrepareColors(const char* paletteName, SDL_Color* colors);

// void CalculateLight(
//   int light,
//   const Vectors& normalVectorsInFaces,
//   const Vectors& normalVectorsInVertices,
//   std::vector<int>& colorNumbersInFaces,
//   std::vector<int>& colorNumbersInVertices);

void CalculateLight(
  Vector lightVector,
  const Vectors& normalVectorsInFaces,
  const Vectors& normalVectorsInVertices,
  std::vector<int>& colorNumbersInFaces,
  std::vector<int>& colorNumbersInVertices);
