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

bool Game::readFromFile_ = false;
ifstream Game::fileInp_;

Game::Game(bool textOnly, int seed, string scriptFile)
    : textOnly_(textOnly), scriptFile_(scriptFile),
      score_(0), hiScore_(0) {
  views_.push_back(make_shared<TextView>(TextView()));
  views_.push_back(make_shared<GUIView>(GUIView(650, 608)));
  grid_ = make_shared<Grid>(Grid(15 + EXTRA_ROWS, 11));
  initializeLevels();
}

void Game::initializeLevels() {
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

bool Game::addBlockIfNone(const shared_ptr<Grid> &g) {
  shared_ptr<Level> curLevel = levelSequence_.at(curLevelIdx_);
  while (!g->fallingBlock()) {
    g->setNextBlocks(curLevel->makeBlock());
  }

  return g->isGameOver();
}

void Game::gameLoop() {
  bool gameOver = addBlockIfNone(grid_);

  shared_ptr<GUIView> guiView;
  bool hasTextView = false;

  for (auto &v : views_) {
    v->draw(grid_, curLevelIdx_, score_, hiScore_);
    if (dynamic_pointer_cast<GUIView>(v) != nullptr) {
      guiView = dynamic_pointer_cast<GUIView>(v);
    }
    if (dynamic_pointer_cast<TextView>(v) != nullptr) {
      hasTextView = true;
    }
  }

  grid_->hintBlock() = nullopt;

  Command c;
  if (gameOver) {
    if (hasTextView) {
      cout << "Game Over! Enter any key to restart or 'q' to quit." << endl;
      string input;
      getline(cin, input);

      cout << input;

      if (input == "q") {
        c = CMD_QUIT;
      } else {
        c = CMD_RESTART;
      }
    } else {
      do {
        c = guiView->getNextEvent();
      } while (c != CMD_QUIT && c != CMD_RESTART);
    }

    if (c == CMD_QUIT) {
      exit(0);
    } else {
      reset();
      return;
    }
  }

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
    if(readFromFile_) {
      if(fileInp_.is_open() && !fileInp_.eof()) {
        fileInp_ >> input;
      } else {
        fileInp_.close();
        readFromFile_ = false;
        getline(cin, input);
      }
    } else {
  //  cin >> input;
      getline(cin, input);
    }
    if (input.empty()) {
      exit(1); // EOF ends the game
    }
    std::pair<int, string> multipliedInput = Helper::splitMultipliedInput(input);
    multiplier = multipliedInput.first;
    input = multipliedInput.second;
    opCmd = matchCommand(input);

  } while (!opCmd || ((multiplier > 1 && *opCmd == CMD_RESTART) ||
                      *opCmd == CMD_RANDOM || *opCmd == CMD_NORANDOM));

  //Command cmd = *opCmd;
  return make_pair(multiplier, *opCmd);
}

void Game::moveDown() {
  bool shouldRemove = grid_->fallingBlock()->move(DOWN, grid_->grid());
  if (shouldRemove) {
    grid_->fallingBlock() = nullopt;
  }
}

void Game::reset() {
  curLevelIdx_ = 0;
  score_ = 0;
  grid_->restart();
  initializeLevels();
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
          addBlockIfNone(grid_);
        }
        break;
      case CMD_LEVELUP:
        if (curLevelIdx_ + 1 < levelSequence_.size()) {
          curLevelIdx_++;
        }
        break;
      case CMD_LEVELDOWN:
        if (curLevelIdx_ - 1 >= 0) {
          curLevelIdx_--;
        }
        break;
      case CMD_NORANDOM:
        (levelSequence_.at(3))->setRandom(false);
        (levelSequence_.at(4))->setRandom(false);
        break;
      case CMD_RANDOM: {
        string file;
        cin >> file;
        (levelSequence_.at(3))->setRandom(true);
        (levelSequence_.at(3))->readFile(file);
        (levelSequence_.at(4))->setRandom(true);
        (levelSequence_.at(4))->readFile(file);
        break;
      }
      case CMD_SEQUENCE: {
        string file;
        cin >> file;
        fileInp_.open(file);
        readFromFile_ = true;
        break;
      }
      case CMD_RESTART:
        reset();
        multiplier = 0;
        break;
      case CMD_HINT:
        if (grid_->hintBlock() != nullopt) {
          grid_->hintBlock() = nullopt;
        } else {
          grid_->setHintBlock();
        }
        break;
      case CMD_I:
      case CMD_J:
      case CMD_L:
      case CMD_S:
      case CMD_Z:
      case CMD_O:
      case CMD_T:
        if (grid_->fallingBlock()) {
          grid_->fallingBlock()->setType(cmdToBlockType[cmd]);
        }
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
