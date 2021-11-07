#pragma once

#include "txpch.hpp"

namespace Texturia {

class GraphicsContext {
public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;

private:
};

} // namespace Texturia