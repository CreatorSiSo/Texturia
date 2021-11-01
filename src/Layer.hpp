#pragma once

#include "txpch.hpp"

#include "Events/Event.hpp"

namespace Texturia {

class Layer {
public:
  Layer(const std::string &debugName = "Layer");
  virtual ~Layer();

  virtual void OnAttach();
  virtual void OnDetach();
  virtual void OnUpdate();
  virtual void OnEvent(Event &e);

private:
  std::string m_DebugName;
};

} // namespace Texturia
