#include "game.h"
#include <string>

using namespace std;

int main() {
  bool textOnly = true;
  string seed = "poop";
  string scriptFile = "";
  int startLevel = 0;

  Game game = Game(textOnly, seed, scriptFile, startLevel);
  game.start();
}
