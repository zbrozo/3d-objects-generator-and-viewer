#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <boost/log/trivial.hpp>

#include "AmigaFile.hpp"
#include "Object3D.hpp"

namespace
{
  
unsigned short swapByteOrder(const unsigned short value)
{
  const char* bytes = reinterpret_cast<const char*>(&value);
  const unsigned char lower = bytes[0];
  const unsigned char higher = bytes[1];
  const unsigned short result = static_cast<unsigned short> ( (lower << 8) | higher );
  return result;
}

// unsigned int swapByteOrder(const unsigned int value)
// {
//   const char* bytes = reinterpret_cast<const char*>(&value);
//   const unsigned char byte0 = bytes[0];
//   const unsigned char byte1 = bytes[1];
//   const unsigned char byte2 = bytes[2];
//   const unsigned char byte3 = bytes[3];
//   const unsigned int result = static_cast<unsigned int> ( (byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3 );
//   return result;
// }
  
// void WriteByte(std::ofstream& file, unsigned char value)
// {
//   file.write(reinterpret_cast<const char*>(&value), sizeof(char));
// }

void WriteWord(std::ofstream& file, unsigned short value)
{
  unsigned short swappedShort = swapByteOrder(value);
  file.write(reinterpret_cast<const char*>(&swappedShort), sizeof(short));
}

short ReadWord(std::ifstream& file)
{
  short swappedShort;
  file.read(reinterpret_cast<char*>(&swappedShort), sizeof(short));
  return swapByteOrder(swappedShort);
}
  
// void WriteLong(std::ofstream& file, unsigned int value)
// {
//   unsigned int swappedValue = swapByteOrder(value);
//   file.write(reinterpret_cast<const char*>(&swappedValue), sizeof(unsigned int));
// }
  
}

bool AmigaFile::Save(const std::string& name, const Object3D& object3d)
{
  // UWAGA - współrzędne są zapisywane w odwrotnej kolejności
  // ponieważ funkcja obrotu (na amidze) zapisuje dane w odwrotnej kolejności (jak na stosie)

  std::ofstream file(name, std::ios::out | std::ios::binary);
  
  if (!file)
    {
      BOOST_LOG_TRIVIAL(error) << "File is not opened (" << name << ")" ;
      return false;
    }

  BOOST_LOG_TRIVIAL(debug) << "Save file: " << name;

  WriteWord(file, object3d.GetVertices().size());
  WriteWord(file, object3d.GetFaces().size());

  for (auto it = object3d.GetVertices().rbegin(); it != object3d.GetVertices().rend(); ++it)
    {
      auto value = *it;
      WriteWord(file, value.getX());
      WriteWord(file, value.getY());
      WriteWord(file, value.getZ());
    }

  for (auto it = object3d.GetNormalVectorsInVertices().rbegin(); it != object3d.GetNormalVectorsInVertices().rend(); ++it)
    {
      auto value = *it;
      WriteWord(file, value.getX());
      WriteWord(file, value.getY());
      WriteWord(file, value.getZ());
    }
  
  for(auto face : object3d.GetFaces())
    {
      WriteWord(file, 0);
      WriteWord(file, face.size());
      for (auto number : face)
        {
          WriteWord(file, number * 8);
        }
    }

  for (auto it = object3d.GetNormalVectorsInFaces().rbegin(); it != object3d.GetNormalVectorsInFaces().rend(); ++it)
    {
      auto face = *it;
      WriteWord(file, face.getX());
      WriteWord(file, face.getY());
      WriteWord(file, face.getZ());
    }

  file.close();

  return true;
}

class ObjectLoaded : public Object3D
{
public:

  ObjectLoaded() : Object3D("")
  {
  }

  void SetVertices(const Vertices& vertices)
  {
    mVertices = vertices;
  }

  void SetFaces(const Faces& faces)
  {
    mFaces = faces;
  }

  void SetNormalVectorsInVertices(const Vectors& vectors)
  {
    mNormalVectorsInVertices = vectors;
  }

  void SetNormalVectorsInFaces(const Vectors& vectors)
  {
    mNormalVectorsInFaces = vectors;
  }
  
};


bool AmigaFile::Load(const std::string& name, Object3D& object3d)
{
  // UWAGA - współrzędne są zapisywane w odwrotnej kolejności
  // ponieważ funkcja obrotu (na amidze) zapisuje dane w odwrotnej kolejności (jak na stosie)

  std::ifstream file(name, std::ios::in | std::ios::binary);
  
  if (!file)
    {
      BOOST_LOG_TRIVIAL(error) << "File is not opened";
      return false;
    }

  BOOST_LOG_TRIVIAL(debug) << "Load file: " << name;
  
  unsigned short verticesCount = ReadWord(file);
  unsigned short facesCount = ReadWord(file);

  BOOST_LOG_TRIVIAL(debug) << "vertices = " + std::to_string(verticesCount);

  Vertices vertices;
  for (int i = 0; i < verticesCount; i++)
    {
      const auto x = ReadWord(file);
      const auto y = ReadWord(file);
      const auto z = ReadWord(file);
      const Vertex vertex(x,y,z);
      vertices.push_back(vertex);
    }
  
  std::reverse(vertices.begin(), vertices.end());
  
  Vectors normalVectorsInVertices;
  for (int i = 0; i < verticesCount; i++)
    {
      const auto x = ReadWord(file);
      const auto y = ReadWord(file);
      const auto z = ReadWord(file);
      const Vector vector({x,y,z});
      normalVectorsInVertices.push_back(vector);
    }
  std::reverse(normalVectorsInVertices.begin(), normalVectorsInVertices.end());

  BOOST_LOG_TRIVIAL(debug) << "faces = " + std::to_string(facesCount);

  Faces faces;
  for (int i = 0; i < facesCount; i++)
    {
      ReadWord(file); // not used
      const auto faceSize = ReadWord(file);
      
      Face face;
      for (int faceNr = 0; faceNr < faceSize; faceNr++)
        {
          const auto vertexNr = ReadWord(file) / 8;
          face.push_back(vertexNr);
        }
      faces.push_back(face);
    }

  Vectors normalVectorsInFaces;
  for (int i = 0; i < facesCount; i++)
    {
      const auto x = ReadWord(file);
      const auto y = ReadWord(file);
      const auto z = ReadWord(file);
      const Vector vector({x,y,z});
      normalVectorsInFaces.push_back(vector);
    }
  std::reverse(normalVectorsInFaces.begin(), normalVectorsInFaces.end());
  
  file.close();

  ObjectLoaded loaded;
  loaded.SetVertices(vertices);
  loaded.SetFaces(faces);
  loaded.SetNormalVectorsInVertices(normalVectorsInVertices);
  loaded.SetNormalVectorsInFaces(normalVectorsInFaces);

  object3d = loaded;
    
  return true;
}
