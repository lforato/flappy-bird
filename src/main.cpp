#include "Bird.h"
#include "Core.h"
#include "Event.h"
#include "GLFW/glfw3.h"
#include "primitives/Mesh.h"
#include "util/Shader.h"
#include "util/Texture.h"
#include "Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float WIDTH = 800.0f;
const float HEIGHT = 600.0f;

int main()
{
  Window* window = new Window(WIDTH, HEIGHT, "Flappy Bird");

  Bird* bird = new Bird;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glm::mat4 proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);

  EventDispatcher* orchestrator = new EventDispatcher;
  window->SetWindowUserPointer((void*)orchestrator);
  window->KeyCallback(EventDispatcher::KeyCallback);

  JumpHandler* jumpHandler = new JumpHandler(bird);
  orchestrator->RegisterHandler(jumpHandler);

  float lastTime = glfwGetTime();

  while (!window->ShouldClose())
  {
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    GlError(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GlError(glClear(GL_COLOR_BUFFER_BIT));

    bird->Update(deltaTime);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(bird->m_Position, 0.0f));
    model = glm::scale(model, glm::vec3(10, 10, 0));

    bird->GetMesh().Bind();
    bird->GetTexture().Bind();
    bird->GetProgram().Bind();

    glUniformMatrix4fv(glGetUniformLocation(bird->GetProgram().GetId(), "uModel"), 1, GL_FALSE,
                       glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(bird->GetProgram().GetId(), "uProj"), 1, GL_FALSE,
                       glm::value_ptr(proj));

    bird->GetTexture().Use(0);

    GlError(
        glDrawElements(GL_TRIANGLES, bird->GetMesh().GetIndexCount(), GL_UNSIGNED_INT, (void*)0));

    window->SwapBuffers();
    window->PollEvents();
    orchestrator->Flush();
  }

  delete bird;
  delete orchestrator;
  delete window;
}
