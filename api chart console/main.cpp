#include <iostream>
#include "constant.hpp"
#include <io.h>
#include <fcntl.h>
#include "color.hpp"

// https://github.com/BoboTiG/py-candlestick-chart.git

class UnicodeOutput {
public:
    UnicodeOutput() {
        _prevMode = _setmode(_fileno(stdout), _O_U16TEXT);
    }

    ~UnicodeOutput() {
        _setmode(_fileno(stdout), _prevMode);
    }

private:
    int _prevMode;
};

int wmain(int argc, wchar_t* argv[])
{
    UnicodeOutput unicodeOutput;

    std::wcout << color(UNICODE_BODY, "red") << std::endl;


    return 0;
}