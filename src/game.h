
#ifndef GAME_H_
#define GAME_H_

#include "grid/grid.h"
#include "view/View.h"
#include "util/command.h"
#include "levels/level.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Game {
  int score_;
  int hiScore_;
  shared_ptr<Grid> grid_;
  vector<shared_ptr<View>> views_;
  // unique_ptr<Random> random_;
  // BlockType[] blockSequence_;

  bool textOnly_;
  bool readFromFile_;
  string scriptFile_;

  vector<shared_ptr<Level>> levelSequence_;

  const int EXTRA_ROWS = 3;

  ifstream fileInp;

public:
  static int curLevelIdx_;

  Game(bool textOnly, int seed, string scriptFile);

  void start();

  void reset();
  // {
  //   textOnly_ = textOnly;
  //   scriptFile_ = scriptFile;
  //   grid_ = make_unique<Grid>(new Grid(11, 15 + EXTRA_ROWS));
  //   random_ = make_unique<Random>(new Random(seed));

  //   curLevelIdx_ = initialLevel;
  //   blockSequence = [];
  //   levelSequence = [make_unique<Level>

  //   ];
  // }
private:
  void initializeLevels();

  void gameLoop();

  static std::pair<int, Command> readCommand();

  void processCommand(int multiplier, Command c);

  void addBlockIfNone(const std::shared_ptr<Grid> &g);

  void moveDown();
};

#endif