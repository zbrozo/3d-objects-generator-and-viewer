#include "Types.hpp"
#include "Vertices.hpp"
#include "Vectors.hpp"
#include "Faces.hpp"

#include "ViewerSortingFaces.hpp"
#include "ViewerDraw.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

void DrawFlatShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInFaces,
  RenderFunction render
  )
{
  const auto sortedFaces = SortFaceNumbers(vertices2d, faces);

  for (const auto& faceNr : sortedFaces)
  {
    std::vector<SDL_Vertex> geometryVertices;

    SDL_Vertex vertex;
    vertex.tex_coord.x = 0;
    vertex.tex_coord.y = 0;
    vertex.color = colors[colorNumbersInFaces[faceNr]];

    const auto& face = faces[faceNr];
    const size_t size = face.size();

    for (size_t i = 0; i < size; ++i)
    {
      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      geometryVertices.push_back(vertex);
    }

    render(size, geometryVertices, nullptr);
  }
}

void DrawGouraudShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInVertices,
  RenderFunction render
  )
{
  const auto sortedFaces = SortFaceNumbers(vertices2d, faces);

  for (auto faceNr : sortedFaces)
  {
    const auto& face = faces[faceNr];

    std::vector<SDL_Vertex> geometryVertices;

    SDL_Vertex vertex;
    vertex.tex_coord.x = 0;
    vertex.tex_coord.y = 0;

    const size_t size = face.size();

    for (size_t i = 0; i < size; ++i)
    {
      vertex.color = colors[colorNumbersInVertices[face[i]]];

      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      geometryVertices.push_back(vertex);
    }

    render(size, geometryVertices, nullptr);
  }
}

void DrawTextureMapping(
  int CenterX, int CenterY,
  const Vertices& vertices2d,
  const Faces& faces,
  SDL_Texture* texture,
  RenderFunction render
  )
{
  for (auto face : faces)
  {
    if (!face.IsVisible(vertices2d))
    {
      continue;
    }

    std::vector<SDL_Vertex> geometryVertices;

    float textureCoords[][2] = {
      {0.0f, 0.0f},
      {0.0f,1.0f},
      {1.0f, 1.0f},
      {1.0f, 0.0f}};

    const size_t size = face.size();

    for (size_t i = 0; i < size; ++i)
    {
      SDL_Vertex vertex;
      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      vertex.tex_coord.x = textureCoords[i][0];
      vertex.tex_coord.y = textureCoords[i][1];
      vertex.color = SDL_Color{255,255,255,255};
      geometryVertices.push_back(vertex);
    }

    render(size, geometryVertices, texture);
  }
}

void DrawNormalVectorsInFaces(
  int CenterX, int CenterY,
  const Vertices& vertices,
  const Vertices& vertices2d,
  const Faces& faces,
  const Vectors& normalVectorsInFaces,
  CalculatePerspectiveFunction calcPerspectiveFunction,
  DrawLineFunction drawLine
  )
{
  unsigned int faceNr = 0;

  for (auto face : faces)
  {
    if (!face.IsVisible(vertices2d))
    {
      ++faceNr;
      continue;
    }

    const auto v = face.GetCenter(vertices);
    const auto vBegin = calcPerspectiveFunction(v);
    const auto vEnd = calcPerspectiveFunction(v + normalVectorsInFaces[faceNr].getEnd());

    drawLine(
      vBegin.getX() + CenterX, vBegin.getY() + CenterY,
      vEnd.getX() + CenterX, vEnd.getY() + CenterY
      );

    ++faceNr;
  }
}

void DrawNormalVectorsInVertices(
  int CenterX, int CenterY,
  const Vertices& vertices,
  const Vertices& vertices2d,
  const Faces& faces,
  const Vectors& normalVectorsInVertices,
  CalculatePerspectiveFunction calcPerspectiveFunction,
  DrawLineFunction drawLine
  )
{
  unsigned int faceNr = 0;

  for (auto face : faces)
  {
    if (!face.IsVisible(vertices2d))
    {
      ++faceNr;
      continue;
    }

    const unsigned int size = face.size();

    for (unsigned int i = 0; i < size; ++i)
    {
      const auto vBegin = vertices2d[face[i]];
      const auto vEnd = calcPerspectiveFunction(vertices[face[i]] + normalVectorsInVertices[face[i]].getEnd());

      drawLine(
        vBegin.getX() + CenterX, vBegin.getY() + CenterY,
        vEnd.getX() + CenterX, vEnd.getY() + CenterY
        );
    }

    ++faceNr;
  }
}

void DrawLines(
  int CenterX, int CenterY,
  const Vertices& vertices2d,
  const Faces& faces,
  DrawLineFunction drawLine
  )
{
  for (auto face : faces)
  {
    if (!face.IsVisible(vertices2d))
    {
      continue;
    }

    const unsigned int size = face.size();

    for (unsigned int i = 0; i < size; ++i)
    {
      auto x1 = vertices2d[face[i]].getX();
      auto y1 = vertices2d[face[i]].getY();

      int x2 = 0;
      int y2 = 0;

      if (i == size-1)
      {
        x2 = vertices2d[face[0]].getX();
        y2 = vertices2d[face[0]].getY();
      }
      else
      {
        x2 = vertices2d[face[i + 1]].getX();
        y2 = vertices2d[face[i + 1]].getY();
      }

      drawLine(
        x1 + CenterX, y1 + CenterY,
        x2 + CenterX, y2 + CenterY
        );
    }
  }
}

bool FindIntersectionPoint(const Vertex& v1, const Vertex& v2, Vertex& found)
{
  return false;
}

void DrawFlatShadedFaces_SpaceCut(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices3d,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInFaces,
  RenderFunction render
  )
{
  Vertices vertices1;
  Vertices vertices2;
  Faces faces1;
  Faces faces2;

  auto AddVertex = [](Vertex v, Vertices& vertices)
  {
    auto it = std::find(vertices.begin(), vertices.end(), v);
    if (it != vertices.end())
    {
      return static_cast<int>(std::distance(vertices.begin(), it));
    }
    vertices.push_back(v);
    return static_cast<int>(vertices.size());
  };

  const auto sortedFaces = SortFaceNumbers(vertices2d, faces);

  for (const auto& faceNr : sortedFaces)
  {
    Face face1;
    Face face2;

    const auto& face = faces[faceNr];
    const size_t size = face.size();

    for (size_t i = 0; i < size; ++i)
    {
      Vertex v1;
      Vertex v2;

      // get vector vertices
      v1 = vertices3d[face[i]];
      if (i < faceNr)
      {
        v2 = vertices3d[face[i + 1]];
      }
      else
      {
        v2 = vertices3d[0];
      }

      if (v1.getZ() >= 0 && v2.getZ() >= 0)
      {
        auto i = AddVertex(v1,vertices1);
        face1.push_back(i);
        i = AddVertex(v2, vertices1);
        face1.push_back(i);
        continue;
      }

      if (v1.getZ() <= 0 && v2.getZ() <= 0)
      {
        auto i = AddVertex(v1, vertices2);
        face2.push_back(i);
        i = AddVertex(v2, vertices2);
        face2.push_back(i);
        continue;
      }

      Vertex found;
      if (FindIntersectionPoint(v1, v2, found))
      {
        auto i = AddVertex(v1,vertices1);
        face1.push_back(i);
        i = AddVertex(found,vertices1);
        face1.push_back(i);

        i = AddVertex(found,vertices2);
        face2.push_back(i);
        i = AddVertex(v2,vertices2);
        face2.push_back(i);
      }
    }

    if (face1.size())
    {
      faces1.push_back(face1);
    }

    if (face2.size())
    {
      faces2.push_back(face2);
    }
  }

  for (const auto& faceNr : sortedFaces)
  {
    std::vector<SDL_Vertex> geometryVertices;

    SDL_Vertex vertex;
    vertex.tex_coord.x = 0;
    vertex.tex_coord.y = 0;
    vertex.color = colors[colorNumbersInFaces[faceNr]];

    const auto& face = faces[faceNr];
    const size_t size = face.size();

    for (size_t i = 0; i < size; ++i)
    {
      const auto x = vertices2d[face[i]].getX();
      const auto y = vertices2d[face[i]].getY();
      vertex.position.x = x + CenterX;
      vertex.position.y = y + CenterY;
      geometryVertices.push_back(vertex);
    }

    render(size, geometryVertices, nullptr);
  }
}
