#pragma once

#include "txpch.hpp"

#include "Events/AppEvent.hpp"
#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Layer.hpp"

namespace Texturia {

class ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach();
  void OnDetach();

  void OnUpdate();
  void OnEvent(Event &e);

private:
  bool OnMouseButtonDownEvent(MouseButtonDownEvent &e);
  bool OnMouseButtonUpEvent(MouseButtonUpEvent &e);
  bool OnKeyDownEvent(KeyDownEvent &e);
  bool OnKeyTypedEvent(KeyTypedEvent &e);
  bool OnKeyUpEvent(KeyUpEvent &e);
  bool OnMouseMovedEvent(MouseMovedEvent &e);
  bool OnMouseScrolledEvent(MouseScrolledEvent &e);
  bool OnWindowResizedEvent(WindowResizeEvent &e);
  bool OnWindowCloseEvent(WindowCloseEvent &e);

private:
  float m_Time = 0.0f;
};

} // namespace Texturia