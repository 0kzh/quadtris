
#ifndef GAME_H_
#define GAME_H_

#include "grid/grid.h"
#include "view/View.h"
#include "util/command.h"
#include <memory>
#include <string>

using namespace std;

class Game {
  int score_;
  int hiScore_;
  shared_ptr<Grid> grid_;
  vector<shared_ptr<View>> views_;
  // unique_ptr<Random> random_;
  // BlockType[] blockSequence_;

  bool textOnly_;
  string scriptFile_;

  int curLevelIdx_;
  // Level[] levelSequence_;

  const int EXTRA_ROWS = 3;

public:
  Game(bool textOnly, int seed, string scriptFile, int initialLevel);

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
  void gameLoop();

  static std::pair<int, Command> readCommand();

  void processCommand(int multiplier, Command c);

  int calculateScore(int linesCleared) const;
};

#endif