#pragma once

#include "txpch.hpp"

#include "Events/AppEvent.hpp"
#include "Events/Event.hpp"
#include "ImGui/ImGuiLayer.hpp"
#include "LayerStack.hpp"
#include "Window.hpp"

namespace Texturia {

class CoreApp {
public:
  CoreApp();
  ~CoreApp();

  void Run();

  void OnEvent(Event &e);

  void PushLayer(Layer *layer);
  void PushOverlay(Layer *overlay);

  inline static CoreApp &GetCoreApp() { return *s_Instance; }
  inline Window &GetWindow() { return *m_Window; }

private:
  bool OnWindowClose(WindowCloseEvent &e);

  static CoreApp *s_Instance;
  std::unique_ptr<Window> m_Window;

  LayerStack m_LayerStack;
  ImGuiLayer *m_ImGuiLayer;

  bool m_Running = true;
};

CoreApp *CreateCoreApp();

} // namespace Texturia
