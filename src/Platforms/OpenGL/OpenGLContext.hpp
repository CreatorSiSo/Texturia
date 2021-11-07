#pragma once

#include "txpch.hpp"

#include "Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace Texturia {

class OpenGLContext : public GraphicsContext {
public:
  OpenGLContext(GLFWwindow *windowHandle);

  virtual void Init() override;
  virtual void SwapBuffers() override;

private:
  GLFWwindow *m_WindowHandle;
};

} // namespace Texturia