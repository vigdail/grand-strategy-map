#pragma once

#include <unordered_map>

#include <glm/glm.hpp>

#include "keycodes.h"
#include "singleton.h"

enum class KeyState {
  Released,
  Up,
  Down,
  Pressed,
};

class InputManager : public Singleton<InputManager> {
 public:
  InputManager()
      : key_states_(),
        mouse_button_states_(),
        mouse_position_(glm::vec2(0.0f)) {}
  virtual ~InputManager() = default;

  void Update();
  KeyState GetKeyState(KeyCode key) const;
  KeyState GetMouseButtonState(MouseButton button) const;
  glm::vec2 GetMousePosition() const;
  void OnKeyPressed(KeyCode key);
  void OnKeyReleased(KeyCode key);
  void OnMouseMoved(float x, float y);
  void OnMouseButtonPressed(MouseButton button);
  void OnMouseButtonReleased(MouseButton button);

 private:
  std::unordered_map<KeyCode, KeyState> key_states_;
  std::unordered_map<MouseButton, KeyState> mouse_button_states_;
  glm::vec2 mouse_position_;

 private:
  void CycleKeyState(KeyState &state);
};
