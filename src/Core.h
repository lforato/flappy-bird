#pragma once

#include "glad/gl.h"

#include <iostream>

#define GlError(x)                                                                                 \
  ClearErrors();                                                                                   \
  x;                                                                                               \
  GetErrors(__FILE__, __LINE__)

inline void ClearErrors()
{
  while (glGetError() != GL_NO_ERROR)
  {
  }
}

inline void GetErrors(const char* file, const int line)
{
  GLenum err;

  while ((err = glGetError()) != GL_NO_ERROR)
  {
    std::cerr << file << ":" << line << ":: 0x" << std::hex << err << '\n';
  }
}
