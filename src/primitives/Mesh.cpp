#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices,
           const std::vector<unsigned int>& layout)
    : m_VBO(vertices.data(), vertices.size() * sizeof(float)),
      m_EBO(indices.data(), indices.size() * sizeof(unsigned int)), m_IndexCount(indices.size())
{
  m_VAO.Bind();
  m_VBO.Bind();
  m_EBO.Bind();

  std::size_t stride = 0;
  for (unsigned int components : layout)
    stride += components * sizeof(float);

  std::size_t offset = 0;
  for (unsigned int i = 0; i < layout.size(); i++)
  {
    m_VBO.DefineAttribPointer(i, layout[i], stride, (void*)offset);
    offset += layout[i] * sizeof(float);
  }

  m_VAO.Unbind();
}

void Mesh::Bind()
{
  m_VAO.Bind();
}

void Mesh::Unbind()
{
  m_VAO.Unbind();
}

unsigned int Mesh::GetIndexCount() const
{
  return m_IndexCount;
}
