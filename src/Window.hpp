#pragma once

#include "txpch.hpp"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Events/AppEvent.hpp"
#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

namespace Texturia {

struct WindowProps {
  std::string Title;
  int Width;
  int Height;

  WindowProps(const std::string &title = "Texturia", unsigned int width = 1600,
              unsigned int height = 900)
      : Title(title), Width(width), Height(height) {}
};

void ErrorCallbackFunction(int error, const char *description) {
  TX_ERROR("{0} {1}", error, (std::string)description);
}

class Window {
public:
  Window(const WindowProps &props);
  ~Window();

  static Window *Create(const WindowProps &props = WindowProps());

  void OnUpdate();

  unsigned int GetWidth() const;
  unsigned int GetHeight() const;

  using EventCallbackFunction = std::function<void(Event &)>;

  // Window attributes
  void SetEventCallback(const EventCallbackFunction &callback);
  void SetVSync(bool enabled);
  bool IsVSync() const;

private:
  GLFWwindow *m_Window;

  void Init(const WindowProps &props);
  void Shutdown();

  void OnEvent(Event &e);
  bool OnWindowClose(WindowCloseEvent &e);

  struct WindowData {
    std::string Title;
    unsigned int Width, Height;
    bool VSync;

    EventCallbackFunction EventCallback;
  };

  WindowData m_Data;
};

} // namespace Texturia