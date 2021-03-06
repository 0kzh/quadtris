#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>

//Enums for all valid commands
enum Command {
  CMD_LEFT,
  CMD_RIGHT,
  CMD_DOWN,
  CMD_CLOCKWISE,
  CMD_COUNTERCLOCKWISE,
  CMD_DROP,
  CMD_LEVELUP,
  CMD_LEVELDOWN,
  CMD_NORANDOM,
  CMD_RANDOM,
  CMD_SEQUENCE,
  CMD_I,
  CMD_J,
  CMD_L,
  CMD_S,
  CMD_Z,
  CMD_O,
  CMD_T,
  CMD_RESTART,
  CMD_HINT,
  CMD_NOOP,
  CMD_QUIT
};

//Matches input strings to their command types
inline std::map<std::string, Command> inputToCommand = {
    {"left",             CMD_LEFT},
    {"right",            CMD_RIGHT},
    {"down",             CMD_DOWN},
    {"clockwise",        CMD_CLOCKWISE},
    {"counterclockwise", CMD_COUNTERCLOCKWISE},
    {"drop",             CMD_DROP},
    {"levelup",          CMD_LEVELUP},
    {"leveldown",        CMD_LEVELDOWN},
    {"norandom",         CMD_NORANDOM},
    {"random",           CMD_RANDOM},
    {"sequence",         CMD_SEQUENCE},
    {"I",                CMD_I},
    {"J",                CMD_J},
    {"L",                CMD_L},
    {"S",                CMD_S},
    {"Z",                CMD_Z},
    {"O",                CMD_O},
    {"T",                CMD_T},
    {"restart",          CMD_RESTART},
    {"hint",             CMD_HINT},
};

inline std::map<Command, BlockType> cmdToBlockType = {
    {CMD_I, I},
    {CMD_J, J},
    {CMD_L, L},
    {CMD_S, S},
    {CMD_Z, Z},
    {CMD_O, O},
    {CMD_T, T},
};

/**
 * Fuzzy matches on the string input based on prefix indexing.
 *
 * @param input the input string
 * @returns `Command` if found, `nullopt` otherwise
 */
inline std::optional<Command> matchCommand(const std::string &input) {
  std::vector<std::string> keys;
  keys.reserve(inputToCommand.size());

  for (auto &it : inputToCommand) {
    keys.push_back(it.first);
  }

  std::optional<Command> foundCommand = std::nullopt;
  for (auto &key : keys) {
    // rfind checks for prefix substring
    if (key.rfind(input, 0) == 0) {
      if (foundCommand) {
        return std::nullopt; // more than 1 matching command
      }
      foundCommand = inputToCommand[key];
    }
  }
  return foundCommand;
}

#endif
