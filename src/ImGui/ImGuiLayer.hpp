#pragma once

#include "txpch.hpp"

#include "Layer.hpp"

namespace Texturia {

class ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnImGuiRender() override;

  void Begin();
  void End();

private:
  float m_Time = 0.0f;
};

} // namespace Texturia