#include "txpch.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "OpenGLContext.hpp"

namespace Texturia {
OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
    : m_WindowHandle(windowHandle) {
  TX_ASSERT(windowHandle, "Window Handle is NULL!")
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(m_WindowHandle);

  int gladInitialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  TX_ASSERT(gladInitialized, "Failed to intialize GLAD!")
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

} // namespace Texturia