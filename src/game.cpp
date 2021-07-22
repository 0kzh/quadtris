#include "game.h"
#include "view/TextView.h"
#include "util/command.h"
#include <iostream>

using namespace std;

Game::Game(bool textOnly, string seed, string scriptFile, int initialLevel)
    : textOnly_(textOnly), scriptFile_(scriptFile), curLevelIdx_(initialLevel) {
  views_.push_back(make_shared<TextView>(TextView()));
  grid_ = make_shared<Grid>(Grid(11, 15 + EXTRA_ROWS));
}

void Game::start() {
  while (true) {
    gameLoop();
  }
}

void Game::gameLoop() {
  for (auto &v : views_) {
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

    cout << cmd << endl;
}
