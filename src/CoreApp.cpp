#include "txpch.hpp"

//! TODO Temprorary
#include <glad/glad.h>

#include "CoreApp.hpp"
#include "ImGui/ImGuiLayer.hpp"
#include "Input/Input.hpp"

namespace Texturia {

CoreApp *CoreApp::s_Instance = nullptr;

CoreApp::CoreApp() {
  Log::Init();
  TX_INFO("Initialized Logger");

  TX_ASSERT(!s_Instance, "CoreApp already exists!");
  s_Instance = this;

  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(TX_BIND_EVENT_FN(CoreApp::OnEvent));

  PushOverlay(new ImGuiLayer());
}

CoreApp::~CoreApp() {}

void CoreApp::Run() {
  while (m_Running) {
    auto [x, y] = Input::GetMousePos();
    TX_TRACE("{0}, {1}", x, y);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (Layer *layer : m_LayerStack)
      layer->OnUpdate();

    m_Window->OnUpdate();
  }
}

void CoreApp::PushLayer(Layer *layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void CoreApp::PushOverlay(Layer *overlay) {
  m_LayerStack.PushOverlay(overlay);
  overlay->OnAttach();
}

void CoreApp::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(
      TX_BIND_EVENT_FN(CoreApp::OnWindowClose));

  TX_TRACE("{0}", e);

  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    (*--it)->OnEvent(e);
    if (e.Handled)
      break;
  }
}

bool CoreApp::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

CoreApp *CreateCoreApp() { return new CoreApp; }

} // namespace Texturia
