#include "game.h"
#include "view/TextView.h"
#include "util/command.h"
#include "util/helper.h"
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

void addBlockIfNone(shared_ptr<Grid> g) {
  if (!g->fallingBlock()) {
    g->setFallingBlock(Block{T, false});
  }
}

void Game::gameLoop() {
  for (auto &v : views_) {
    addBlockIfNone(grid_);

    v->draw(grid_);
    processCommand();

    addBlockIfNone(grid_);
  }
}

void Game::processCommand() {
  int multiplier;
  string input;

  do {
    getline(cin, input);
    std::pair<int, string> multipliedInput = splitMultipliedInput(input);
    multiplier = multipliedInput.first;
    input = multipliedInput.second;
  } while (!matchCommand(input));

  Command cmd = *matchCommand(input);

  for (int i = 0; i < multiplier; i++) {
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
          bool shouldRemove = grid_->fallingBlock()->move(DOWN, grid_->grid());
          if (shouldRemove) {
            grid_->fallingBlock() = nullopt;
          }
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
      case CMD_DROP:
        if (grid_->fallingBlock()) {
          grid_->fallingBlock()->drop(grid_->grid());
          grid_->fallingBlock() = nullopt;
        }
        break;
      default:
        break;
    }
  }
}

