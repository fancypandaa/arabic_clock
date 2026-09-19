#ifndef CLOCK_DIGITS_H
#define CLOCK_DIGITS_H

#include <string>

namespace ClockDigits {
constexpr int DIGIT_HEIGHT = 8;
constexpr int DIGIT_WIDTH = 8;
constexpr int DIGIT_COUNT = 12;

std::string getDigitLine(int digit, int row);
void printDigit(int digit);
void printNumber(const std::string &number);
void printClock(int hour, int minute, bool showSeconds = false, int second = 0);

} // namespace ClockDigits

#endif
