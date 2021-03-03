#include <iostream>

#include <glad/glad.h>
#include "window.h"
#include "input.h"

Window::Window(int width, int height) : width_(width), height_(height) {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, false);

  window_ = glfwCreateWindow(width, height, "OpenGL Grand Strategy Map",
                             nullptr, nullptr);
  glfwMakeContextCurrent(window_);
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  if (monitor == NULL) {
    std::cerr << "Failed to get primary monitor" << std::endl;
    glfwTerminate();
  }

  int screenWidth, screeHeight;
  glfwGetMonitorWorkarea(monitor, NULL, NULL, &screenWidth, &screeHeight);
  glfwSetWindowPos(window_, (screenWidth - width) / 2,
                   (screeHeight - height) / 2);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glfwSetWindowUserPointer(window_, this);

  glfwSetKeyCallback(
      window_, [](GLFWwindow* const window, int const key, int const scancode,
                  int const action, int const mods) {
        if (static_cast<KeyCode>(key) == KeyCode::ESCAPE) {
          glfwSetWindowShouldClose(window, true);
        }
        if (action == GLFW_PRESS) {
          InputManager::GetInstance()->OnKeyPressed(static_cast<KeyCode>(key));
        } else if (action == GLFW_RELEASE) {
          InputManager::GetInstance()->OnKeyReleased(static_cast<KeyCode>(key));
        }
      });

  glfwSetFramebufferSizeCallback(window_,
                                 [](GLFWwindow* window, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });
  // glfwSetCursorPosCallback(window_, MouseCallback);
  // glfwSetMouseButtonCallback(window_, MouseButtonCallback);
}

Window::~Window() { glfwTerminate(); }

void Window::SetTitle(std::string title) const {
  glfwSetWindowTitle(window_, title.c_str());
}

void Window::SwapBuffers() const { glfwSwapBuffers(window_); }
