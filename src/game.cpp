#include "game.h"
#include "application.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const uint Game::kKeysCount_;

Game::Game(uint width, uint height)
    : width_(width),
      height_(height),
      keys_(),
      camera_(Camera(60.0f, 1.0f * width_ / height_, 0.1f, 1000.0f)),
      light_(DirectionalLight(glm::vec3(0.0f), glm::vec3(0.0f))),
      mouse_last_x_(0.0),
      mouse_last_y_(0.0) {
  LoadAssets();
  camera_.position = glm::vec3(0.0f, 3.0f, 0.0f);

  gui_ = std::make_unique<GUILayer>(width, height);
}

void Game::LoadAssets() {
  ResourceManager::LoadShader("solid", "../assets/shaders/solid_color.vs",
                              "../assets/shaders/solid_color.fs");
  ResourceManager::LoadShader("sprite", "../assets/shaders/sprite.vs",
                              "../assets/shaders/sprite.fs");

  ResourceManager::LoadTexture("regions", "../assets/textures/regions.bmp");

  LoadMap();
}

void Game::LoadMap() {
  std::ifstream file;
  file.open("../assets/data/provinces.txt");
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') {
      continue;
    }
    Province province;
    std::istringstream ss(line);
    ss >> province;

    provinces_[province.id] = province;
  }
  file.close();
}

void Game::ProcessInput(float dt) {
  if (keys_[GLFW_KEY_W]) {
    camera_.move(CameraMovement::FORWARD, dt);
  }
  if (keys_[GLFW_KEY_S]) {
    camera_.move(CameraMovement::BACKWARD, dt);
  }
  if (keys_[GLFW_KEY_A]) {
    camera_.move(CameraMovement::LEFT, dt);
  }
  if (keys_[GLFW_KEY_D]) {
    camera_.move(CameraMovement::RIGHT, dt);
  }
}

void Game::Update(float dt) {
  // camera_.position.y =
  gui_->Update(dt);
}

void Game::Render() {
  // Main pass
  glDisable(GL_CLIP_DISTANCE0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, width_, height_);
  RenderScene(glm::vec4(0.0f));

  gui_->Render();
}

void Game::RenderScene(glm::vec4 clip_plane) {
  //
}

void Game::OnKeyEvent(int key, int scancode, int action, int mode) {
  gui_->OnKeyEvent(key, scancode, action, mode);

  if (action == GLFW_PRESS) {
    SetKeyPressed(key);
  } else if (action == GLFW_RELEASE) {
    SetKeyReleased(key);
  }
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    camera_.Toggle();
  }
}

void Game::OnMouseButtonEvent(int button, int action, int mode) {
  gui_->OnMouseButtonEvent(button, action, mode);
}

void Game::OnMousePositionEvent(double x, double y) {
  float offsetX = x - mouse_last_x_;
  float offsetY = mouse_last_y_ - y;

  mouse_last_x_ = x;
  mouse_last_y_ = y;

  camera_.handleMouseMovement(offsetX, offsetY);

  gui_->OnMousePositionEvent(x, y);
}

void Game::SetKeyPressed(uint key) {
  if (key < kKeysCount_) {
    keys_[key] = true;
  }
}

void Game::SetKeyReleased(uint key) {
  if (key < kKeysCount_) {
    keys_[key] = false;
  }
}

bool Game::IsKeyPressed(uint key) {
  if (key < kKeysCount_) {
    return keys_[key];
  }

  return false;
}
