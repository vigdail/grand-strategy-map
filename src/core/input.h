#pragma once

#include <unordered_map>

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
  InputManager() : key_states_() {}
  virtual ~InputManager() = default;

  void Update();
  KeyState GetKeyState(KeyCode key) const;
  void OnKeyPressed(KeyCode key);
  void OnKeyReleased(KeyCode key);

 private:
  std::unordered_map<KeyCode, KeyState> key_states_;

 private:
  void CycleKeyState(KeyState &state);
};
