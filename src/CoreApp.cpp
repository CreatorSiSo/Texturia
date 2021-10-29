#include "txpch.hpp"

#include <GLFW/glfw3.h>

#include "CoreApp.hpp"
#include "Events/AppEvent.hpp"

Texturia::CoreApp::CoreApp() {}

Texturia::CoreApp::~CoreApp() {}

void Texturia::CoreApp::Run() {
  struct WindowProps {
    std::string Title;
    int Width;
    int Height;

    WindowProps(const std::string &title = "Texturia",
                unsigned int width = 1600, unsigned int height = 900)
        : Title(title), Width(width), Height(height) {}
  };

  Texturia::Log::Init();
  TX_INFO("Initialized Logger");

  TX_WARN("Hello World");

  WindowResizeEvent e(1280, 720);
  TX_TRACE(e);

  WindowProps props;

  TX_INFO("Creating Window {0} ({1} {2})", props.Title, props.Width,
          props.Height);

  GLFWwindow *window;

  bool GLFWInitialized = false;
  if (!GLFWInitialized) {
    // TODO glfwTerminate() on system shutdown
    int success = glfwInit();
    TX_ASSERT(success, "Could not initialize glfw!");

    GLFWInitialized = true;
  }

  window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(),
                            NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  // glfwSetWindowUserPointer(window, NULL);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
}

Texturia::CoreApp *Texturia::CreateCoreApp() { return new CoreApp; }
