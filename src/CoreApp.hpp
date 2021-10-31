#pragma once

#include "txpch.hpp"

#include "Events/AppEvent.hpp"
#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Window.hpp"

namespace Texturia {

class CoreApp {
public:
  CoreApp();
  ~CoreApp();

  void Run();

  void OnEvent(Event &e);

private:
  bool OnWindowClose(WindowCloseEvent &e);

  std::unique_ptr<Window> m_Window;
  bool m_Running = true;
};

CoreApp *CreateCoreApp();

} // namespace Texturia
