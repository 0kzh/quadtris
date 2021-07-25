#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include "../grid/grid.h"
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
public:
  GUIView(int width, int height);

  void draw(std::shared_ptr<Grid> g) override;

  void redraw();
};

#endif