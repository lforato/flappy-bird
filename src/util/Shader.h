#pragma once

#include <glad/gl.h>
#include <string>

class Shader
{
private:
  unsigned int m_ID;

  static std::string LoadFile(std::string path);
  unsigned int CompileShader(std::string shader, GLenum type);

public:
  Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
  ~Shader() = default;

  void Bind();
  void Unbind();
};
