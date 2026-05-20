#pragma once

class IGenerator
{
public:
  
  virtual ~IGenerator() = default;

  virtual void Generate() = 0;

  void SetTraingulated()
  {
    mTriangulated = true;
  }

protected:
  
  bool mTriangulated = false;
};

