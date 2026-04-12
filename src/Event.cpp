// clang-format off
#include "Bird.h"
#include "Event.h"

#include <iostream>
// clang-format on

// Events ----------------------------------------------------------------------

KeyPressEvent::KeyPressEvent(int key, int scancode, int action, int mods) : m_Key(key), Event() {}

EventType KeyPressEvent::GetEventType() const
{
  return m_EventType;
}

const char* KeyPressEvent::GetName() const
{
  if (m_Key == GLFW_KEY_SPACE)
    return "Space Key";

  return "None";
}

// Handler ---------------------------------------------------------------------

Handler::Handler(EventType e) : m_EventType(e) {}

// JumpHandler -----------------------------------------------------------------

JumpHandler::JumpHandler(Bird* bird) : Handler(EventType::KeyPressed), m_Bird(bird) {}

void JumpHandler::Exec()
{
  m_Bird->Jump();
}

bool JumpHandler::IsInterested(Event* e) const
{
  auto* key = static_cast<KeyPressEvent*>(e);
  return key->m_Key == GLFW_KEY_SPACE;
}

// EventDispatcher ----------------------------------------------------------------

void EventDispatcher::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  auto* orchestrator = static_cast<EventDispatcher*>(glfwGetWindowUserPointer(window));

  switch (action)
  {
  case GLFW_PRESS:
    KeyPressEvent* e = new KeyPressEvent(key, scancode, action, mods);
    orchestrator->m_Queue.emplace_back(e);
    std::cout << "key pressed -> " << e->GetName() << std::endl;
    break;
  }
}

void EventDispatcher::RegisterHandler(Handler* h)
{
  m_Handlers[h->GetEventType()].emplace_back(h);
}

void EventDispatcher::UnregisterHandler(Handler* h)
{
  auto& vec = m_Handlers[h->GetEventType()];
  auto it = std::find(vec.begin(), vec.end(), h);
  if (it != vec.end())
    vec.erase(it);
}

void EventDispatcher::Flush()
{
  for (auto it : m_Queue)
  {
    for (auto handler : m_Handlers[it->GetEventType()])
    {
      if (handler->IsInterested(it))
        handler->Exec();
    }
  }

  for (auto* e : m_Queue)
    delete e;
  m_Queue.clear();
}
