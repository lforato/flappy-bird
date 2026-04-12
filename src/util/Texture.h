#pragma once

#include "glad/gl.h"
class Texture
{
private:
  unsigned int m_ID;
  unsigned int m_ShaderID;
  const char* m_UniformName;

public:
  Texture(const char* path, GLenum wrap = GL_REPEAT, GLenum filter = GL_NEAREST);
  ~Texture() = default;
  Texture(const Texture&) = delete;
  Texture& operator=(const Texture&) = delete;

  void SetShader(unsigned int shaderId, const char* uniformName);
  void Bind();
  void Use(unsigned int unit = 0);
  void Unbind();
};
