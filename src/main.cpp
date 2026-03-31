#include "Core.h"
#include "primitives/Mesh.h"
#include "util/Shader.h"
#include "util/Texture.h"
#include "Window.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;

// clang-format off
std::vector<float> vertices = {
//  x      y  |  u     v
  -0.5f,  0.5f, 0.0f, 1.0f, // top-left
  -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
   0.5f,  0.5f, 1.0f, 1.0f, // top-right
   0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
};

std::vector<unsigned int> indices = {
  0, 1, 2, // first
  1, 2, 3, // second
};
// clang-format on

int main()
{
  Window window(WIDTH, HEIGHT, "Flappy Bird");

  Mesh mesh(vertices, indices, {2, 2});

  Shader program("../src/res/shader/vertex.glsl", "../src/res/shader/fragment.glsl");

  Texture tex("../src/res/textures/flappy.png");
  tex.SetShader(program.GetId(), "uTexture");

  glm::mat4 model = glm::mat4(1.0);
  model = glm::translate(model, glm::vec3(1.0f, 1.0f, 0.0f));

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!window.ShouldClose())
  {
    GlError(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GlError(glClear(GL_COLOR_BUFFER_BIT));

    mesh.Bind();
    tex.Bind();
    program.Bind();

    glUniformMatrix4fv(glGetUniformLocation(program.GetId(), "uModel"), 1, GL_FALSE,
                       glm::value_ptr(model));

    tex.Use(0);

    GlError(glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, (void*)0));

    window.SwapBuffers();
    window.PollEvents();
  }
}
