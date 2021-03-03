#include "camera_controller.h"
#include "../core/input.h"
#include <glm/gtc/matrix_transform.hpp>

CameraController::CameraController(float fov, float aspect_ratio, float near,
                                   float far)
    : camera_(Camera(fov, aspect_ratio, far, near)),
      target_position_(0.0f),
      angle_(45.0f),
      height_(5.0f),
      zoom_speed_(20.0f) {}

void CameraController::Update(float dt) {
  if (InputManager::GetInstance()->GetKeyState(KeyCode::W) ==
      KeyState::Pressed) {
    target_position_.z -= camera_.speed * dt;
  }
  if (InputManager::GetInstance()->GetKeyState(KeyCode::S) ==
      KeyState::Pressed) {
    target_position_.z += camera_.speed * dt;
  }
  if (InputManager::GetInstance()->GetKeyState(KeyCode::A) ==
      KeyState::Pressed) {
    target_position_.x -= camera_.speed * dt;
  }
  if (InputManager::GetInstance()->GetKeyState(KeyCode::D) ==
      KeyState::Pressed) {
    target_position_.x += camera_.speed * dt;
  }

  // @TODO: Mouse scroll instead of keys
  if (InputManager::GetInstance()->GetKeyState(KeyCode::Q) ==
      KeyState::Pressed) {
    angle_ -= zoom_speed_ * dt;
    if (angle_ < 15.0f) {
      angle_ = 15.0f;
    }
  }
  if (InputManager::GetInstance()->GetKeyState(KeyCode::E) ==
      KeyState::Pressed) {
    angle_ += zoom_speed_ * dt;
    if (angle_ > 55.0f) {
      angle_ = 55.0f;
    }
  }
  // @TODO: Get rid of magic numbers
  height_ = (1.0 - (angle_ - 15.0) / (55.0f - 15.0f)) * 3.0f + 2.0f;

  glm::vec3 pos = glm::vec3(0.0f, 1.0f, 0.0f) * height_;
  glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(angle_),
                              glm::vec3(1.0f, 0.0f, 0.0f));
  pos = glm::vec3(rot * glm::vec4(pos, 1.0)) + target_position_;
  camera_.position = pos;
  camera_.front = glm::normalize(target_position_ - camera_.position);
}
