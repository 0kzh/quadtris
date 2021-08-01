#include "GUIView.h"
#include "../util/helper.h"
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
  XSetStandardProperties(dis, win, "Quadtris", "Quadtris", None, NULL, 0, NULL);

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

void GUIView::draw(shared_ptr<Grid> g, int level, int score, int hiScore) {
  redraw();

  Color white = {255, 255, 255};
  drawText("SCORE: " + to_string(score), 448, 48, white);
  drawText("HI-SCORE: " + to_string(hiScore), 448, 80, white);

  drawText("NEXT", 448, 128, white);
  drawRect(448, 145, 192, 96, white);

  const auto &nextBlock = g->nextBlock();
  if (nextBlock) {
    Block nb = *nextBlock;
    for (int r = 0; r < nb.height(); r++) {
      for (int c = 0; c < nb.width(); c++) {
        if (nb.shape()[r][c].val) {
          int width = (int) nb.shape()[0].size() * GRID_SIZE;
          int totalWidth = 6 * GRID_SIZE;
          int xStart = (totalWidth - width) / 2;

          int height = (int) nb.shape().size() * GRID_SIZE;
          int totalHeight = 3 * GRID_SIZE;
          int yStart = (totalHeight - height) / 2;
          drawCell(448 + xStart + c * GRID_SIZE, 145 + yStart + r * GRID_SIZE, nb.type());
        }
      }
    }
  }

  drawText("CONTROLS", 448, 350, white);

  Color gray = {196, 196, 196};
  int controlsWidth = 15;
  drawText(Helper::generateCenterJustifiedString("Left", "- ", controlsWidth), 448, 400, gray);
  drawText(Helper::generateCenterJustifiedString("", "<", controlsWidth), 435, 400, gray);
  drawText(Helper::generateCenterJustifiedString("Right", "- ", controlsWidth), 448, 430, gray);
  drawText(Helper::generateCenterJustifiedString("", ">", controlsWidth), 440, 430, gray);
  drawText(Helper::generateCenterJustifiedString("Down", "| ", controlsWidth), 448, 460, gray);
  drawText(Helper::generateCenterJustifiedString("", "v ", controlsWidth), 448, 460, gray);
  drawText(Helper::generateCenterJustifiedString("", "^ ", controlsWidth), 448, 490, gray);
  drawText(Helper::generateCenterJustifiedString("Rotate", "| ", controlsWidth), 448, 490, gray);
  drawText(Helper::generateCenterJustifiedString("Drop", "<SPACE>", controlsWidth), 448, 520, gray);
  drawText(Helper::generateCenterJustifiedString("Level Up", "+ ", controlsWidth), 448, 550, gray);
  drawText(Helper::generateCenterJustifiedString("Level Down", "- ", controlsWidth), 448, 580, gray);

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

  // add padding for walls
  for (auto &row : gridToPrint) {
    row.insert(row.begin(), GridItem{WALL});
    row.push_back(GridItem{WALL});
  }

  vector<GridItem> floor(g->width() + 2, GridItem{WALL});
  gridToPrint.push_back(floor);


  // print it!
  for (int row = 0; row < g->height() + 1; row++) {
    const vector<GridItem> &rowVec = gridToPrint.at(row);
    for (int col = 0; col < rowVec.size(); col++) {
      GridItem block = gridToPrint[row][col];

      if (block.val) {
        drawCellInGrid(row, col, *block.val);
      }
    }
  }

  while (XPending(dis)) {
    XNextEvent(dis, &event);
  }
}

Command GUIView::getNextEvent() {
  XNextEvent(dis, &event);
  switch (event.type) {
    case KeyPress:
      switch (XLookupKeysym(&event.xkey, 0)) {
        case XK_Left:
          return CMD_LEFT;
        case XK_Right:
          return CMD_RIGHT;
        case XK_Down:
          return CMD_DOWN;
        case XK_Up:
          return CMD_CLOCKWISE;
        case XK_space:
          return CMD_DROP;
      }
  }
  return CMD_NOOP;
}

void GUIView::fillRect(int x, int y, int width, int height, Color color) {
  XSetForeground(dis, gc, RGB(color.r, color.g, color.b));
  XFillRectangle(dis, win, gc, x, y, width, height);
}

void GUIView::drawRect(int x, int y, int width, int height, Color color) {
  XSetForeground(dis, gc, RGB(color.r, color.g, color.b));
  XDrawRectangle(dis, win, gc, x, y, width, height);
}

void GUIView::drawCell(int x, int y, BlockType block) {
  Color base = blockColors[block].base;
  Color highlight = blockColors[block].highlight;
  Color shadow = blockColors[block].shadow;
  int edge = GRID_SIZE / 8;

  fillRect(x, y, GRID_SIZE, GRID_SIZE, shadow);
  fillRect(x + edge, y, GRID_SIZE - edge, GRID_SIZE - edge, highlight);
  fillRect(x + edge, y + edge, GRID_SIZE - edge * 2, GRID_SIZE - edge * 2, base);
}

void GUIView::drawCellInGrid(int row, int col, BlockType block) {
  int x = col * GRID_SIZE;
  int y = row * GRID_SIZE;
  drawCell(x, y, block);
}

unsigned long GUIView::RGB(int r, int g, int b) {
  return b + (g << 8) + (r << 16);
}

void GUIView::redraw() {
  XClearWindow(dis, win);
}

void GUIView::drawText(std::string text, int x, int y, Color color) {
  XFontStruct *font = XLoadQueryFont(dis, "10x20");
  XTextItem textToDraw = {const_cast<char *>(text.c_str()), static_cast<int>(text.length()), 0, font->fid};

  XSetForeground(dis, gc, RGB(color.r, color.g, color.b));
  XDrawText(dis, win, gc, x, y, &textToDraw, 1);
}
