#include "game.h"
#include "view/TextView.h"

Game::Game(bool textOnly, string seed, string scriptFile, int initialLevel)
    : textOnly_(textOnly), scriptFile_(scriptFile), curLevelIdx_(initialLevel) {
  views_.push_back(make_unique<TextView>());
}

void Game::start() {
  while (true) {
    gameLoop();
  }
}

void Game::gameLoop() {
  for (auto &v : views_) {
    v->draw(grid_);
  }
}