#include "txpch.hpp"

#include "CoreApp.hpp"

namespace Texturia {

#define BIND_EVENT_FN(x) std::bind(&CoreApp::x, this, std::placeholders::_1)

CoreApp::CoreApp() {
  Log::Init();
  TX_INFO("Initialized Logger");

  m_Window = std::unique_ptr<Window>(Window::Create());
  m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

CoreApp::~CoreApp() {}

void CoreApp::Run() {
  while (m_Running) {
    m_Window->OnUpdate();
  }
}

void CoreApp::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

  TX_TRACE("{0}", e);
}

bool CoreApp::OnWindowClose(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}

CoreApp *CreateCoreApp() { return new CoreApp; }

} // namespace Texturia
