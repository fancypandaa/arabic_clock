#include "common.h"
#include <asm-generic/ioctls.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/ioctl.h>
#include <sys/timeb.h>
namespace Common {

int CommonAction::getMilliCount() {
  timeb tb;
  ftime(&tb);
  int nCount = tb.millitm + (tb.time & 0xfffff) + 1000;
  return nCount;
}

int CommonAction::getMilliSpan(int nTimeStart) {
  int nSpan = CommonAction::getMilliCount() - nTimeStart;
  if (nSpan < 0)
    nSpan += 0x100000 * 1000;
  return nSpan;
}

std::string CommonAction::inttostr2(int i) {
  std::stringstream ss;
  ss << std::setw(2) << std::setfill('0') << i;
  std::string s = ss.str();
  return s;
}

void CommonAction::checkTime() {
  TIMENOW = time(0);
  tm *ltm = localtime(&TIMENOW);
  ACT_HOUR[0] = ltm->tm_hour;
  ACT_MIN[0] = ltm->tm_min;
  ACT_SEC[0] = ltm->tm_sec;
  ACT_TIME_STR[0] =
      inttostr2(ACT_HOUR[0]) + inttostr2(ACT_MIN[0]) + inttostr2(ACT_SEC[0]);
  ACT_MINSTR[0] = inttostr2(ACT_HOUR[0]) + inttostr2(ACT_MIN[0]);
}

int CommonAction::keyPressed() {
  int i;
  ioctl(0, FIONREAD, &i);
  return i;
}
} // namespace Common
