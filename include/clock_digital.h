#ifndef CLOCK_DIGITAL_H
#define CLOCK_DIGITAL_H

#include "screen.h"
#include <vector>
namespace ClockDigital {
inline const int CLOCKLAYER = 2;
inline int CLOCKCOLOR = 0, AVOIDCLOCKCOLOR = 0;
inline Screen::s_simplechar CLOCKCHAR = {32, 1, 2, true, true, false};
inline Screen::s_simplechar CLOCKCLEAR = {32,   0,   8, true,
                                          true, true}; // namespace ClockDigital
inline int ACTDIGITDESIGN = 2;
inline const int MAXDIGITDESIGNS = 1;

struct s_digital_design {
  unsigned int x;
  unsigned int y;
};
inline s_digital_design DIGIT_DESIGNS[MAXDIGITDESIGNS] = {{8, 8}};
class ArabicClock {
public:
  static void init_clock_digital();
  static std::vector<std::string> number_draw(int num);
  static void draw_digit(int layer, int px, int py, int digit,
                         Screen::s_simplechar);
  static void draw_clock(int cx, int cy);
};
} // namespace ClockDigital
#endif
