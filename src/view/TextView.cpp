#include "TextView.h"
#include <iostream>
#include <memory>
#include <iomanip>

using namespace std;

TextView::TextView() {}

void TextView::draw(shared_ptr<Grid> g, int level, int score, int hiScore) {
  // deep copy grid
  GridShape gridToPrint = g->grid();

  // add the falling block
  const auto &fallingBlock = g->fallingBlock();
  if (fallingBlock) {
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

  string highScoreStr = "    Hi-Score: " + to_string(hiScore);
  string levelStr = "    Level: ";
  string scoreStr = "    Score: ";

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
}