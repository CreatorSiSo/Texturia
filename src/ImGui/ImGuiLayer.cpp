#include "txpch.hpp"

//! Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "imgui.h"

#include "CoreApp.hpp"
#include "ImGuiLayer.hpp"
#include "Platforms/OpenGL/ImGuiOpenGL3Renderer.hpp"

namespace Texturia {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

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
}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate() {
  ImGuiIO &io = ImGui::GetIO();
  CoreApp &coreApp = CoreApp::GetCoreApp();
  io.DisplaySize =
      ImVec2(coreApp.GetWindow().GetWidth(), coreApp.GetWindow().GetHeight());

  float time = (float)glfwGetTime();
  io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();

  static bool showDemoWindow = true;
  ImGui::ShowDemoWindow(&showDemoWindow);

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
