#ifndef SCREEN_H
#define SCREEN_H
#include <string>
namespace Screen {
inline constexpr float SCREEN_CHAR_ASPECT_RATIO = 2.0f;

inline constexpr int FPS = 25;
inline constexpr int FPS2MILLISEC = 1000 / FPS;

inline constexpr short MAXLAYERS = 5;

inline constexpr int MAXX = 200;
inline constexpr int MAXY = 200;

inline constexpr int C_BLACK = 0;
inline constexpr int C_RED = 1;
inline constexpr int C_GREEN = 2;
inline constexpr int C_YELLOW = 3;
inline constexpr int C_BLUE = 4;
inline constexpr int C_MAGENTA = 5;
inline constexpr int C_CYAN = 6;
inline constexpr int C_GRAY = 7;

inline constexpr int C_DGRAY = 8;
inline constexpr int C_LRED = 9;
inline constexpr int C_LGREEN = 10;
inline constexpr int C_LYELLOW = 11;
inline constexpr int C_LBLUE = 12;
inline constexpr int C_LMAGENTA = 13;
inline constexpr int C_LCYAN = 14;
inline constexpr int C_WHITE = 15;

inline constexpr int C_BGTRANS = 8;
struct simple_str {
  std::string str = " ";
  bool transpchr = true;
  bool transpcol = true;
  bool transpbcol = true;
};
struct s_simplechar {
  char chr = 32;
  unsigned short int col = 0;
  unsigned short int bcol = 8;

  bool transpchr = true;
  bool transpcol = true;
  bool transpbcol = true;
};

inline const std::string COLORS[16] = {
    "0;30", "0;31", "0;32", "0;33", "0;34", "0;35", "0;36", "0;37",
    "0;30", "0;31", "0;32", "0;33", "0;34", "0;35", "0;36", "0;37"};

inline const std::string BCOLORS[9] = {"40", "41", "42", "43", "44",
                                       "45", "46", "47", "49"};

inline int SCREENX = 0;
inline int SCREENY = 0;
inline simple_str LAYER_STR[MAXX][MAXY];

inline s_simplechar LAYER[MAXLAYERS + 1][MAXX][MAXY];

inline s_simplechar FINAL[MAXX][MAXY];

inline s_simplechar WRITECHAR = {32, 7, 8, false, false, false};

inline s_simplechar CLEARCHAR = {32, 7, 8, true, true, true};

#define clearScreen() printf("\033[H\033[J")
#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))
#define hideCursor() printf("\033[?25l");
#define showCursor() printf("\033[?25h");
#define textReset() printf("\033[0m");
#define textColor(c) printf("\033[38;5;%dm", (c))
class ScreenJobs {
public:
  static void initScreen();
  static void charXY(int layer, int x, int y, s_simplechar &s_s_char);
  static void stringXY(int layer, int x, int y, s_simplechar &s_S_char,
                       std::string s);
  static void lineXY(int layer, int x1, int y1, int x2, int y2,
                     s_simplechar &s_S_char);
  static void stringXX(int x, int y, simple_str &s_str);
  static void clearLayer(int layer, s_simplechar &s_char);
  static void clearAllLayer(s_simplechar simple_c);
  static void mergeLayers();
  static void printScreen();
};
} // namespace Screen
#endif
