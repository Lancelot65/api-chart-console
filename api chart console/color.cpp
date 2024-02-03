#include "color.hpp"

static std::wstring blue(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[94m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring bold(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[01m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring cyan(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[96m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring grey(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[90m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring green(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[92m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring magenta(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[95m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring red(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[91m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring white(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[97m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring yellow(std::wstring value)
{
    std::wstringstream ss;
    ss << L"\033[93m" << value << L"\033[00m";
    return ss.str();
}

static std::wstring color_perso(std::wstring value, int r, int g, int b)
{
    std::wstringstream ss;
    ss << L"\033[38; 2; " << r << L"; " << g << L"; " << b << L"m" << value << L"\033[00m";
    return ss.str();
}

static std::map<std::string, std::function<std::wstring(std::wstring)>> colors = {
    {"blue", blue},
    {"bold", bold},
    {"cyan", cyan},
    {"grey", grey},
    {"green", green},
    {"magenta", magenta},
    {"red", red},
    {"white", white},
    {"yellow", yellow}
};

std::wstring color(std::wstring text, std::string value)
{
    if (value.empty())
    {
        return text;
    }

    if (colors.find(value) != colors.end())
    {
        return colors[value](text);
    }

    std::wstring wstr(value.length(), L' ');
    std::copy(value.begin(), value.end(), wstr.begin());

    std::wstringstream ss;
    ss << L"\033[" << wstr << text << L"\033[00m";
    return ss.str();
}

std::wstring color(std::wstring text, std::tuple<int, int, int> color_tuple)
{
    return color_perso(text, std::get<0>(color_tuple), std::get<1>(color_tuple), std::get<2>(color_tuple));
}