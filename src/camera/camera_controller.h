#pragma once

#include "camera.h"
#include "../core/input.h"

class CameraController {
 public:
  CameraController(float fov, float aspect_ratio, float near, float far);
  Camera& GetCamera() { return camera_; }
  const Camera& GetCamera() const { return camera_; }
  void Update(float dt);

 private:
  Camera camera_;
  glm::vec3 target_position_;
  float angle_;
  float height_;
  float zoom_speed_;
};
