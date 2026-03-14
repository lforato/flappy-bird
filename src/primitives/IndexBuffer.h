#pragma once

#include "glad/gl.h"

#include <cstddef>

class IndexBuffer
{
private:
  unsigned int m_ID;

public:
  IndexBuffer(const void* data, std::size_t size, GLenum mode = GL_STATIC_DRAW);
  ~IndexBuffer();

  void Bind();

  void Unbind();
};
