/* Base class for all views. Follows Observer pattern. */

#ifndef VIEW_H
#define VIEW_H

#include "../grid/grid.h"
#include <memory>

class View {
public:
  virtual void draw(std::shared_ptr<Grid> g, int level, int score, int highScore) = 0;

  virtual ~View() = default;
};

#endif