#include "game.h"
#include "util/helper.h"
#include "view/GUIView.h"
#include "view/TextView.h"
#include "levels/levelZero.h"
#include "levels/levelOne.h"
#include "levels/levelTwo.h"
#include "levels/levelThree.h"
#include "levels/levelFour.h"
#include <memory>
#include <iostream>

using namespace std;

Game::Game(bool textOnly, int seed, string scriptFile)
    : textOnly_(textOnly), scriptFile_(scriptFile),
      score_(0), hiScore_(0) {
//  views_.push_back(make_shared<TextView>(TextView()));
  views_.push_back(make_shared<GUIView>(GUIView(600, 608)));
  grid_ = make_shared<Grid>(Grid(15 + EXTRA_ROWS, 11));

  levelSequence_ = {make_shared<LevelZero>(LevelZero(scriptFile_)),
                    make_shared<LevelOne>(LevelOne()),
                    make_shared<LevelTwo>(LevelTwo()),
                    make_shared<LevelThree>(LevelThree()),
                    make_shared<LevelFour>(LevelFour())};
}

int Game::curLevelIdx_ = 0;

void Game::start() {
  while (true) {
    gameLoop();
  }
}

void Game::addBlockIfNone(const shared_ptr<Grid> &g) {
  shared_ptr<Level> curLevel = levelSequence_.at(curLevelIdx_);
  while (!g->fallingBlock()) {
    g->setNextBlocks(curLevel->makeBlock());
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
  std::optional<Command> opCmd;

  do {
    cin >> input;
    //getline(cin, input);
    std::pair<int, string> multipliedInput = Helper::splitMultipliedInput(input);
    multiplier = multipliedInput.first;
    input = multipliedInput.second;
    opCmd = matchCommand(input);

  } while (!opCmd || (multipler > 1 && *opCmd == CMD_RESTART || 
    *opCmd == CMD_HINT || *opCmd == CMD_RANDOM || *opCmd == CMD_NORANDOM));

  //Command cmd = *opCmd;
  return make_pair(multiplier, *opCmd);
}

void Game::moveDown() {
  bool shouldRemove = grid_->fallingBlock()->move(DOWN, grid_->grid());
  if (shouldRemove) {
    grid_->fallingBlock() = nullopt;
  }
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
          moveDown();
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
      case CMD_LEVELUP:
        curLevelIdx_++;
        break;
      case CMD_LEVELDOWN:
        curLevelIdx_--;
        break;
      case CMD_NORANDOM:
        (levelSequence_.at(3))->setRandom(false);
        (levelSequence_.at(4))->setRandom(false);
        break;
      case CMD_RANDOM:
        string file; cin >> file;
        (levelSequence_.at(3))->setRandom(true);
        (levelSequence_.at(3))->readFile(file);
        (levelSequence_.at(4))->setRandom(true);
        (levelSequence_.at(4))->readFile(file);
        break;
      case CMD_SEQUENCE:
        break;
      case CMD_RESTART:
        grid_->restart();
        score_ = 0;
        multiplier = 0;
        break;
      default:
        break;
    }

    if (grid_->fallingBlock() && grid_->fallingBlock()->heavy() &&
        cmd >= CMD_LEFT && cmd <= CMD_COUNTERCLOCKWISE) {
      moveDown();
    }
  }
}
