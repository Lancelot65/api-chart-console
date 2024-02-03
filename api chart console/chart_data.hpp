#ifndef CHART_DATA_HPP
#define CHART_DATA_HPP

#include "constant.hpp"
#include "candle.hpp"
#include "candle_set.hpp"
#include "volume_pane.hpp"
#include <windows.h>

COORD get_terminal_size() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD size;
    size.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    size.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return size;
}

struct TERMINAL_SIZE
{
    int x;
    int y;
};


class ChartData
{
private:
    int height;
    TERMINAL_SIZE terminal_size;
    int width;


    CandleSet main_candle_set;
    CandleSet visible_candle_set;
public:

    ChartData(Candles candles, int width = 0, int height = 0)
    {
        this->main_candle_set.set_candles(candles);

        if (width == 0 || height == 0)
        {
            COORD size = get_terminal_size();
            width = size.X;
            height = size.Y;
            
        }
        this->set_size(width, height);

        this->compute_visible_candles();
    }

    void set_size(int width, int height)
    {
        this->terminal_size.x = width;
        this->terminal_size.y = height;
        this->width = width;
        this->height = height;
    }

    void compute_height(VolumePane volume_pane)
    {
        bool volume_pane_height = (volume_pane.getEnabled() ? volume_pane.getHeight() : 0);
        this->height = (int)this->terminal_size.y - MARGIN_TOP - HEIGHT - volume_pane_height;
    }

    void compute_visible_candles()
    {
        int nb_visible_candles = this->width - WIDTH;
        if (!Y_AXIS_ON_THE_RIGHT)
        {
            nb_visible_candles -= MARGIN_RIGHT;
        }

        Candles temp(this->main_candle_set.getCandles().end() - nb_visible_candles, this->main_candle_set.getCandles().end());

        this->visible_candle_set.set_candles(temp); // cree function resize candles
    }

    void reset_candles()
    {
        this->main_candle_set.reset();
        this->visible_candle_set.reset();
    }

    void add_candles(Candles candles)
    {
        Candles temp;
        this->main_candle_set.add_candles(candles);
        this->visible_candle_set.reset();
    }

    int getHeight()
    {
        return this->height;
    }

    int getWidth()
    {
        return this->width;
    }

    CandleSet getVisible_candle_set()
    {
        return this->visible_candle_set;
    }
};

#endif //!