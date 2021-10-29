#include "txpch.hpp"

#include "CoreApp.hpp"
#include "Events/AppEvent.hpp"

Texturia::CoreApp::CoreApp() {}

Texturia::CoreApp::~CoreApp() {}

void Texturia::CoreApp::Run() {
  Texturia::Log::Init();
  TX_INFO("Initialized Logger");

  TX_WARN("Hello World");

  WindowResizeEvent e(1280, 720);
  TX_TRACE(e);

  while (true) {
  }
}

Texturia::CoreApp *Texturia::CreateCoreApp() { return new CoreApp; }
