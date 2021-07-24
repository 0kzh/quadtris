#include "helper.h"

using namespace std;

pair<int, string> splitMultipliedInput(const string &input) {
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
