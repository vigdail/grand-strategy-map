#pragma once

#include <string>
#include <sstream>

struct Color {
  int red;
  int green;
  int blue;
};

struct Province {
  int id;
  Color color;
  std::string name;
};

std::istringstream &operator>>(std::istringstream &ss, Color &color);
std::istringstream &operator>>(std::istringstream &ss, Province &province);
