#include "background_snow.h"
#include "clock_digital.h"
#include "common.h"
#include "screen.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>
using namespace std;
typedef void (*backgrounds)();

backgrounds background[][3] = {{BackgroundSnow::Snow::init_bg_snow,
                                BackgroundSnow::Snow::calc_bg_snow,
                                BackgroundSnow::Snow::draw_bg_snow}};

const int BG_EFFECTNO = 9;
int ACT_BG_EFFECT = 3;

void init_all() {
  int i;
  Screen::ScreenJobs::initScreen();
  clearScreen();
  Screen::ScreenJobs::clearAllLayer(Screen::CLEARCHAR);

  // ACT_BG_EFFECT = rand() % BG_EFFECTNO;
  ACT_BG_EFFECT = 0;
  background[ACT_BG_EFFECT][0]();
  background[ACT_BG_EFFECT][1]();
  background[ACT_BG_EFFECT][2]();
}
int main() {
  system("stty raw -echo");
  hideCursor();
  char ch = 0;
  bool snowForeground = false;
  srand(Common::CommonAction::getMilliCount());
  ClockDigital::ArabicClock::init_clock_digital();
  init_all();
  int nTimeElapsed = 0;
  Common::CommonAction::checkTime();
  Common::LAST_MINSTR[0] = Common::ACT_MINSTR[0];
  while (ch != 27 && ch != 113 && ch != 120) {
    int nTimeStart = Common::CommonAction::getMilliCount();
    Common::CommonAction::checkTime();
    if (Common::LAST_MINSTR[0] != Common::ACT_MINSTR[0]) {
      ClockDigital::ArabicClock::init_clock_digital();
      init_all();
      ClockDigital::ArabicClock::draw_clock(
          (Screen::SCREENX -
           (ClockDigital::DIGIT_DESIGNS[ClockDigital::ACTDIGITDESIGN].x * 5)) /
              2,
          (Screen::SCREENY -
           ClockDigital::DIGIT_DESIGNS[ClockDigital::ACTDIGITDESIGN].y) /
              2);
    }
    background[ACT_BG_EFFECT][1]();
    background[ACT_BG_EFFECT][2]();
    Screen::ScreenJobs::mergeLayers();
    Screen::ScreenJobs::printScreen();
    // ClockDigital::ArabicClock::draw_clock(
    // Common::ACT_HOUR[0], Common::ACT_MIN[0], Common::ACT_SEC[0]);

    ClockDigital::ArabicClock::draw_clock(
        (Screen::SCREENX -
         (ClockDigital::DIGIT_DESIGNS[ClockDigital::ACTDIGITDESIGN].x * 5)) /
            2,
        (Screen::SCREENY -
         ClockDigital::DIGIT_DESIGNS[ClockDigital::ACTDIGITDESIGN].y) /
            2);
    if (Common::CommonAction::keyPressed()) {
      ch = getchar();
      switch (ch) {
      case 27:
        cout << endl << "ESC" << ch << endl;
        exit(0);
        break;
      case 68:
        cout << "Left";
        break;
      case 67:
        cout << "Right";
        break;
      case 102:
        init_all();
        break;
      }
    }
    Common::LAST_MINSTR[0] = Common::ACT_MINSTR[0];
    nTimeElapsed = Common::CommonAction::getMilliSpan(nTimeStart);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(Screen::FPS2MILLISEC - nTimeElapsed));
  }
  system("stty cooked echo");
  textReset();
  showCursor();
  return 0;
}
