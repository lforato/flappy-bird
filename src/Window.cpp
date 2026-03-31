#include "Window.h"

#include <iostream>
#include <cstdlib>

Window::Window(int width, int height, const std::string& title)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (m_Window == nullptr)
  {
    std::cout << "FAILED TO CREATE WINDOW" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(m_Window);
  gladLoadGL(glfwGetProcAddress);
}

Window::~Window()
{
  glfwTerminate();
}

bool Window::ShouldClose() const
{
  return glfwWindowShouldClose(m_Window);
}

void Window::SwapBuffers()
{
  glfwSwapBuffers(m_Window);
}

void Window::PollEvents()
{
  glfwPollEvents();
}

GLFWwindow* Window::GetHandle() const
{
  return m_Window;
}
