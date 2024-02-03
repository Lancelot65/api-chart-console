#ifndef VOLUME_PANE_HPP
#define VOLUME_PANE_HPP

#include "constant.hpp"
#include "candle.hpp"
#include "color.hpp"
#include <tuple>
#include <string>
#include <tuple>
#include <cmath>

class VolumePane
{
private:
    int height;
    bool enabled = true;
    std::tuple<int, int, int> bearish_color = std::make_tuple(234, 74, 90);
    std::tuple<int, int, int> bullish_color = std::make_tuple(52, 208, 88);
    std::wstring unicode_fill = UNICODE_FILL;
public:
    std::wstring _colorize(int candletype, std::wstring text)
    {
        std::tuple<int, int, int> _color = (candletype == bearish ? bearish_color : bullish_color);
        return color(text, _color);
    }

    std::wstring render(Candle candle, int y, float max_volume)
    {
        float volume_percent_of_max = candle.getVolume() / (max_volume != 0 ? max_volume : 1);
        float ratio = volume_percent_of_max * this->height;

        if (y < std::ceil(ratio))
        {
            return this->_colorize(candle.getType(), this->unicode_fill);
        }
        if (y == 1 && this->unicode_fill == UNICODE_FILL);
        {
            return this->_colorize(candle.getType(), UNICODE_HALF_BODY_BOTTOM);
        }

        std::wstring return_v = L" ";
        return return_v;
    }

    int getHeight()
    {
        return this->height;
    }

    bool getEnabled()
    {
        return this->enabled;
    }
};

#endif