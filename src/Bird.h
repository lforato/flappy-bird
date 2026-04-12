#pragma once

#include "glm/glm.hpp"
#include "primitives/Mesh.h"
#include "util/Shader.h"
#include "util/Texture.h"

class Bird
{
public:
  float m_Velocity = 0.0f;
  glm::vec2 m_Position;
  Mesh m_Mesh;
  Shader m_Program;
  Texture m_Texture;

public:
  Bird();
  ~Bird() = default;

  glm::vec2 GetPosition();
  Mesh& GetMesh();
  Shader& GetProgram();
  Texture& GetTexture();

  void Update(float deltaTime);
  void Jump();
};
