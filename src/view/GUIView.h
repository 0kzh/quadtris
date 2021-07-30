#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include "../grid/grid.h"
#include "../util/color.h"
#include "../util/types.h"
#include "../util/command.h"
#include "View.h"
#include <memory>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

class GUIView : public View {
  Display *dis;
  int screen;
  Window win;
  GC gc;
  XSizeHints *size_hints;
  XEvent event;
  const int GRID_SIZE = 32;

public:
  GUIView(int width, int height);

  void draw(std::shared_ptr<Grid> g, int level, int score, int highScore) override;

  Command getNextEvent();

private:
  void drawRect(int x, int y, int width, int height, Color color);

  void drawCell(int row, int col, BlockType b);

  void redraw();

  static unsigned long RGB(int r, int g, int b);
};

#endif