#include "VertexArray.h"

#include "../Core.h"
#include "glad/gl.h"

VertexArray::VertexArray()
{
  GlError(glGenVertexArrays(1, &m_ID));
}

VertexArray::~VertexArray()
{
  GlError(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::Bind()
{
  GlError(glBindVertexArray(m_ID));
}

void VertexArray::Unbind()
{
  GlError(glBindVertexArray(0));
}
