#include "./Texture.h"

#include <iostream>
#include <stb_image/stb_image.h>

Texture::Texture(const char* path, GLenum wrap, GLenum filter)
{
  glGenTextures(1, &m_ID);
  Bind();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

  int width, height, nChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
  if (!data)
  {
    std::cerr << "Failed to load image" << std::endl;
    exit(EXIT_FAILURE);
  }

  GLenum format = (nChannels == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  Unbind();
}

void Texture::SetShader(unsigned int shaderId, const char* uniformName)
{
  m_UniformName = uniformName;
  m_ShaderID = shaderId;
}

void Texture::Bind()
{
  glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Use(unsigned int unit)
{
  glUniform1i(glGetUniformLocation(m_ShaderID, m_UniformName), unit);
}

void Texture::Unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}
