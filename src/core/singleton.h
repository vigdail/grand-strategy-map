#pragma once

#include <memory>

template <class T>
class Singleton {
 public:
  static T* GetInstance() {
    if (!instance_) {
      instance_ = new T();
    }
    return instance_;
  }

  static void DestroyInstance() {
    if (instance_) {
      delete instance_;
    }
  }

 private:
  static T* instance_;
};

template <class T>
T* Singleton<T>::instance_ = nullptr;
