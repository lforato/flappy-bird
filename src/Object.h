#pragma once

#include "glm/glm.hpp"
#include "primitives/Mesh.h"
#include "util/Shader.h"
#include "util/Texture.h"

class Object
{
public:
  virtual glm::vec2 GetPosition() = 0;
  virtual Mesh& GetMesh() = 0;
  virtual Shader& GetProgram() = 0;
  virtual Texture& GetTexture() = 0;
};
