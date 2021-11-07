#include "framio/framio.hpp"

#include <imgui.h>

class GuiLayer : public Framio::Layer {
public:
  void OnImGuiRender() {
    ImGui::DockSpaceOverViewport();

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        ImGui::MenuItem("1");
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Edit")) {
        ImGui::MenuItem("1");
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("View")) {
        ImGui::MenuItem("1");
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Help")) {
        ImGui::MenuItem("1");
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Platform")) {
#ifdef TX_PLATFORM_WINDOWS
        ImGui::MenuItem("Windows");
#endif
#ifdef TX_PLATFORM_LINUX
        ImGui::MenuItem("Linux");
#endif
#ifdef TX_PLATFORM_MACOS
        ImGui::MenuItem("MacOS");
#endif
        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }

    ImGui::ShowDemoWindow();
  }

  void OnEvent(Framio::Event &event) override {
    if (event.GetEventType() == Framio::EventType::KeyTyped) {
      Framio::KeyTypedEvent &e = (Framio::KeyTypedEvent &)event;
      FR_TRACE((char)e.GetKeyCode());
    }
  }
};

class TexturiaApp : public Framio::App {
public:
  TexturiaApp() { PushOverlay(new GuiLayer()); }
  ~TexturiaApp() {}
};

Framio::App *Framio::CreateApp() { return new TexturiaApp(); }
