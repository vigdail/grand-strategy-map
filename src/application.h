#pragma once

#include <memory>

#include "./game.h"
#include "core/window.h"
#include "./gui/gui_layer.h"

class Application {
 public:
  Application() : Application(1280, 720) {}
  Application(unsigned int width, unsigned int height);
  ~Application();
  void Run();

 private:
  std::shared_ptr<Window> window_;
  std::unique_ptr<Game> game_;
  unsigned int width_;
  unsigned int height_;

  // static void FramebufferSizeCallback(GLFWwindow *window, int width,
  //                                     int height);
  // static void MouseButtonCallback(GLFWwindow *window, int button, int action,
  //                                 int mode);
  // static void MouseCallback(GLFWwindow *window, double x, double y);
};
