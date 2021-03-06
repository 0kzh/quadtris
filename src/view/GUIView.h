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
  int width_;
  int height_;
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
  void drawGameScreen(std::shared_ptr<Grid> g, int level, int score, int highScore);

  void drawGameOverScreen(std::shared_ptr<Grid> g, int level, int score, int highScore);

  void fillRect(int x, int y, int width, int height, Color color);

  void drawRect(int x, int y, int width, int height, Color color);

  void drawCell(int x, int y, BlockType b);

  void drawCellInGrid(int row, int col, BlockType b);

  void drawText(std::string text, int x, int y, Color color);

  void redraw();

  static unsigned long RGB(int r, int g, int b);
};

#endif