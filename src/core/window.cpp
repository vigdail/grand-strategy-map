#include <iostream>

#include <glad/glad.h>
#include "window.h"
#include "input.h"

Window::Window(int width, int height) noexcept
    : width_(width), height_(height) {
  InitOpenGL();
  CreateWindow();
  MoveToCenter();
  SetupCallbacks();
}

Window::~Window() { glfwTerminate(); }

void Window::SetTitle(std::string title) const {
  glfwSetWindowTitle(window_, title.c_str());
}

void Window::SwapBuffers() const { glfwSwapBuffers(window_); }

void Window::ShowCursor() {
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::HideCursor() {
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::ToggleCursor() {
  if (IsCursorHidden()) {
    ShowCursor();
  } else {
    HideCursor();
  }
}

bool Window::IsCursorHidden() const {
  return glfwGetInputMode(window_, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void InitOpenGL() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, false);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }
}

void Window::CreateWindow() {
  window_ = glfwCreateWindow(width_, height_, "", nullptr, nullptr);
  glfwMakeContextCurrent(window_);
}

void Window::MoveToCenter() {
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  if (monitor == NULL) {
    std::cerr << "Failed to get primary monitor" << std::endl;
    return;
  }

  int screenWidth, screeHeight;
  glfwGetMonitorWorkarea(monitor, NULL, NULL, &screenWidth, &screeHeight);
  glfwSetWindowPos(window_, (screenWidth - width_) / 2,
                   (screeHeight - height_) / 2);
}

void Window::SetupCallbacks() {
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

  glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x, double y) {
    InputManager::GetInstance()->OnMouseMoved(x, y);
  });

  glfwSetMouseButtonCallback(
      window_, [](GLFWwindow* window, int button, int action, int mode) {
        if (action == GLFW_PRESS) {
          InputManager::GetInstance()->OnMouseButtonPressed(
              static_cast<MouseButton>(button));
        } else if (action == GLFW_RELEASE) {
          InputManager::GetInstance()->OnMouseButtonReleased(
              static_cast<MouseButton>(button));
        }
      });
}
