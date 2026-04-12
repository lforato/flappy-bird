
#include "Bird.h"

// clang-format off
std::vector<float> vertices = {
//  x      y  |  u     v
  00.0f, 13.0f, 0.0f, 1.0f, // top-left
  00.0f, 00.0f, 0.0f, 0.0f, // bottom-left
  18.0f, 13.0f, 1.0f, 1.0f, // top-right
  18.0f, 00.0f, 1.0f, 0.0f, // bottom-right
};

std::vector<unsigned int> indices = {
  0, 1, 2, // first
  1, 2, 3, // second
};
// clang-format on

Bird::Bird()
    : m_Mesh(vertices, indices, {2, 2}), m_Position(200.0f, 300.0f),
      m_Program("../src/res/shader/vertex.glsl", "../src/res/shader/fragment.glsl"),
      m_Texture("../src/res/textures/flappy.png")

{
  m_Texture.SetShader(m_Program.GetId(), "uTexture");
}

glm::vec2 Bird::GetPosition()
{
  return m_Position;
}

Mesh& Bird::GetMesh()
{
  return m_Mesh;
}

Shader& Bird::GetProgram()
{
  return m_Program;
}

Texture& Bird::GetTexture()
{
  return m_Texture;
}

void Bird::Update(float deltaTime)
{
  m_Velocity -= 980.0f * deltaTime;
  m_Position.y += m_Velocity * deltaTime;
}

void Bird::Jump()
{
  m_Velocity = 350.0f;
}
