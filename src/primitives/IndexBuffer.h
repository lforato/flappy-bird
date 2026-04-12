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
  IndexBuffer(const IndexBuffer&) = delete;
  IndexBuffer& operator=(const IndexBuffer&) = delete;

  void Bind();

  void Unbind();
};
