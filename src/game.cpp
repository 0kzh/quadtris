#include "game.h"
#include "util/helper.h"
#include "view/GUIView.h"
#include "view/TextView.h"
#include "levels/levelOne.h"
#include <memory>
#include <iostream>

using namespace std;

Game::Game(bool textOnly, int seed, string scriptFile)
    : textOnly_(textOnly), scriptFile_(scriptFile),
      score_(0), hiScore_(0) {
  views_.push_back(make_shared<TextView>(TextView()));
  //  views_.push_back(make_shared<GUIView>(GUIView(400, 800)));
  grid_ = make_shared<Grid>(Grid(15 + EXTRA_ROWS, 11));

  // TODO: add other levels
  levelSequence_ = {make_shared<LevelOne>(LevelOne())};
}

int Game::curLevelIdx_ = 0;

void

Game::start() {
  while (true) {
    gameLoop();
  }
}

void Game::addBlockIfNone(const shared_ptr<Grid> &g) {
  shared_ptr<Level> curLevel = levelSequence_.at(curLevelIdx_);
  if (!g->fallingBlock()) {
    g->setFallingBlock(curLevel->makeBlock());
  }
}

void Game::gameLoop() {
  addBlockIfNone(grid_);
  shared_ptr<GUIView> guiView;
  bool hasTextView = false;

  for (auto &v : views_) {
    v->draw(grid_, curLevelIdx_ + 1, score_, hiScore_);
    if (dynamic_pointer_cast<GUIView>(v) != nullptr) {
      guiView = dynamic_pointer_cast<GUIView>(v);
    }
    if (dynamic_pointer_cast<TextView>(v) != nullptr) {
      hasTextView = true;
    }
  }

  Command c;
  int multiplier;
  if (hasTextView) {
    pair<int, Command> res = readCommand();
    multiplier = res.first;
    c = res.second;
  } else {
    multiplier = 1;
    c = guiView->getNextEvent();
  }

  processCommand(multiplier, c);

  score_ += grid_->clearLines();
  hiScore_ = max(hiScore_, score_);

  addBlockIfNone(grid_);
}

pair<int, Command> Game::readCommand() {
  int multiplier;
  string input;

  do {
    getline(cin, input);
    std::pair<int, string> multipliedInput = Helper::splitMultipliedInput(input);
    multiplier = multipliedInput.first;
    input = multipliedInput.second;
  } while (!matchCommand(input));

  Command cmd = *matchCommand(input);

  return make_pair(multiplier, cmd);
}

void Game::processCommand(int multiplier, Command cmd) {
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