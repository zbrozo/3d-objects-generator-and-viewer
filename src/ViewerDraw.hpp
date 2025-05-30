#pragma once

struct SDL_Color;
struct SDL_Vertex;
struct SDL_Texture;

#include <functional>

#include "Types.hpp"
#include "Vertices.hpp"
#include "Vectors.hpp"
#include "Faces.hpp"
#include "ViewerPerspective.hpp"

using RenderFunction = std::function<void(
                                       int,
                                       const std::vector<SDL_Vertex> &,
                                       SDL_Texture *texture)
                                     >;

using DrawLineFunction = std::function<void(int, int, int, int)>;

using CalculateVertexPerspectiveFunction = std::function<Vertex(const Vertex &)>;
using CalculateVectorPerspectiveFunction = std::function<Vector(const Vector &)>;
using CalculateVerticesPerspectiveFunction = std::function<Vertices(const Vertices &)>;

using CalculateLightFunction = std::function<void(
  const Vectors&,
  const Vectors&,
  std::vector<int>&,
  std::vector<int>&)>;

void DrawFlatShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInFaces,
  RenderFunction render
  );

void DrawGouraudShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInVertices,
  RenderFunction render
  );

void DrawTextureMapping(
  int CenterX, int CenterY,
  const Vertices& vertices2d,
  const Faces& faces,
  SDL_Texture* texture,
  RenderFunction render
  );

void DrawNormalVectorsInFaces(
  int CenterX, int CenterY,
  const Vertices& vertices,
  const Vertices& vertices2d,
  const Faces& faces,
  const Vectors& normalVectorsInFaces,
  CalculateVertexPerspectiveFunction calcPerspectiveFunction,
  DrawLineFunction drawLine
  );

void DrawNormalVectorsInVertices(
  int CenterX, int CenterY,
  const Vertices& vertices,
  const Vertices& vertices2d,
  const Faces& faces,
  const Vectors& normalVectorsInVertices,
  CalculateVertexPerspectiveFunction calcPerspectiveFunction,
  DrawLineFunction drawLine
  );

void DrawLines(
  int CenterX, int CenterY,
  const Vertices& vertices2d,
  const Faces& faces,
  DrawLineFunction drawLine
  );

void DrawFlatSpaceCutShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices3d,
  const Faces& faces,
  CalculateLightFunction calcLightFunction,
  CalculateVertexPerspectiveFunction calcVertexPerspectiveFunction,
  CalculateVerticesPerspectiveFunction calcPerspectiveFunction,
  DrawLineFunction drawLine,
  RenderFunction render
  );
