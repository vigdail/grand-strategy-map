#include "application.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

void DebugMessageCallback(unsigned source, unsigned type, unsigned id,
                          unsigned severity, int length, const char *message,
                          const void *userParam) {
  std::cerr << message << std::endl;
}

Application::Application(unsigned int width, unsigned int height)
    : window_(std::make_shared<Window>(width, height)),
      width_(width),
      height_(height) {
#ifndef NDEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(DebugMessageCallback, nullptr);

  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                        GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  game_ = std::make_unique<Game>(width, height);
}

Application::~Application() {
  InputManager::DestroyInstance();
  glfwTerminate();
}

void Application::Run() {
  float last_time = 0.0f;
  while (!window_->ShouldClose()) {
    float current_time = glfwGetTime();
    float delta_time = current_time - last_time;
    last_time = current_time;

    int fps = floor(1.0f / delta_time);
    std::string title = "OpenGL | " + std::to_string(fps);
    window_->SetTitle(title);

    glfwPollEvents();

    game_->Update(delta_time);

    game_->Render();

    window_->SwapBuffers();
  }
}

// void Application::MouseCallback(GLFWwindow *window, double x, double y) {
//   auto self = static_cast<Application *>(glfwGetWindowUserPointer(window));
//   self->game_->OnMousePositionEvent(x, y);
// }

// void Application::MouseButtonCallback(GLFWwindow *window, int button,
//                                       int action, int mode) {
//   auto self = static_cast<Application *>(glfwGetWindowUserPointer(window));
//   self->game_->OnMouseButtonEvent(button, action, mode);
// }
