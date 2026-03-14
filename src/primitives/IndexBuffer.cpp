#include "IndexBuffer.h"

#include "glad/gl.h"
#include "../Core.h"

IndexBuffer::IndexBuffer(const void* data, std::size_t size, GLenum mode)
{
  GlError(glGenBuffers(1, &m_ID));
  this->Bind();
  GlError(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode));
}

IndexBuffer::~IndexBuffer()
{
  GlError(glDeleteBuffers(1, &m_ID));
}

void IndexBuffer::Bind()
{
  GlError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::Unbind()
{
  GlError(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
