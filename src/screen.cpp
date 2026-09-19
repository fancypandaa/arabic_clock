#include "screen.h"
#include <iostream>
#include <math.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
namespace Screen {

void ScreenJobs::initScreen() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  SCREENY = (w.ws_row > MAXY) ? MAXY : w.ws_row;
  SCREENX = (w.ws_col > MAXX) ? MAXX : w.ws_col;
}

void ScreenJobs::charXY(int layer, int x, int y, s_simplechar &simplechar) {
  if (x >= 0 && x <= SCREENX && y >= 0 && y <= SCREENY) {
    LAYER[layer][x][y] = simplechar;
  }
}
void ScreenJobs::stringXX(int x, int y, simple_str &s_str) {
  if (x >= 0 && x <= SCREENX && y >= 0 && y <= SCREENY) {
    LAYER_STR[x][y] = s_str;
  }
}
void ScreenJobs::stringXY(int layer, int x, int y, s_simplechar &simplechar,
                          std::string s) {
  int i;
  for (i = 0; i < s.length(); i++) {
    simplechar.chr = s[i];
    charXY(layer, x + i, y, simplechar);
  }
}

void ScreenJobs::lineXY(int layer, int x1, int y1, int x2, int y2,
                        s_simplechar &simplechar) {
  int x, y = 0;
  float fx, fy = 0; // line angle
  int t = 0;
  int kulx = x2 - x1;
  int kuly = y2 - y1;

  if (abs(kulx) >= abs(kuly)) {
    fy = (float)(y2 - y1) / (x2 - x1);
    if (x1 > x2) {
      t = x1;
      x1 = x2;
      x2 = t;
      t = y1;
      y1 = y2;
      y2 = t;
    }
    for (x = x1; x <= x2; x++) {
      charXY(layer, x, round(y1 + fy * (x - x1)), simplechar);
    }

  } else {
    fx = (float)(x2 - x1) / (y2 - y1);
    if (y1 > y2) {
      t = x1;
      x1 = x2;
      x2 = t;
      t = y1;
      y1 = y2;
      y2 = t;
    }

    for (y = y1; y <= y2; y++) {
      charXY(layer, round(x1 + fx * (y - y1)), y, simplechar);
    }
  }
}

void ScreenJobs::clearLayer(int layer, s_simplechar &simplechar) {
  int x, y;
  for (y = 0; y <= SCREENY; y++) {
    for (x = 0; x <= SCREENX; x++) {
      LAYER[layer][x][y] = simplechar;
    }
  }
}

void ScreenJobs::clearAllLayer(s_simplechar simplechar) {
  int l;
  clearLayer(0, WRITECHAR);
  for (l = 1; l < MAXLAYERS; l++) { // others can be filled with anything
    clearLayer(l, simplechar);
  }
}

void ScreenJobs::mergeLayers() {
  int l, x, y;
  for (l = 0; l <= MAXLAYERS; l++) {
    for (y = 0; y <= SCREENY; y++) {
      for (x = 0; x <= SCREENX; x++) {
        FINAL[x][y].chr =
            LAYER[l][x][y].transpchr ? FINAL[x][y].chr : LAYER[l][x][y].chr;
        FINAL[x][y].col =
            LAYER[l][x][y].transpcol ? FINAL[x][y].col : LAYER[l][x][y].col;
        FINAL[x][y].bcol =
            LAYER[l][x][y].transpbcol ? FINAL[x][y].bcol : LAYER[l][x][y].bcol;
      }
    }
  }
}

void ScreenJobs::printScreen() {
  int x, y;
  gotoxy(1, 1);
  for (y = 0; y < SCREENY; y++) {
    for (x = 0; x < SCREENX; x++) {
      simple_str &strLayer = LAYER_STR[x][y];
      if (!strLayer.transpchr && strLayer.str != " " &&
          strLayer.str.length() > 0) {
        printf("\033[%s;%sm", COLORS[FINAL[x][y].col].c_str(),
               BCOLORS[FINAL[x][y].bcol].c_str());
        printf("\033[%dm", 10);
        std::cout << strLayer.str;
        printf("\033[%dm", 0);
      } else {
        printf("\033[%s;%sm", COLORS[FINAL[x][y].col].c_str(),
               BCOLORS[FINAL[x][y].bcol].c_str());
        printf("\033[%dm", 10); // Set character spacing
        putchar(FINAL[x][y].chr);
        printf("\033[%dm", 0); // Reset
      }
    }
    if (y < SCREENY - 1) {
      putchar(10);
      putchar(13);
    }
  }
}
} // namespace Screen
  // een
