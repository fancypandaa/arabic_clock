#ifndef BACKGROUND_SNOW_H
#define BACKGROUND_SNOW_H

#include "screen.h"
namespace BackgroundSnow {
inline const int MAXSNOW = 100, MAXSPD = 2, SNOWLAYER = 1;
inline const int MAXSNOWBG = 5;
inline int SNOWBG[Screen::MAXX][Screen::MAXY];

inline Screen::s_simplechar SNOWCHARS[3] = {
    {42, Screen::C_WHITE, 8, false, false, true},
    {43, Screen::C_GRAY, 8, false, false, true},
    {46, Screen::C_DGRAY, 8, false, false, true}};

inline Screen::s_simplechar SNOWCLEAR = {32, 0, 8, false, false, false};

inline Screen::s_simplechar SNOWBGCHARS[MAXSNOWBG] = {
    {32, Screen::C_WHITE, 8, false, false, true}, // dummy char 0 is for nothing
    {95, Screen::C_DGRAY, 8, false, false, true},
    {46, Screen::C_GRAY, 8, false, false, true},
    {120, Screen::C_GRAY, 8, false, false, true},
    {88, Screen::C_WHITE, 8, false, false, true}};

struct s_snow {
  unsigned int x = 0;
  unsigned int y = 0;
  unsigned int spd = 0;
  unsigned int spdcounter = 0;
};

inline s_snow SNOWFLAKES[MAXSNOW];
class Snow {
public:
  static void calc_new_flake(int i);
  static void init_bg_snow();
  static void inc_snow_bg(unsigned intx, unsigned int y);
  static void calc_bg_snow();
  static void draw_bg_snow();
};
} // namespace BackgroundSnow
#endif
