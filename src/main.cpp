#include "game.h"
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  bool textOnly = false;
  bool guiOnly = false;
  int seed = 0;
  string scriptFile = "sequence.txt";
  int startLevel = 0;

  for (int i = 1; i < argc; i++) {
    char *cur = argv[i];
    int j = 0;
    char prev = '\0';
    while (cur[j] != '\0') {
      if (prev == 's') {
        if (cur[j] == 'c') {
          scriptFile = argv[i + 1];
        } else if (cur[j] == 'e') {
          seed = atoi(argv[i + 1]);
        } else if (cur[j] == 't') {
          startLevel = atoi(argv[i + 1]);
        }
        i++;
        break;
      } else if (prev == '-' && cur[j] == 't') {
        textOnly = true;
        break;
      } else if (prev == '-' && cur[j] == 'g') {
        guiOnly = true;
        break;
      }
      prev = cur[j];
      j++;
    }
  }
  if (startLevel < 0 || startLevel > 4) {
    startLevel = 0;
  }


  srand(seed);
  Game game = Game(textOnly, guiOnly, seed, scriptFile);
  Game::curLevelIdx_ = startLevel;
  game.start();
}
