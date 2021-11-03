#include "txpch.hpp"

//! Temporary
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "imgui.h"

#include "CoreApp.hpp"
#include "ImGuiLayer.hpp"
#include "Platforms/OpenGL/ImGuiOpenGL3Renderer.hpp"

namespace Texturia {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.BackendFlags = ImGuiBackendFlags_HasMouseCursors;
  io.BackendFlags = ImGuiBackendFlags_HasSetMousePos;

  // Temporary should eventually use internal key codes
  io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
  io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
  io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
  io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
  io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
  io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
  io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
  io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
  io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
  io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
  io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
  io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
  io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
  io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
  io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
  io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
  io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
  io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

  ImGui_ImplOpenGL3_Init("#version 410");

  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigDockingTransparentPayload = true;

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Needs io.BackendFlags & ImGuiBackendFlags_HasMouseCursors
  io.ConfigWindowsResizeFromEdges = true;

  ImFontConfig fontConfig;
  fontConfig.OversampleH = 1;
  fontConfig.OversampleH = 1;
  fontConfig.PixelSnapH = true;
  fontConfig.MergeMode = true;

  io.Fonts->AddFontFromFileTTF("./assets/fonts/Comfortaa/Comfortaa-Regular.ttf",
                               14.0f);

  ImGuiStyle &style = ImGui::GetStyle();
  // style.WindowPadding = ImVec2(8.00f, 8.00f);
  // style.FramePadding = ImVec2(5.00f, 2.00f);
  // style.CellPadding = ImVec2(6.00f, 6.00f);
  // style.ItemSpacing = ImVec2(6.00f, 6.00f);
  // style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
  // style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
  // style.IndentSpacing = 25;
  // style.ScrollbarSize = 15;
  // style.GrabMinSize = 10;
  // style.WindowBorderSize = 1;
  // style.ChildBorderSize = 1;
  // style.PopupBorderSize = 1;
  // style.FrameBorderSize = 1;
  // style.TabBorderSize = 1;
  style.WindowRounding = 5;
  style.ChildRounding = 3;
  style.FrameRounding = 3;
  style.PopupRounding = 3;
  style.ScrollbarRounding = 9;
  style.GrabRounding = 3;
  style.TabRounding = 3;

  ImVec4 *colors = ImGui::GetStyle().Colors;
  // colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  // colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  // colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  // colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  // colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  // colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
  // colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  // colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  // colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  // colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  // colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  // colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  // colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  // colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  // colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  // colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  // colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  // colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  // colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  // colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  // colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  // colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  // colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  // colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  // colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  // colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  // colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  // colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  // colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  // colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  // colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  // colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  // colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  // colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  // colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  // colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  // colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  // colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  // colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  // colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  // colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  // colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  // colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  // colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  // colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  // colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  // colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  // colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  // colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  // colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  // colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  // colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  // colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f,
  // 0.70f); colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f,
  // 0.20f); colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f,
  // 0.35f);
}

void ImGuiLayer::OnDetach() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate() {
  ImGuiIO &io = ImGui::GetIO();
  CoreApp &coreApp = CoreApp::GetCoreApp();
  io.DisplaySize =
      ImVec2(coreApp.GetWindow().GetWidth(), coreApp.GetWindow().GetHeight());

  float time = (float)glfwGetTime();
  io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  ImGui::BeginMainMenuBar();
  ImGui::MenuItem("File");
  ImGui::MenuItem("Edit");
  ImGui::MenuItem("View");
  ImGui::MenuItem("Help");

#ifdef TX_PLATFORM_WINDOWS
  ImGui::MenuItem("Windows");
#endif
#ifdef TX_PLATFORM_LINUX
  ImGui::MenuItem("Linux");
#endif
#ifdef TX_PLATFORM_MACOS
  ImGui::MenuItem("MacOS");
#endif

  ImGui::EndMainMenuBar();

  ImGui::ShowDemoWindow();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);

  dispatcher.Dispatch<KeyDownEvent>(
      TX_BIND_EVENT_FN(ImGuiLayer::OnKeyDownEvent));

  dispatcher.Dispatch<KeyTypedEvent>(
      TX_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

  dispatcher.Dispatch<KeyUpEvent>(TX_BIND_EVENT_FN(ImGuiLayer::OnKeyUpEvent));

  dispatcher.Dispatch<MouseButtonDownEvent>(
      TX_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonDownEvent));

  dispatcher.Dispatch<MouseButtonUpEvent>(
      TX_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonUpEvent));

  dispatcher.Dispatch<MouseMovedEvent>(
      TX_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));

  dispatcher.Dispatch<MouseScrolledEvent>(
      TX_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

  dispatcher.Dispatch<WindowResizeEvent>(
      TX_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));

  dispatcher.Dispatch<WindowCloseEvent>(
      TX_BIND_EVENT_FN(ImGuiLayer::OnWindowCloseEvent));
}

bool ImGuiLayer::OnKeyDownEvent(KeyDownEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[e.GetKeyCode()] = true;

  io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
  io.KeyCtrl =
      io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
  io.KeyShift =
      io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
  io.KeySuper =
      io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

  return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  unsigned int keycode = e.GetKeyCode();
  io.AddInputCharacter(keycode);
  return false;
}

bool ImGuiLayer::OnKeyUpEvent(KeyUpEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[e.GetKeyCode()] = false;
  return false;
}

bool ImGuiLayer::OnMouseButtonDownEvent(MouseButtonDownEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[e.GetMouseButton()] = true;
  return false;
}

bool ImGuiLayer::OnMouseButtonUpEvent(MouseButtonUpEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseDown[e.GetMouseButton()] = false;
  return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MousePos = ImVec2(e.GetX(), e.GetY());
  return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.MouseWheel += e.GetOffsetY();
  io.MouseWheelH += e.GetOffsetX();
  return false;
}

bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  io.DisplaySize = ImVec2(e.GetWidth(), e.GetWidth());
  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
  //! Temporary
  glViewport(0, 0, e.GetWidth(), e.GetWidth());
  return false;
}

bool ImGuiLayer::OnWindowCloseEvent(WindowCloseEvent &e) {
  ImGuiIO &io = ImGui::GetIO();
  return false;
}

} // namespace Texturia
