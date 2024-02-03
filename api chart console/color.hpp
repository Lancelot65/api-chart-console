#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <sstream>
#include <map>
#include <functional>
#include <tuple>

std::wstring color(std::wstring text, std::string value);
std::wstring color(std::wstring text, std::tuple<int, int, int> color_tuple);

#endif
