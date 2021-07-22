#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "../grid/grid.h"
#include "View.h"
#include <memory>

class TextView : public View {
public:
  void draw(std::shared_ptr<Grid> g) override;
};

#endif