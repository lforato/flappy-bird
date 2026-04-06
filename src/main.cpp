#include "Core.h"
#include "primitives/Mesh.h"
#include "util/Shader.h"
#include "util/Texture.h"
#include "Window.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const float WIDTH = 800.0f;
const float HEIGHT = 600.0f;

// clang-format off
std::vector<float> vertices = {
//  x      y  |  u     v
  00.0f, 13.0f, 0.0f, 1.0f, // top-left
  00.0f, 00.0f, 0.0f, 0.0f, // bottom-left
  18.0f, 13.0f, 1.0f, 1.0f, // top-right
  18.0f, 00.0f, 1.0f, 0.0f, // bottom-right
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

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(10, 10, 0));
  model = glm::translate(model, glm::vec3(20, 20, 0));

  glm::mat4 proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);


  while (!window.ShouldClose())
  {
    GlError(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GlError(glClear(GL_COLOR_BUFFER_BIT));

    mesh.Bind();
    tex.Bind();
    program.Bind();

    glUniformMatrix4fv(glGetUniformLocation(program.GetId(), "uModel"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(program.GetId(), "uProj"), 1, GL_FALSE, glm::value_ptr(proj));

    tex.Use(0);

    GlError(glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, (void*)0));

    window.SwapBuffers();
    window.PollEvents();
  }
}
