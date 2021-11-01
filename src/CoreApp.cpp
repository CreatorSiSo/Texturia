#include "txpch.hpp"

#include "CoreApp.hpp"
#include "ImGui/ImGuiLayer.hpp"

namespace Texturia {

#define BIND_EVENT_FN(x) std::bind(&CoreApp::x, this, std::placeholders::_1)

CoreApp *CoreApp::s_Instance = nullptr;

CoreApp::CoreApp() {
  TX_ASSERT(!s_Instance, "CoreApp already exists!");
  s_Instance = this;

  Log::Init();
  TX_INFO("Initialized Logger");

  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

  PushOverlay(new ImGuiLayer());
}

CoreApp::~CoreApp() {}

void CoreApp::Run() {
  while (m_Running) {
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
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

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
