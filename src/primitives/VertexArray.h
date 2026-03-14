#pragma once

class VertexArray
{
private:
  unsigned int m_ID;

public:
  VertexArray();
  ~VertexArray();

  void Bind();
  void Unbind();
};
