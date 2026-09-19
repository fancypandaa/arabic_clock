#include "background_snow.h"
#include "clock_digital.h"
#include "screen.h"
#include <cstdlib>

namespace BackgroundSnow {
void Snow::calc_new_flake(int i) {
  SNOWFLAKES[i].x = rand() % Screen::SCREENX;
  SNOWFLAKES[i].y = 0;
  SNOWFLAKES[i].spd = rand() % (MAXSPD + 1);
}
void Snow::init_bg_snow() {
  int i, x, y;
  for (int i = 0; i <= 1; i++) {
    Screen::ScreenJobs::clearLayer(i, SNOWCLEAR);
  }

  for (int i = 0; i < MAXSNOW; i++) {
    calc_new_flake(i);
    SNOWFLAKES[i].y = rand() % Screen::SCREENY;
  }
  for (int y = 0; y < Screen::SCREENY; y++) {
    for (x = 0; x <= Screen::SCREENX; x++) {
      SNOWBG[x][y] = 0;
    }
  }
  for (x = 0; x <= Screen::SCREENX; x++) {
    SNOWBG[x][Screen::SCREENY - 1] = 1;
  }

  ClockDigital::CLOCKCHAR.transpbcol = false;
  ClockDigital::CLOCKCHAR.transpcol = true;
  ClockDigital::CLOCKCHAR.transpchr = true;
  ClockDigital::AVOIDCLOCKCOLOR = 0;
}

void Snow::inc_snow_bg(unsigned int x, unsigned int y) {
  SNOWBG[x][y]++;
  if (SNOWBG[x][y] > MAXSNOWBG - 1) {
    SNOWBG[x][y] = MAXSNOWBG - 1;
    if (y > 0) {
      SNOWBG[x][y - 1]++;
      if (SNOWBG[x][y - 1] > MAXSNOWBG - 1) {
        SNOWBG[x][y - 1] = MAXSNOWBG - 1;
      }
    }
  }
}
void Snow::calc_bg_snow() {
  int i;
  for (i = 0; i < MAXSNOW; i++) {
    SNOWFLAKES[i].spdcounter++;

    if (SNOWFLAKES[i].spdcounter > SNOWFLAKES[i].spd + 2) {
      SNOWFLAKES[i].spdcounter = 0;
      SNOWFLAKES[i].y++; // go down :)

      if (SNOWFLAKES[i].y > Screen::SCREENY) {
        // generate a new flake at random position
        calc_new_flake(i);
      } else {
        if (SNOWFLAKES[i].x > 0 && SNOWFLAKES[i].x < Screen::SCREENX &&
            SNOWFLAKES[i].y > 0 && SNOWFLAKES[i].y < Screen::SCREENY) {

          if (SNOWBG[SNOWFLAKES[i].x][SNOWFLAKES[i].y] > 0) {
            inc_snow_bg(SNOWFLAKES[i].x - 1, SNOWFLAKES[i].y);
            inc_snow_bg(SNOWFLAKES[i].x, SNOWFLAKES[i].y);
            inc_snow_bg(SNOWFLAKES[i].x + 1, SNOWFLAKES[i].y);

            // calc_new_flake(i);
          }
        }
      }
      SNOWFLAKES[i].x += rand() % 3 - 1;
      inc_snow_bg(5, Screen::SCREENY - 1);
    }
  }
}
void Snow::draw_bg_snow() {
  int i, x, y;
  Screen::ScreenJobs::clearLayer(SNOWLAYER, SNOWCLEAR);
  for (i = 0; i < MAXSNOW; i++) {
    Screen::ScreenJobs::charXY(1, SNOWFLAKES[i].x, SNOWFLAKES[i].y,
                               SNOWCHARS[SNOWFLAKES[i].spd]);
  }
  for (y = 0; y <= Screen::SCREENY; y++) {
    for (x = 0; x <= Screen::SCREENX; x++) {
      if (SNOWBG[x][y] > 0) {
        Screen::ScreenJobs::charXY(SNOWLAYER, x, y, SNOWBGCHARS[SNOWBG[x][y]]);
      }
    }
  }
}
} // namespace BackgroundSnow
// print out the final image to screen
// print out the final image to screen
// print out the final image to screen
