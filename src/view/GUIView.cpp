#include "GUIView.h"
#include <memory>

using namespace std;

GUIView::GUIView(int width, int height) {
  unsigned long black, white;

  /* use the information from the environment variable DISPLAY
     to create the X connection:
  */
  dis = XOpenDisplay((char *) nullptr);
  assert(dis);
  screen = DefaultScreen(dis);
  black = BlackPixel(dis, screen);  /* get color black */
  white = WhitePixel(dis, screen);  /* get color white */

  /* once the display is initialized, create the window.
     This window will be have be 200 pixels across and 300 down.
     It will have the foreground white and background black
  */
  win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0,
                            width, height, 5, white, black);

  /* here is where some properties of the window can be set.
     The third and fourth items indicate the name which appears
     at the top of the window and the name of the minimized window
     respectively.
  */
  XSetStandardProperties(dis, win, "Quadtris", "HI!", None, NULL, 0, NULL);

  /* this routine determines which types of input are allowed in
     the input.  see the appropriate section for details...
  */
  XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask);

  /* create the Graphics Context */
  gc = XCreateGC(dis, win, 0, 0);

  /* here is another routine to set the foreground and background
     colors _currently_ in use in the window.
  */
  XSetBackground(dis, gc, white);
  XSetForeground(dis, gc, black);

  size_hints = XAllocSizeHints();

  if (size_hints == nullptr) {
    fprintf(stderr, "XMallocSizeHints() failed\n");

    exit(1);
  }

  size_hints->flags = USPosition | PAspect | PMinSize | PMaxSize;
  size_hints->min_width = width;
  size_hints->min_height = height;
  size_hints->max_width = width;
  size_hints->max_height = height;

  XSetWMNormalHints(dis, win, size_hints);

  /* clear the window and bring it on top of the other windows */
  XClearWindow(dis, win);
  XMapRaised(dis, win);
}

void GUIView::draw(shared_ptr<Grid> g) {
  XNextEvent(dis, &event);
  if (event.type == Expose && event.xexpose.count == 0) {
    redraw();
  }
}

void GUIView::redraw() {
  XClearWindow(dis, win);
};