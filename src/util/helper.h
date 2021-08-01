#ifndef HELPER_H
#define HELPER_H

#include <string>

class Helper {

public:
  static std::pair<int, std::string> splitMultipliedInput(const std::string &);

  static int generateUniqueId();

  static std::string generateCenterJustifiedString(std::string a, std::string b, int width);
};

#endif
