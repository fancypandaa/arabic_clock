#include "clock_digital.h"
#include "common.h"
#include "screen.h"
#include <cstdlib>
#include <iostream>
namespace ClockDigital {
std::string CLOCK_DIGITS[MAXDIGITDESIGNS][12][6]{
    {{"  ╱█ ", " ╱ █ ", "   █ ", "   █ ", "   █ ", "   █ "},
     {" ████ ", "    ╱ ", "   ╱  ", "  ╱   ", " ╱    ", " ████ "},
     {" █████ ", "     ╱ ", "    ╱  ", "    ╲  ", "     ╲ ", " █████ "},
     {"    ╱█ ", "   ╱ █ ", "  ╱  █ ", " ╱   █ ", " █████ ", "     █ "},
     {" █▀▀▀▀ ", " █     ", " █▄▄▄▄ ", "     █ ", "     █ ", " █▄▄▄█ "},
     {" █▀▀▀▀▀ ", " █      ", " █▄▄▄▄▄ ", " █    █ ", " █    █ ", " █▄▄▄▄█ "},
     {" ▆▆▆▆▆ ", "     ╱ ", "    ╱  ", "  ▆▆▆  ", "  ╱    ", " 🮅🮅    "},
     {" ████ ", " ╲  ╱ ", "  ╲╱  ", "  ╱╲  ", " ╱  ╲ ", " ████ "},
     {" █▀▀▀█ ", " █   █ ", " █▄▄▄█ ", "     █ ", " █▀▎ █ ", " █▄▄▄█ "},
     {"  ⏜    ", " ⎛   ⎞ ", " █   █ ", " █   █ ", " ⎝   ⎠ ", "  ⏝    "},
     {"  ", "    ", "    ", "    ", "    ", "    "}}};
std::vector<std::string> ArabicClock::number_draw(int num) {
  std::vector<std::string> lines;

  switch (num) {
  case 1:
    lines.push_back(" ╱█");
    lines.push_back("╱ █");
    lines.push_back("  █");
    lines.push_back("  █");
    lines.push_back("  █");
    lines.push_back("  █");
    break;
  case 2:
    lines.push_back("████");
    lines.push_back("   ╱");
    lines.push_back("  ╱ ");
    lines.push_back(" ╱  ");
    lines.push_back("╱   ");
    lines.push_back("████");
    break;
  case 3:
    lines.push_back("█████");
    lines.push_back("    ╱");
    lines.push_back("   ╱ ");
    lines.push_back("   ╲ ");
    lines.push_back("    ╲");
    lines.push_back("█████");
    break;
  case 4:
    lines.push_back("   ╱█");
    lines.push_back("  ╱ █");
    lines.push_back(" ╱  █");
    lines.push_back("╱   █");
    lines.push_back("█████");
    lines.push_back("    █");
    break;
  case 5:
    lines.push_back("█▀▀▀▀");
    lines.push_back("█    ");
    lines.push_back("█▄▄▄▄");
    lines.push_back("    █");
    lines.push_back("    █");
    lines.push_back("█▄▄▄█");
    break;
  case 6:
    lines.push_back("█▀▀▀▀▀");
    lines.push_back("█     ");
    lines.push_back("█▄▄▄▄▄");
    lines.push_back("█    █");
    lines.push_back("█    █");
    lines.push_back("█▄▄▄▄█");
    break;
  case 7:
    lines.push_back("▆▆▆▆▆");
    lines.push_back("    ╱");
    lines.push_back("   ╱ ");
    lines.push_back(" ▆▆▆ ");
    lines.push_back(" ╱   ");
    lines.push_back("🮅🮅   ");
    break;
  case 8:
    lines.push_back("████");
    lines.push_back("╲  ╱");
    lines.push_back(" ╲╱ ");
    lines.push_back(" ╱╲ ");
    lines.push_back("╱  ╲");
    lines.push_back("████");
    break;
  case 9:
    lines.push_back("█▀▀▀█");
    lines.push_back("█   █");
    lines.push_back("█▄▄▄█");
    lines.push_back("    █");
    lines.push_back("█▀▎ █");
    lines.push_back("█▄▄▄█");
    break;
  case 0:
    lines.push_back(" ⏜   ");
    lines.push_back("⎛   ⎞");
    lines.push_back("█   █");
    lines.push_back("█   █");
    lines.push_back("⎝   ⎠");
    lines.push_back(" ⏝   ");
    break;
  default:
    // Show something for debugging
    lines.push_back("█");
    lines.push_back("█");
    lines.push_back("█");
    lines.push_back("█");
    lines.push_back("█");
    lines.push_back("█");
    break;
  }
  return lines;
}
void ArabicClock::init_clock_digital() {
  ACTDIGITDESIGN = rand() % MAXDIGITDESIGNS;
  do {
    CLOCKCOLOR = rand() % 8;
  } while (CLOCKCOLOR == AVOIDCLOCKCOLOR || CLOCKCOLOR == 0);
}
void ArabicClock::draw_digit(int layer, int x, int y, int digit,
                             Screen::s_simplechar drawChar) {
  auto lines = number_draw(digit);
  /* for (int row = 0; row < lines.size(); row++) {
     for (int col = 0; col < lines[row].length(); col++) {
       char c = lines[row][col];
       if (c != ' ') {
         Screen::s_simplechar ch = {c, 7, true, true, false};
         Screen::ScreenJobs::charXY(CLOCKLAYER, x + col, y + row, ch);
       }
     }
   }
   */
  for (int i = 0; i < lines.size(); i++) {
    textColor(drawChar.bcol);
    std::cout << "\033[" << (y + i) << ";" << x << "H" << lines[i];
    textReset();
    // Screen::ScreenJobs::stringXY(layer, x, y, drawChar, lines[i]);
  }
}

void ArabicClock::draw_clock(int cx, int cy) {
  int startX = cx, startY = cy;
  int timeX = startX + 4;
  int timeY = startY + 6;
  int hour = Common::ACT_HOUR[0], minute = Common::ACT_MIN[0],
      second = Common::ACT_SEC[0];
  draw_digit(CLOCKLAYER, timeX, timeY, hour / 10, CLOCKCHAR);
  draw_digit(CLOCKLAYER, timeX + 6, timeY, hour % 10, CLOCKCHAR);

  std::cout << "\033[" << (timeY + 1) << ";" << (timeX + 12) << "H▌";
  std::cout << "\033[" << (timeY + 3) << ";" << (timeX + 12) << "H▌";
  /*
  Screen::s_simplechar colonChar = {':', 7, true, true, false};
  Screen::ScreenJobs::charXY(CLOCKLAYER, startX + 12, startY + 1, colonChar);
  Screen::ScreenJobs::charXY(CLOCKLAYER, startX + 12, startY + 3, colonChar);
  */
  draw_digit(CLOCKLAYER, timeX + 14, timeY, minute / 10, CLOCKCHAR);
  draw_digit(CLOCKLAYER, timeX + 20, timeY, minute % 10, CLOCKCHAR);

  std::cout << "\033[" << (timeY + 1) << ";" << (timeX + 26) << "H▌";
  std::cout << "\033[" << (timeY + 3) << ";" << (timeX + 26) << "H▌";

  draw_digit(CLOCKLAYER, timeX + 28, timeY, second / 10, CLOCKCHAR);
  draw_digit(CLOCKLAYER, timeX + 34, timeY, second % 10, CLOCKCHAR);
  std::cout.flush();

  /*CLOCKCHAR.bcol = CLOCKCOLOR;
  Screen::ScreenJobs::clearLayer(CLOCKLAYER, CLOCKCLEAR);

  int digitWidth = 0;
  for (int d = 0; d < 12; d++) {
    for (int i = 0; i < 6; i++) {
      if (CLOCK_DIGITS[ACTDIGITDESIGN][d][i].length() > digitWidth) {
        digitWidth = CLOCK_DIGITS[ACTDIGITDESIGN][d][i].length();
      }
    }
  }
  int digitHeight = 6;

  for (int digit = 0; digit < 2; digit++) {
    draw_digit(CLOCKLAYER, cx + (digit * (digitWidth + 1)), cy,
               Common::ACT_TIME_STR[0][digit] - 48, CLOCKCHAR);
  }

  if (!(Common::LAST_TIME_STR[0] == Common::ACT_TIME_STR[0])) {
    colon = !colon;
  }
  if (colon) {
    draw_digit(CLOCKLAYER, cx + (2 * (digitWidth + 1)), cy, 10, CLOCKCHAR);
  }

  for (int digit = 2; digit < 4; digit++) {
    draw_digit(CLOCKLAYER, cx + (digitWidth + 1) + (digit * (digitWidth + 1)),
               cy, Common::ACT_TIME_STR[0][digit] - 48, CLOCKCHAR);
  }

  Common::LAST_TIME_STR[0] = Common::ACT_TIME_STR[0];

  int digit;

  // Hours
  for (digit = 0; digit < 2; digit++) {
    draw_digit(CLOCKLAYER, cx + (digit * 7), cy,
               Common::ACT_TIME_STR[0][digit] - '0', CLOCKCHAR);
  }

  // Blink colon
  if (Common::LAST_TIME_STR[0] != Common::ACT_TIME_STR[0]) {
    colon = !colon;
  }

  if (colon) {
    draw_digit(CLOCKLAYER, cx + (2 * 7), cy, 10, CLOCKCHAR);
  }

  // Minutes
  for (digit = 2; digit < 4; digit++) {
    draw_digit(CLOCKLAYER, cx + (digit * 7), cy,
               Common::ACT_TIME_STR[0][digit] - '0', CLOCKCHAR);
  }

  Common::LAST_TIME_STR[0] = Common::ACT_TIME_STR[0];
*/
}
} // namespace ClockDigital
