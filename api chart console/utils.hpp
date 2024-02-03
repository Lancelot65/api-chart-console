#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <regex>
#include <cmath>

std::regex REPLACE_CONSECUTIVE_ZEROES(R"(0\.(0{4,})(.{4}).*)");

std::string fnum_replace_consecutive_zeroes(const std::smatch& match) {
    auto p1 = match[1].str();
    auto p2 = match[2].str();
    auto p3 = match[3].str();
    return p1 + "⦗0×" + std::to_string(p2.length()) + "⦘" + p3;
}

std::string fnum(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    if (!value || std::abs(value) >= 1) {
        oss << std::setprecision(0) << std::showpoint << value;
    }
    else {
        std::wstringstream temp_stream;
        temp_stream << std::setprecision(18) << value;
        auto formatted = std::regex_replace(temp_stream.str(), R"(0\.(0{4,})(.{4}).*)", fnum_replace_consecutive_zeroes);
        if (formatted.find("0×") != std::string::npos)
        {
            oss << formatted;
        }
        else {
            oss << std::setprecision(10) << std::showpoint << value;
        }
    }
    return oss.str();
}

std::tuple<int, int, int> hexa_to_rgb(const std::string& hex_code) {
    std::string hex_code_cleaned = hex_code.substr(1); // Remove leading #
    int r = std::stoi(hex_code_cleaned.substr(0, 2), nullptr, 16);
    int g = std::stoi(hex_code_cleaned.substr(2, 2), nullptr, 16);
    int b = std::stoi(hex_code_cleaned.substr(4, 2), nullptr, 16);
    return std::make_tuple(r, g, b);
}

#endif //! 