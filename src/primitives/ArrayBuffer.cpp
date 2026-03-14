#include "ArrayBuffer.h"

#include "../Core.h"
#include "glad/gl.h"

ArrayBuffer::ArrayBuffer(const void* data, std::size_t size, GLenum mode)
{
  GlError(glGenBuffers(1, &m_ID));
  this->Bind();
  GlError(glBufferData(GL_ARRAY_BUFFER, size, data, mode));
}

ArrayBuffer::~ArrayBuffer()
{
  GlError(glDeleteBuffers(1, &m_ID));
}

void ArrayBuffer::DefineAttribPointer(unsigned int index, unsigned int components,
                                      std::size_t stride, void* offset)
{
  this->Bind();
  GlError(glVertexAttribPointer(index, components, GL_FLOAT, GL_FALSE, stride, offset));
  GlError(glEnableVertexAttribArray(index));
}

void ArrayBuffer::Bind()
{
  GlError(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void ArrayBuffer::Unbind()
{
  GlError(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
