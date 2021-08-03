#include "GUIView.h"
#include "../util/helper.h"
#include <memory>
#include <cassert>

using namespace std;

/**
 * GUIView constructor which initializes the GUI display.
 * 
 * @param width the display width in pixels
 * @param height the display height in pixels
 */
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

  width_ = width;
  height_ = height;

  XSetWMNormalHints(dis, win, size_hints);

  /* clear the window and bring it on top of the other windows */
  XClearWindow(dis, win);
  XMapRaised(dis, win);
}

/**
 * Draws a game grid onto the display
 * 
 * @param g the pointer to the grid
 * @param level the current level
 * @param score the current score
 * @param hiScore the current high score
 */
void GUIView::draw(shared_ptr<Grid> g, int level, int score, int hiScore) {
  redraw();

  if (g->isGameOver()) {
    drawGameOverScreen(g, level, score, hiScore);
  } else {
    drawGameScreen(g, level, score, hiScore);
  }

  while (XPending(dis)) {
    XNextEvent(dis, &event);
  }
}

/**
 * For drawing the game grid when it is not yet game over
 * 
 * @param g the pointer to the grid
 * @param level the current level
 * @param score the current score
 * @param hiScore the current high score
 */
void GUIView::drawGameScreen(shared_ptr<Grid> g, int level, int score, int hiScore) {
  Color white = {255, 255, 255};

  drawText("LEVEL: " + to_string(level), 448, 46, white);
  drawText("SCORE: " + to_string(score), 448, 78, white);
  drawText("HI-SCORE: " + to_string(hiScore), 448, 110, white);

  drawText("NEXT", 448, 158, white);
  drawRect(448, 175, 192, 96, white);

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
          drawCell(448 + xStart + c * GRID_SIZE, 175 + yStart + r * GRID_SIZE, nb.type());
        }
      }
    }
  }

  drawText("CONTROLS", 448, 320, white);

  Color gray = {196, 196, 196};
  int controlsWidth = 15;
  drawText(Helper::generateCenterJustifiedString("Left", "- ", controlsWidth), 448, 370, gray);
  drawText(Helper::generateCenterJustifiedString("", "<", controlsWidth), 435, 370, gray);
  drawText(Helper::generateCenterJustifiedString("Right", "- ", controlsWidth), 448, 400, gray);
  drawText(Helper::generateCenterJustifiedString("", ">", controlsWidth), 440, 400, gray);
  drawText(Helper::generateCenterJustifiedString("Down", "| ", controlsWidth), 448, 430, gray);
  drawText(Helper::generateCenterJustifiedString("", "v ", controlsWidth), 448, 430, gray);
  drawText(Helper::generateCenterJustifiedString("", "^ ", controlsWidth), 448, 460, gray);
  drawText(Helper::generateCenterJustifiedString("Rotate", "| ", controlsWidth), 448, 460, gray);
  drawText(Helper::generateCenterJustifiedString("Drop", "<SPACE>", controlsWidth), 448, 490, gray);
  drawText(Helper::generateCenterJustifiedString("Level Up", "<e>", controlsWidth), 448, 520, gray);
  drawText(Helper::generateCenterJustifiedString("Level Down", "<q>", controlsWidth), 448, 550, gray);
  drawText(Helper::generateCenterJustifiedString("Hint", "<h>", controlsWidth), 448, 580, gray);

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

  const auto &hintBlock = g->hintBlock();
  if (hintBlock) {
    Block b = *hintBlock;
    for (int r = 0; r < b.height(); r++) {
      for (int c = 0; c < b.width(); c++) {
        int gridRow = b.bottomLeft().y - (b.height() - 1) + r;
        int gridCol = b.bottomLeft().x + c;

        if (b.shape()[r][c].val) {
          gridToPrint[gridRow][gridCol] = GridItem{HINT};
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
}

/**
 * For drawing the game over screen
 * 
 * @param g the pointer to the grid
 * @param level the current level
 * @param score the current score
 * @param hiScore the current high score
 */
void GUIView::drawGameOverScreen(std::shared_ptr<Grid> g, int level, int score, int highScore) {
  Color white = {255, 255, 255};
  Color gray = {196, 196, 196};

  string gameOverText = "GAME OVER!";
  string scoreText = "SCORE: " + to_string(score);
  string restartText = "press <r> to restart";

  auto textWidth = [](const string &text) {
    return (int) text.length() * 11; // each char is 11px in width
  };

  drawText(gameOverText, (width_ - textWidth(gameOverText)) / 2, 270, white);
  drawText(scoreText, (width_ - textWidth(scoreText)) / 2, 290, gray);
  drawText(restartText, (width_ - textWidth(restartText)) / 2, 340, gray);
}

/**
 * Gets the next GUI event
 *
 * @returns the command ENUM specifying the next GUI event
 */
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
        case XK_e:
          return CMD_LEVELUP;
        case XK_q:
          return CMD_LEVELDOWN;
        case XK_r:
          return CMD_RESTART;
        case XK_h:
          return CMD_HINT;
      }
  }
  return CMD_NOOP;
}

/**
 * Fills a rectangle shape with colour
 * 
 * @param x the x-coordinate of the top-left pixel
 * @param y the y-coordinate of the top-left pixel
 * @param width the width of the rectangle in pixels 
 * @param height the height of the rectangle in pixels
 * @param color the colour to fill with
 */
void GUIView::fillRect(int x, int y, int width, int height, Color color) {
  XSetForeground(dis, gc, RGB(color.r, color.g, color.b));
  XFillRectangle(dis, win, gc, x, y, width, height);
}

/**
 * Defines the outline of a rectangle shape
 * 
 * @param x the x-coordinate of the top-left pixel
 * @param y the y-coordinate of the top-left pixel
 * @param width the width of the rectangle in pixels
 * @param height the height of the rectangle in pixels
 * @param color the colour to fill with
 */
void GUIView::drawRect(int x, int y, int width, int height, Color color) {
  XSetForeground(dis, gc, RGB(color.r, color.g, color.b));
  XDrawRectangle(dis, win, gc, x, y, width, height);
}

/**
 * Draws one cell of a block with foreground, shadow, and highlighting.
 * 
 * @param x the x-coordinate of the cell's top-left pixel
 * @param y the y-coordinate of the cell's top-left pixel
 * @param block the type of the block
 */
void GUIView::drawCell(int x, int y, BlockType block) {
  Color base = blockColors[block].base;
  Color highlight = blockColors[block].highlight;
  Color shadow = blockColors[block].shadow;
  int edge = GRID_SIZE / 8;

  fillRect(x, y, GRID_SIZE, GRID_SIZE, shadow);
  fillRect(x + edge, y, GRID_SIZE - edge, GRID_SIZE - edge, highlight);
  fillRect(x + edge, y + edge, GRID_SIZE - edge * 2, GRID_SIZE - edge * 2, base);
}

/**
 * Calls drawCell() based on the grid dimensions
 * 
 * @param x the x position of the cell in the game grid
 * @param y the y position of the cell in the game grid
 * @param block the type of the block
 */
void GUIView::drawCellInGrid(int row, int col, BlockType block) {
  int x = col * GRID_SIZE;
  int y = row * GRID_SIZE;
  drawCell(x, y, block);
}

/**
 * Computes a long to store RGB information about a colour.
 * 
 * @param r the R value
 * @param g the G value
 * @param b the b Value
 * @returns the long encoding all three values at once
 */
unsigned long GUIView::RGB(int r, int g, int b) {
  return b + (g << 8) + (r << 16);
}

/**
 * Clears the display for redrawing
 */
void GUIView::redraw() {
  XClearWindow(dis, win);
}

/**
 * Draws text on the display
 * 
 * @param text the string of text
 * @param x the x-coordinate of the textbox's top left corner
 * @param y the y-coordinate of the textbox's top left corner
 * @param color the colour of the text
 */
void GUIView::drawText(std::string text, int x, int y, Color color) {
  XFontStruct *font = XLoadQueryFont(dis, "10x20");
  XTextItem textToDraw = {const_cast<char *>(text.c_str()), static_cast<int>(text.length()), 0, font->fid};

  XSetForeground(dis, gc, RGB(color.r, color.g, color.b));
  XDrawText(dis, win, gc, x, y, &textToDraw, 1);
}
