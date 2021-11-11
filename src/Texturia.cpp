#include "frameio/frameio.hpp"

#include <imgui.h>

class GuiLayer : public Frameio::Layer {
public:
  void OnImGuiRender() override {
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

  void OnEvent(Frameio::Event &event) override {
    if (event.GetEventType() == Frameio::EventType::KeyTyped) {
      Frameio::KeyTypedEvent &e = (Frameio::KeyTypedEvent &)event;
      FR_TRACE((char)e.GetKeyCode());
    }
  }
};

class TexturiaApp : public Frameio::App {
public:
  TexturiaApp() { PushOverlay(new GuiLayer()); }
  ~TexturiaApp() = default;
};

Frameio::App *Frameio::CreateApp() { return new TexturiaApp(); }
