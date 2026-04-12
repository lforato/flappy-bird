#pragma once

#include "GLFW/glfw3.h"

#include <unordered_map>
#include <vector>

// Events ----------------------------------------------------------------------

enum class EventType
{
  None = 0,
  KeyPressed,
  KeyReleased,
  KeyTyped,
};

class Event
{
public:
  Event() = default;
  virtual ~Event() = default;

  virtual EventType GetEventType() const = 0;
  virtual const char* GetName() const = 0;
};

class KeyPressEvent : public Event
{
public:
  EventType m_EventType = EventType::KeyPressed;
  int m_Key;

public:
  KeyPressEvent(int key, int scancode, int action, int mods);
  ~KeyPressEvent() = default;

  EventType GetEventType() const;
  const char* GetName() const;
};

// Event handler ---------------------------------------------------------------

class Handler
{
public:
  EventType m_EventType;

public:
  Handler(EventType e);
  ~Handler() = default;

  EventType GetEventType()
  {
    return m_EventType;
  }
  void UnregisterHandler();

  virtual void Exec() = 0;
  virtual bool IsInterested(Event* e) const = 0;
};

class Bird;

class JumpHandler : public Handler
{
public:
  Bird* m_Bird;

  JumpHandler(Bird* bird);
  ~JumpHandler() = default;

  void Exec() override;
  bool IsInterested(Event* e) const override;
};

// EventDispatcher ----------------------------------------------------------------

struct EventTypeHash
{
  std::size_t operator()(EventType e) const { return static_cast<std::size_t>(e); }
};

class EventDispatcher
{
public:
  std::unordered_map<EventType, std::vector<Handler*>, EventTypeHash> m_Handlers;
  std::vector<Event*> m_Queue;
  uint64_t m_LastID;

public:
  EventDispatcher() = default;
  ~EventDispatcher() = default;

  void RegisterHandler(Handler* h);
  void UnregisterHandler(Handler* h);

  void Flush();

  uint64_t GetNextID();
  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
