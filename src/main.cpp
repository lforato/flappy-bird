#include <cstdlib>
#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

// clang-format off
float vertices[] = {
   0.0f, 0.5f, // top
  -0.5f, 0.0f, // left
   0.5f, 0.0f, // right
};
// clang-format on 

int main()
{
  // --- init GLFW ---
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // --- create window ---
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Flappy Bird", NULL, NULL);
  if (window == nullptr)
  {
    std::cout << "FAILED TO CREATE WINDOW" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // --- creating the context for opengl functions ---
  glfwMakeContextCurrent(window);
  gladLoadGL(glfwGetProcAddress);

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
  glEnableVertexAttribArray(0);

  // --- rendering ---
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
