#include "TextView.h"
#include <iostream>
#include <memory>

using namespace std;

TextView::TextView() {}

void TextView::draw(shared_ptr<Grid> g) {
  // deep copy grid
  vector<vector<GridItem>> gridToPrint = g->grid();

  // add the falling block
  const auto &fallingBlock = g->fallingBlock();
  if (fallingBlock) {
    Block b = *fallingBlock;
    for (int r = 0; r < b.height(); r++) {
      for (int c = 0; c < b.width(); c++) {
        int gridRow = b.bottomLeft().y - b.height() + r;
        int gridCol = b.bottomLeft().x + c;

        if (b.shape()[r][c].val) {
          gridToPrint[gridRow][gridCol] = GridItem{b.type()};
        }
      }
    }
  }

  // print everything
  for (int row = 0; row < g->height(); row++) {
    const vector<GridItem> &rowVec = gridToPrint.at(row);
    for (int col = 0; col < rowVec.size(); col++) {
      cout << gridToPrint[row][col];
    }

    cout << std::endl;
  }
}