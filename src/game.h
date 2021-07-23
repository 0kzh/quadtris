
#ifndef GAME_H_
#define GAME_H_

#include "grid/grid.h"
#include "view/View.h"
#include <memory>
#include <string>

using namespace std;

class Game {
  int score_;
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
  Game(bool textOnly, string seed, string scriptFile, int initialLevel);

  void start();

  void update();
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

  void readCommand();
  //  { grid_->draw(); }
};

#endif