
#ifndef COMMON_H
#define COMMON_H

#include <string>
namespace Common {
inline time_t TIMENOW;
inline const int MAXTIMEZONES = 1;
inline int ACT_HOUR[MAXTIMEZONES], ACT_MIN[MAXTIMEZONES], ACT_SEC[MAXTIMEZONES];
inline std::string ACT_TIME_STR[MAXTIMEZONES], ACT_MINSTR[MAXTIMEZONES];
inline std::string LAST_TIME_STR[MAXTIMEZONES], LAST_MINSTR[MAXTIMEZONES];
class CommonAction {
public:
  static int getMilliCount();
  static int getMilliSpan(int nTimeStart);
  static int keyPressed();
  static std::string inttostr2(int i);
  static void checkTime();
};
} // namespace Common
#endif
