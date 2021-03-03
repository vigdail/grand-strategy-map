#include "input.h"

void InputManager::Update() {
  for (auto& key : key_states_) {
    CycleKeyState(key.second);
  }
}

KeyState InputManager::GetKeyState(KeyCode key) const {
  auto it = key_states_.find(key);
  if (it != key_states_.cend()) {
    return it->second;
  }

  return KeyState::Up;
}

void InputManager::OnKeyPressed(KeyCode key) {
  key_states_[key] = KeyState::Pressed;
}

void InputManager::OnKeyReleased(KeyCode key) {
  key_states_[key] = KeyState::Released;
}

void InputManager::CycleKeyState(KeyState& state) {
  if (state == KeyState::Pressed) {
    state = KeyState::Down;
  } else if (state == KeyState::Released) {
    state = KeyState::Up;
  }
}
