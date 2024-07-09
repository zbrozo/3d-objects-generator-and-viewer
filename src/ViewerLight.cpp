#include <vector>
#include <fstream>
#include <regex>

#include "Types.hpp"
#include "Vectors.hpp"
#include "ViewerLight.hpp"

#include <SDL2/SDL.h>

namespace
{

unsigned int readColor(const std::string& line)
{
  std::regex r("([[:digit:]]+)");  
  
  auto words_begin = std::sregex_iterator(line.begin(), line.end(), r);
  auto words_end = std::sregex_iterator();

  int nr = 0;
  int color = 0;
 
  for (std::sregex_iterator i = words_begin; i != words_end; ++i)
  {
    std::smatch match = *i;
    std::string match_str = match.str();

    if (nr == 0)
    {
      color |= std::stoi(match_str);
    }
   
    if (nr == 1)
    {
      color |= (std::stoi(match_str) << 8);
    }

    if (nr == 2)
    {
      color |= (std::stoi(match_str) << 16);
    }

    ++nr;
  }
 
  return color;
}

auto readColors(const char* paletteName, int maxColors)
{
  std::string line;
  std::vector<int> colors;
  
  std::ifstream file(paletteName);
  
  if (!file.is_open())
  {
    return colors;
  }

  int nr = 0;
  
  while(std::getline(file, line) && nr < maxColors)
  {
    if (nr > 2)
    {
      auto color = readColor(line);
      colors.push_back(color);
    }
    
    ++nr;
  }
  
  return colors;
}

} // namespace

void PrepareColors(const char* paletteName, SDL_Color* colors)
{
  std::vector<int> colorsFromFile;

  if (paletteName != nullptr)
  {
    colorsFromFile = readColors(paletteName, maxColorNumber);
  }
  
  if (colorsFromFile.size())
  {
    std::reverse(colorsFromFile.begin(), colorsFromFile.end());
    
    for (int i = 0; i < maxColorNumber; ++i)
    {
      colors[i] = SDL_Color{
        static_cast<Uint8>((colorsFromFile[i] >> 16) & 255),
        static_cast<Uint8>((colorsFromFile[i] >> 8) & 255),
        static_cast<Uint8>(colorsFromFile[i] & 255),
        255
      };
    }
  }
  else
  {
    for (int i = 0; i < maxColorNumber; ++i)
    {
      const int maxValue = 255;
      unsigned char col = ((-i + maxColorNumber) * maxValue) /  maxColorNumber;
      colors[i] = SDL_Color{col, col, col, maxValue};
    }
  }
}

void CalculateLight(
  int light,
  const Vectors& normalVectorsInFaces,
  const Vectors& normalVectorsInVertices,
  std::vector<int>& colorNumbersInFaces,
  std::vector<int>& colorNumbersInVertices)
{
  auto calcColorNumber = [light](const Vector& v){
    Vertex lightVector(0,0,light);
    const int z = (v.getZ() * lightVector.getZ()) + (maxLightValue * maxLightValue);
    const int id = (z * maxColorNumber) / (maxLightValue * 2 * maxLightValue);
    return id;
  };
  
  for (auto v : normalVectorsInFaces)
  {
    colorNumbersInFaces.push_back(calcColorNumber(v));
  }
  
  for (auto v : normalVectorsInVertices)
  {
    colorNumbersInVertices.push_back(calcColorNumber(v));
  }
}
