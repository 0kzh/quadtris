#include "TextView.h"
#include <iostream>
#include <memory>

using namespace std;

void TextView::draw(shared_ptr<Grid> g) {
  for (int row = 0; row < g->height(); row++) {
    const std::vector<GridItem> &rowVec = g->grid().at(row);
    for (int col = 0; col < rowVec.size(); col++) {
      cout << g->grid()[row][col];
    }

    cout << std::endl;
  }
}