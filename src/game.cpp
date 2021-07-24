#include "game.h"
#include "view/TextView.h"
#include "util/command.h"
#include <iostream>

using namespace std;

Game::Game(bool textOnly, int seed, string scriptFile, int initialLevel)
    : textOnly_(textOnly), scriptFile_(scriptFile), curLevelIdx_(initialLevel) {
  views_.push_back(make_shared<TextView>(TextView()));
  grid_ = make_shared<Grid>(Grid(15 + EXTRA_ROWS, 11));
}

void Game::start() {
  while (true) {
    gameLoop();
  }
}

void Game::gameLoop() {
  for (auto &v : views_) {
    if (!grid_->fallingBlock()) {
      grid_->setFallingBlock(Block{T, false});
    }
    readCommand();
    v->draw(grid_);
  }
}

void Game::readCommand() {
  string input;
  do {
    getline(cin, input);
  } while (inputToCommand.find(input) == inputToCommand.end());

  Command cmd = inputToCommand[input];

  switch (cmd) {
    case CMD_LEFT:
      if (grid_->fallingBlock()) {
        grid_->fallingBlock()->move(LEFT, grid_->grid());
      }
      break;
    case CMD_RIGHT:
      if (grid_->fallingBlock()) {
        grid_->fallingBlock()->move(RIGHT, grid_->grid());
      }
      break;
    case CMD_DOWN:
      if (grid_->fallingBlock()) {
        grid_->fallingBlock()->move(DOWN, grid_->grid());
      }
      break;
    case CMD_CLOCKWISE:
      if (grid_->fallingBlock()) {
        grid_->fallingBlock()->rotate(CW, grid_->grid());
      }
      break;
    case CMD_COUNTERCLOCKWISE:
      if (grid_->fallingBlock()) {
        grid_->fallingBlock()->rotate(CCW, grid_->grid());
      }
      break;
    default:
      cout << cmd << endl;
  }
}
