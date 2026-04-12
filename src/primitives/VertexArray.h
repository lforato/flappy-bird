#pragma once

class VertexArray
{
private:
  unsigned int m_ID;

public:
  VertexArray();
  ~VertexArray();
  VertexArray(const VertexArray&) = delete;
  VertexArray& operator=(const VertexArray&) = delete;

  void Bind();
  void Unbind();
};
