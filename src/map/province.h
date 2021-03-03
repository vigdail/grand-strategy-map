#pragma once

#include <string>
#include <sstream>

struct Color {
  int red = 0;
  int green = 0;
  int blue = 0;
};

struct Province {
  int id = -1;
  Color color;
  std::string name;
};

std::istringstream &operator>>(std::istringstream &ss, Color &color);
std::istringstream &operator>>(std::istringstream &ss, Province &province);
