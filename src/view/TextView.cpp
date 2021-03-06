#include "TextView.h"
#include <iostream>
#include <memory>
#include <iomanip>

using namespace std;

TextView::TextView() {}

/**
 * Outputs the game grid textually
 * 
 * @param g the pointer to the grid
 * @param level the current level
 * @param score the current score
 * @param hiScore the current high score
 */
void TextView::draw(shared_ptr<Grid> g, int level, int score, int hiScore) {
  // deep copy grid
  GridShape gridToPrint = g->grid();

  // add the falling block
  const auto &fallingBlock = g->fallingBlock();
  if (fallingBlock && !g->isGameOver()) {
    Block b = *fallingBlock;
    for (int r = 0; r < b.height(); r++) {
      for (int c = 0; c < b.width(); c++) {
        int gridRow = b.bottomLeft().y - (b.height() - 1) + r;
        int gridCol = b.bottomLeft().x + c;

        if (b.shape()[r][c].val) {
          gridToPrint[gridRow][gridCol] = GridItem{b.type()};
        }
      }
    }
  }

  // add hintBlock
  const auto &hintBlock = g->hintBlock();
  if (hintBlock && !g->isGameOver()) {
    Block b = *hintBlock;
    for (int r = 0; r < b.height(); r++) {
      for (int c = 0; c < b.width(); c++) {
        int gridRow = b.bottomLeft().y - (b.height() - 1) + r;
        int gridCol = b.bottomLeft().x + c;

        if (b.shape()[r][c].val) {
          gridToPrint[gridRow][gridCol] = GridItem{HINT};
        }
      }
    }
  }

  //four spaces
  string highScoreStr = "    Hi-Score: " + to_string(hiScore);
  string levelStr = "    Level: ";
  string scoreStr = "    Score: ";
  string nextStr = "    Next: ";

  cout << levelStr << right << setw(highScoreStr.length() - levelStr.length()) << level << endl;
  cout << scoreStr << right << setw(highScoreStr.length() - scoreStr.length()) << score << endl;
  cout << highScoreStr << endl;

  // print everything
  cout << "    -----------" << endl;
  for (int row = 0; row < g->height(); row++) {
    cout << right << setw(2) << row + 1 << "  ";
    const vector<GridItem> &rowVec = gridToPrint.at(row);
    for (int col = 0; col < rowVec.size(); col++) {
      cout << gridToPrint[row][col];
    }

    cout << std::endl;
  }
  cout << "    -----------" << endl;
  cout << nextStr << endl;

  // display the next block underneath the grid
  const auto &nextBlock = g->nextBlock();
  if (nextBlock) {
    Block nb = *nextBlock;
    for (int nr = 0; nr < nb.height(); nr++) {
      cout << "    ";
      for (int nc = 0; nc < nb.width(); nc++) {
        cout << nb.shape()[nr][nc];
      }
      cout << endl;
    }
    cout << endl;
  }
}