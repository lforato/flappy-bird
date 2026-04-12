#pragma once

#include "glad/gl.h"

#include <cstddef>

class ArrayBuffer
{
private:
  unsigned int m_ID;

public:
  ArrayBuffer(const void* data, std::size_t size, GLenum mode = GL_STATIC_DRAW);
  ~ArrayBuffer();
  ArrayBuffer(const ArrayBuffer&) = delete;
  ArrayBuffer& operator=(const ArrayBuffer&) = delete;

  void UpdateData(const void* data, std::size_t size);
  void DefineAttribPointer(unsigned int index, unsigned int components, std::size_t stride, void* offset);

  void Bind();
  void Unbind();
};
