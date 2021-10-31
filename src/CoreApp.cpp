#include "txpch.hpp"

#include "CoreApp.hpp"
#include "Events/AppEvent.hpp"
#include "Window.hpp"

Texturia::CoreApp::CoreApp() {}

Texturia::CoreApp::~CoreApp() {}

void Texturia::CoreApp::Run() {
  Log::Init();
  TX_INFO("Initialized Logger");

  auto test1 = Window::Create();
  auto test2 = Window::Create();
  while (m_Running) {
    test1->OnUpdate();
    test2->OnUpdate();
  }
  delete test1;
  delete test2;
}

Texturia::CoreApp *Texturia::CreateCoreApp() { return new CoreApp; }

  WindowProps props;

  TX_INFO("Creating Window '{0}' ({1}, {2})", props.Title, props.Width,
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
