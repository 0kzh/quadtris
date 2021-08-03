#include "helper.h"
#include <cassert>
#include <atomic>

using namespace std;

/**
 * Splits input strings into a multiplier and a command string
 *
 * @param input the input string
 * @returns a pair with the multiplier as an int, and the rest of the input string
 * as the command string. the mulitplier defaults as 1 if not explicitly given.
 */
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

/**
 * Generates a unique ID for each block created for scoring purposes.
 * 
 * @return uid the unique ID 
 */
int Helper::generateUniqueId() {
  static atomic<uint32_t> uid{0};
  return ++uid;
}

/**
 * Generates a center justified string from two input strings
 * for text display by inserting whitespaces between them.
 * 
 * @param a the first string
 * @param b the second string
 * @param width the desired string width
 * @return the string containing a and b separated by enough white
 * spaces to center justify them according to the width
 */
string Helper::generateCenterJustifiedString(string a, string b, int width) {
  int remWidth = width - a.length() - b.length();
  assert(remWidth >= 0);

  return a + string(remWidth, ' ') + b;
}
