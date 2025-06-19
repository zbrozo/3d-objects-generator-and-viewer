#include "Types.hpp"
#include "Vertices.hpp"
#include "Vectors.hpp"
#include "Faces.hpp"
#include "Object3DBuilder.hpp"
#include "ViewerSortingFaces.hpp"
#include "ViewerDraw.hpp"

#include <SDL2/SDL.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <sys/types.h>

void DrawFlatShadedFaces(
  int CenterX, int CenterY,
  SDL_Color* colors,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInFaces,
  RenderFunction render
  )
{
  const auto sortedFaces = GetVisibleFaceNumbers(vertices2d, faces);

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
  const auto sortedFaces = GetVisibleFaceNumbers(vertices2d, faces);

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
  CalculateVertexPerspectiveFunction calcPerspectiveFunction,
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
  CalculateVertexPerspectiveFunction calcPerspectiveFunction,
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

namespace {

void DrawFlatSpaceCutShadedFaces(
  int CenterX, int CenterY,
  const Vertices& vertices,
  const Faces& faces,
  std::vector<std::pair<size_t, size_t>> facesPairs,
  SDL_Color* colors,
  std::vector<int> colorNumbersInFaces,
  RenderFunction render)    
{
  for (size_t faceNr = 0; faceNr < faces.size(); faceNr++)
  {
    std::vector<SDL_Vertex> geometryVertices;

    size_t baseFaceNr = 0;
    const auto found = std::find_if(facesPairs.cbegin(), facesPairs.cend(), [&](std::pair<size_t, size_t>(x)){ return x.first == faceNr;});
    if (found != facesPairs.end())
    {
      baseFaceNr = found->second;
    }
    
    SDL_Vertex vertex;
    vertex.tex_coord.x = 0;
    vertex.tex_coord.y = 0;
    vertex.color = colors[colorNumbersInFaces[baseFaceNr]];

    const auto& face = faces[faceNr];
    const size_t size = face.size();

    for (size_t i = 0; i < size; ++i)
    {
      auto vertexNr = face[i];
      vertex.position.x = vertices[vertexNr].getX() + CenterX;
      vertex.position.y = vertices[vertexNr].getY() + CenterY;
      geometryVertices.push_back(vertex);
    }

    render(size, geometryVertices, nullptr);
  }
}

}

void DrawFlatSpaceCutShadedFaces(
  int spacecutValueZ,
  int CenterX, int CenterY,
  SDL_Color* colors1,
  SDL_Color* colors2,
  const Vertices& vertices3d,
  const Vertices& vertices2d,
  const Faces& faces,
  const std::vector<int>& colorNumbersInFaces,
  CalculateVerticesPerspectiveFunction calcVerticesPerspectiveFunction,
  RenderFunction render
  )
{
  Vertices vertices = vertices3d;

  Faces faces1;
  Faces faces2;

  auto FindIntersectionPoint = [](const Vertex& v1, const Vertex& v2, Vertex& found, int z)
  {
    const double a = v2.getX() - v1.getX();
    const double b = v2.getY() - v1.getY();
    const double c = v2.getZ() - v1.getZ();

    const double x = a / c * (z - v1.getZ()) + v1.getX();
    const double y = b / c * (z - v1.getZ()) + v1.getY();
    
    found = Vertex(static_cast<int>(x), static_cast<int>(y), z);
    return true;
  };

  // return: vertex index in vertices
  auto AddVertex = [](Vertex v, Vertices& vertices)
  {
    auto it = std::find(vertices.begin(), vertices.end(), v);
    if (it != vertices.end())
    {
      return static_cast<int>(std::distance(vertices.begin(), it));
    }
    vertices.push_back(v);
    return static_cast<int>(vertices.size() - 1);
  };
  
  const auto visibleFaces = GetVisibleFaceNumbers(vertices2d, faces);

  std::vector<std::pair<size_t, size_t>> facesPairs1;
  std::vector<std::pair<size_t, size_t>> facesPairs2;

  for (const auto faceNr : visibleFaces) 
  {
    Face face1;
    Face face2;

    const auto& face = faces[faceNr];
    const size_t faceSize = face.size();
    
    // find intersection in each 3d vector and split its parts to different arrays
    for (size_t i = 0; i < faceSize; ++i)
    {
      // get vector vertices
      Vertex v1 = vertices3d[face[i]];
      Vertex v2;

      if (i < (faceSize-1))
      {
        v2 = vertices3d[face[i + 1]];
      }
      else
      {
        v2 = vertices3d[face[0]];
      }
      
      if (v1.getZ() == spacecutValueZ)
      {
        if (std::all_of(face.cbegin(), face.cend(), [&](int x) { return vertices3d[x].getZ() >= spacecutValueZ; }))
        {
          //std::cout << " 1";
          face1.push_back(AddVertex(v1,vertices));
          continue;
        }

        if (std::all_of(face.cbegin(), face.cend(), [&](int x) { return vertices3d[x].getZ() <= spacecutValueZ; }))
        {
          //std::cout << " 2";
          face2.push_back(AddVertex(v1,vertices));
          continue;
        }

        //std::cout << " 3";
        face1.push_back(AddVertex(v1,vertices));
        face2.push_back(AddVertex(v1,vertices));
        continue;
      }

      if (v1.getZ() > spacecutValueZ && v2.getZ() >= spacecutValueZ)
      {
        // brak przeciecia
        //std::cout << " 4";
        face1.push_back(AddVertex(v1,vertices));
        continue;
      }

      if (v1.getZ() < spacecutValueZ && v2.getZ() <= spacecutValueZ)
      {
        // brak przeciecia
        //std::cout << " 5";
        face2.push_back(AddVertex(v1, vertices));
        continue;
      }

      Vertex found;
      if (FindIntersectionPoint(v1, v2, found, spacecutValueZ))
      {
        //std::cout << " 6";
        if (v1.getZ() > spacecutValueZ)
        {
          face1.push_back(AddVertex(v1,vertices));
        }
        else
        {
          face2.push_back(AddVertex(v1,vertices));
        }

        face1.push_back(AddVertex(found,vertices));
        face2.push_back(AddVertex(found,vertices));
      }
    }

    //std::cout << std::endl;

    if (face1.size())
    {
      faces1.push_back(face1);
      facesPairs1.push_back(std::pair<size_t, size_t>(faces1.size() - 1, faceNr));
    }

    if (face2.size())
    {
      faces2.push_back(face2);
      facesPairs2.push_back(std::pair<size_t, size_t>(faces2.size() - 1, faceNr));
    }
  }

  // std::cout << "=======" << std::endl;
  // std::cout << vertices3d << std::endl;
  // std::cout << "-------" << std::endl;
  // std::cout << faces << std::endl;
  // std::cout << "#######" << std::endl;
  // std::cout << vertices << std::endl;
  // std::cout << "-------" << std::endl;
  // std::cout << faces1 << std::endl;
  // std::cout << "-------" << std::endl;
  // std::cout << faces2 << std::endl;
  // std::cout << "-------" << std::endl;
  // std::cout << "&&&&&&&" << std::endl;

  auto newObjectVertices2d = calcVerticesPerspectiveFunction(vertices);

  DrawFlatSpaceCutShadedFaces(
    CenterX, CenterY,
    newObjectVertices2d,
    faces1,
    facesPairs1,
    colors1,
    colorNumbersInFaces,
    render);
 
  DrawFlatSpaceCutShadedFaces(
    CenterX, CenterY,
    newObjectVertices2d,
    faces2,
    facesPairs2,
    colors2,
    colorNumbersInFaces,
    render);

}
