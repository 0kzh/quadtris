#include "helper.h"
#include <cassert>
#inlcude <atomic>

using namespace std;

pair<int, string> Helper::splitMultipliedInput(const string &input) {
  string digStr;
  string command;
  bool parsingCommand = false;

  for (auto &c : input) {
    if (isdigit(c) && !parsingCommand) {
      digStr += c;
    } else {
      parsingCommand = true;
      command += c;
    }
  }

  return make_pair(digStr == "" ? 1 : stoi(digStr), command);
}

int Helper::generateUniqueId() {
  static atomic<uint32_t> uid{0};
  return ++uid;
}

string Helper::generateCenterJustifiedString(string a, string b, int width) {
  int remWidth = width - a.length() - b.length();
  assert(remWidth >= 0);

  return a + string(remWidth, ' ') + b;
}
