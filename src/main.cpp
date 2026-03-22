#include "../src/primitives/ArrayBuffer.h"
#include "../src/primitives/VertexArray.h"
#include "../src/util/Shader.h"
#include "Core.h"
#include "primitives/IndexBuffer.h"
#include "util/Texture.h"

#include <cstdlib>
#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <stb_image/stb_image.h>

const int WIDTH = 800;
const int HEIGHT = 600;

// clang-format off
float vertices[] = {
//  x      y  |  u     v
  -0.5f,  0.5f, 0.0f, 1.0f, // top-left
  -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
   0.5f,  0.5f, 1.0f, 1.0f, // top-right
   0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
};


unsigned int indexes[] {
  0, 1, 2, // first 
  1, 2, 3, // second
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

  // Vertex Arrays
  VertexArray vao; 
  vao.Bind();

  // Vertex Buffer
  ArrayBuffer buffer(vertices, 16 * sizeof(float));
  buffer.DefineAttribPointer(0, 2, 4 * sizeof(float), (void*)0);
  buffer.DefineAttribPointer(1, 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));

  IndexBuffer indexBuf(indexes, 6 * sizeof(unsigned int));
  indexBuf.Bind();

  vao.Unbind();
  Shader program("../src/res/shader/vertex.glsl", "../src/res/shader/fragment.glsl");

  Texture tex("../src/res/textures/flappy.png"); 
  tex.SetShader(program.GetId(), "uTexture");

  // --- rendering ---

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!glfwWindowShouldClose(window))
  {
    GlError(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GlError(glClear(GL_COLOR_BUFFER_BIT));

    vao.Bind();
    tex.Bind();
    program.Bind();
    tex.Use(0);

    GlError(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) 0));

    GlError(glfwSwapBuffers(window));
    glfwPollEvents();
  }
}
