#include "province.h"
#include <iomanip>

std::istringstream &operator>>(std::istringstream &ss, Color &color) {
  ss >> color.red >> color.green >> color.blue;
  return ss;
}

std::istringstream &operator>>(std::istringstream &ss, Province &province) {
  ss >> province.id;
  ss >> province.color >> std::quoted(province.name);
  return ss;
}
