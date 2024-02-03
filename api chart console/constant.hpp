#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>

namespace LABLELS
{
    std::string average = "Avg.";
    std::string currency = "";
    std::string highest = "Highest";
    std::string lowest = "Lowest";
    std::string price = "Price";
    std::string variation = "Var.";
    std::string volume = "Cum. Vol.";
}


int MARGIN_TOP = 3;
int MARGIN_RIGHT = 4;
int CHAR_PRECISION = 6;
int DEC_PRECISION = 5;
int WIDTH = CHAR_PRECISION + 1 + DEC_PRECISION + MARGIN_RIGHT;
int HEIGHT = 2;
int Y_AXIS_SPACING = 4;

int PRECISION = 2;
int PRECISION_SMALL = 4;
    
std::wstring UNICODE_BODY = L"┃";
std::wstring UNICODE_BOTTOM = L"╿";
std::wstring UNICODE_HALF_BODY_BOTTOM = L"╻";
std::wstring UNICODE_HALF_BODY_TOP = L"╹";
std::wstring UNICODE_FILL = L"┃";
std::wstring UNICODE_TOP = L"╽";
std::wstring UNICODE_VOID = L" ";
std::wstring UNICODE_WICK = L"│";
std::wstring UNICODE_WICK_LOWER = L"╵";
std::wstring UNICODE_WICK_UPPER = L"╷";
float MIN_DIFF_THRESHOLD = 0.25f;
float MAX_DIFF_THRESHOLD = 0.75f;

bool Y_AXIS_ON_THE_RIGHT = false;
std::string Y_AXIS_ROUND_DIR = "down";  // Or "up"
float Y_AXIS_ROUND_MULTIPLIER = 0.0f;

#endif // CANDLESTICK_H 