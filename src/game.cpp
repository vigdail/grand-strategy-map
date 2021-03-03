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
      camera_(CameraController(60.0f, 1.0f * width_ / height_, 0.1f, 1000.0f)),
      light_(DirectionalLight(glm::vec3(0.0f), glm::vec3(0.0f))),
      mouse_last_x_(0.0),
      mouse_last_y_(0.0) {
  LoadAssets();

  map_quad_ = std::make_unique<Quad>(10.0f);
  sphere_ = std::make_unique<Sphere>(16.0f, 16.0f, 20.0f);

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

void Game::Update(float dt) {
  camera_.Update(dt);
  gui_->Update(dt);
}

void Game::Render() {
  // Main pass
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  RenderScene(glm::vec4(0.0f));

  gui_->Render();
}

void Game::RenderScene(glm::vec4 clip_plane) {
  const Texture& regions_texture = ResourceManager::GetTexture("regions");
  regions_texture.Bind();
  Shader& sprite_shader = ResourceManager::GetShader("sprite");
  sprite_shader.Use();
  sprite_shader.SetMat4("model", glm::mat4(1.0f));
  sprite_shader.SetMat4("view", camera_.GetCamera().getViewMatrix());
  sprite_shader.SetMat4("projection",
                        camera_.GetCamera().getProjectionMatrix());
  map_quad_->Draw();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glCullFace(GL_FRONT);
  Shader& solid_shader = ResourceManager::GetShader("solid");
  solid_shader.Use();
  solid_shader.SetMat4("model", glm::mat4(1.0f));
  solid_shader.SetMat4("view", camera_.GetCamera().getViewMatrix());
  solid_shader.SetMat4("projection", camera_.GetCamera().getProjectionMatrix());
  sphere_->Draw();
  glCullFace(GL_BACK);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Game::OnKeyEvent(int key, int scancode, int action, int mode) {
  gui_->OnKeyEvent(key, scancode, action, mode);

  // if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
  //   camera_.GetCamera().Toggle();
  // }
}

void Game::OnMouseButtonEvent(int button, int action, int mode) {
  gui_->OnMouseButtonEvent(button, action, mode);
}

void Game::OnMousePositionEvent(double x, double y) {
  // float offsetX = x - mouse_last_x_;
  // float offsetY = mouse_last_y_ - y;

  // mouse_last_x_ = x;
  // mouse_last_y_ = y;

  // camera_.GetCamera().HandleMouseMovement(offsetX, offsetY);

  gui_->OnMousePositionEvent(x, y);
}
