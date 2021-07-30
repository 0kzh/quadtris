#ifndef HELPER_H
#define HELPER_H

#include <string>

class Helper {

public:
  static std::pair<int, std::string> splitMultipliedInput(const std::string &);

  static int generateUniqueId();
};

#endif
