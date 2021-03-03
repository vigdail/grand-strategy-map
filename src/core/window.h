#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
 public:
  Window(int width, int height);
  ~Window();
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  GLFWwindow* GetRawWindow() const { return window_; }
  void SetTitle(std::string title) const;
  void SwapBuffers() const;
  bool ShouldClose() const { return glfwWindowShouldClose(window_); }

 private:
  GLFWwindow* window_;
  int width_;
  int height_;
};
