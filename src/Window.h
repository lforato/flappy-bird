#pragma once

#include "glad/gl.h"

#include <glfw/glfw3.h>
#include <string>

class Window
{
private:
  GLFWwindow* m_Window;

public:
  Window(int width, int height, const std::string& title);
  ~Window();

  bool ShouldClose() const;
  void SwapBuffers();
  void PollEvents();
  void SetWindowUserPointer(void* ptr);

  GLFWwindow* GetHandle() const;
  void KeyCallback(GLFWkeyfun callback);
};
