#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
 public:
  Shader() noexcept;
  Shader(const Shader &) = delete;
  Shader(Shader &&other) noexcept;
  Shader &operator=(const Shader &) = delete;
  Shader &operator=(Shader &&other);
  ~Shader();
  void Use();
  void AttachShader(const unsigned int type, const char *source);
  void Link();
  void SetInt(const char *name, const int value);
  void SetFloat(const char *name, const float value);
  void SetVec3(const char *name, const glm::vec3 &value);
  void SetVec4(const char *name, const glm::vec4 &value);
  void SetMat4(const char *name, const glm::mat4 &value);

 private:
  unsigned int ID_;
  void CheckCompileErrors(uint object, const unsigned int type);
  void Delete();
};
