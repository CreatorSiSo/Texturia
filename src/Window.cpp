#include "txpch.hpp"

#include "Window.hpp"

namespace Texturia {

static bool s_GLFWInitialized = false;

Window::Window(const WindowProps &props) { Init(props); }
Window::~Window() { Shutdown(); }

Window *Window::Create(const WindowProps &props) { return new Window(props); }

void Window::Init(const WindowProps &props) {
  m_Data.Title = props.Title;
  m_Data.Width = props.Width;
  m_Data.Height = props.Height;

  TX_INFO("Creating Window '{0}' ({1}, {2})", m_Data.Title, m_Data.Width,
          m_Data.Height);

  glfwSetErrorCallback(ErrorCallbackFunction);

  if (!s_GLFWInitialized) {
    // TODO: glfwTerminate on system shutdown
    int isInitialized = glfwInit();
    TX_ASSERT(isInitialized, "Could not intialize GLFW!");

    s_GLFWInitialized = true;
  }

  m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(),
                              nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);
  glfwSetWindowUserPointer(m_Window, &m_Data);
  SetVSync(true);
}

void Window::Shutdown() { glfwTerminate(); }

unsigned int Window::GetWidth() const { return m_Data.Width; }
unsigned int Window::GetHeight() const { return m_Data.Height; }

void Window::OnUpdate() {
  if (!glfwWindowShouldClose(m_Window)) {
    glfwMakeContextCurrent(m_Window);
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
  } else {
    glfwDestroyWindow(m_Window);
  }
}

void Window::SetVSync(bool use) {
  if (use)
    glfwSwapInterval(1);
  else
    glfwSwapInterval(0);

  m_Data.VSync = use;
}

bool Window::IsVSync() const { return m_Data.VSync; }

} // namespace Texturia
