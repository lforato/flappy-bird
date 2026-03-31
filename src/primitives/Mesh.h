#pragma once

#include "ArrayBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <vector>

class Mesh
{
private:
  VertexArray m_VAO;
  ArrayBuffer m_VBO;
  IndexBuffer m_EBO;
  unsigned int m_IndexCount;

public:
  Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices,
       const std::vector<unsigned int>& layout);

  void Bind();
  void Unbind();

  unsigned int GetIndexCount() const;
};
