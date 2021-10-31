#pragma once

#include "txpch.hpp"

namespace Texturia {

class Layer {
public:
  Layer(const std::string &debugName = "Layer");
  virtual ~Layer();

  virtual void OnAttach();
  virtual void OnDetach();
  virtual void OnUpdate();
  virtual void OnEvent();

private:
  std::string m_DebugName;
};

} // namespace Texturia
