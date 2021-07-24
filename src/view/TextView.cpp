#include "TextView.h"
#include <iostream>
#include <memory>
#include <iomanip>

using namespace std;

TextView::TextView() {}

void TextView::draw(shared_ptr<Grid> g) {
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