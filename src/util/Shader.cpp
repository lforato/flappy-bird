#include "Shader.h"

#include <fstream>
#include <glad/gl.h>
#include <string>

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
  m_ID = glCreateProgram();

  std::string vertexInput = Shader::LoadFile(vertexShaderPath);
  std::string fragmentInput = Shader::LoadFile(fragmentShaderPath);

  unsigned int vertex = CompileShader(vertexInput, GL_VERTEX_SHADER);
  unsigned int fragment = CompileShader(fragmentInput, GL_FRAGMENT_SHADER);

  glAttachShader(m_ID, vertex);
  glAttachShader(m_ID, fragment);
  glLinkProgram(m_ID);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

}

std::string Shader::LoadFile(std::string path)
{
  std::fstream file(path);
  std::string line;
  std::string result;

  while (getline(file, line))
  {
    result += line + '\n';
  }

  return result;
}

unsigned int Shader::CompileShader(std::string shader, GLenum type)
{
  const char* str = shader.c_str();
  unsigned int compiledShader = glCreateShader(type);
  glShaderSource(compiledShader, 1, &str, 0);
  glCompileShader(compiledShader);

  return compiledShader;
}

void Shader::Bind()
{
  glUseProgram(m_ID);
}

void Shader::Unbind()
{
  glUseProgram(0);
}
