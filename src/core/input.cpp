#include "input.h"

void InputManager::Update() {
  for (auto& key : key_states_) {
    CycleKeyState(key.second);
  }
  for (auto& button : mouse_button_states_) {
    CycleKeyState(button.second);
  }
}

KeyState InputManager::GetKeyState(KeyCode key) const {
  auto it = key_states_.find(key);
  if (it != key_states_.cend()) {
    return it->second;
  }

  return KeyState::Up;
}

KeyState InputManager::GetMouseButtonState(MouseButton button) const {
  auto it = mouse_button_states_.find(button);
  if (it != mouse_button_states_.cend()) {
    return it->second;
  }

  return KeyState::Up;
}

glm::vec2 InputManager::GetMousePosition() const { return mouse_position_; }

void InputManager::OnKeyPressed(KeyCode key) {
  key_states_[key] = KeyState::Pressed;
}

void InputManager::OnKeyReleased(KeyCode key) {
  key_states_[key] = KeyState::Released;
}

void InputManager::OnMouseMoved(float x, float y) {
  mouse_position_.x = x;
  mouse_position_.y = y;
}

void InputManager::OnMouseButtonPressed(MouseButton button) {
  mouse_button_states_[button] = KeyState::Pressed;
}

void InputManager::OnMouseButtonReleased(MouseButton button) {
  mouse_button_states_[button] = KeyState::Released;
}

void InputManager::CycleKeyState(KeyState& state) {
  if (state == KeyState::Pressed) {
    state = KeyState::Down;
  } else if (state == KeyState::Released) {
    state = KeyState::Up;
  }
}
