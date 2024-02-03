#ifndef Y_AXIS_HPP
#define Y_AXIS_HPP

#include "constant.hpp"
#include "candle.hpp"
#include "color.hpp"
#include "utils.hpp"
#include "chart_data.hpp"

#include <tuple>
#include <string>
#include <cmath>

class YAxis
{
private:
    ChartData chart_data;
public:
    std::tuple<float, float, float, float> price_to_heights(Candle candle)
    {
        ChartData chart_data_ = this->chart_data;
        int height = chart_data.getHeight();

        CandleSet candle_set = this->chart_data.getVisible_candle_set();

        double min_open = (candle.getOpen() < candle.getClose() ? candle.getOpen() : candle.getClose());
        double max_open = (candle.getOpen() > candle.getClose() ? candle.getOpen() : candle.getClose());

        double min_value = candle_set.getMin_price();

        double diff = (candle_set.getMax_price() - min_value) || 1;

        return std::make_tuple
        (
            (candle.getHigh() - min_value) / diff * height,
            (candle.getLow() - min_value) / diff * height,
            (max_open - min_value) / diff * height,
            (min_open - min_value) / diff * height
        );

    }

    std::wstring render_line(int y, std::vector<std::tuple<int, int, int>> & highlights)
    {
        return (y % Y_AXIS_SPACING != 0) ? render_empty(y) : _render_tick(y, {});
    }

    std::wstring render_line(int y, std::vector<std::string>& highlights)
    {
        return (y % Y_AXIS_SPACING != 0) ? render_empty(y, highlights) : _render_tick(y, highlights);
    }

    std::wstring _round_price(float value)
    {
        if (Y_AXIS_ROUND_MULTIPLIER > 0.0f)
        {
            float multiplier = Y_AXIS_ROUND_MULTIPLIER;
            if (Y_AXIS_ROUND_DIR == "down")
            {
                value = std::floor(value * multiplier) / multiplier;
            }
            else
            {
                value = std::ceil(value * multiplier) / multiplier;
            }
        }

        return fnum(value);
    }


};

#endif

/*

            if constants.Y_AXIS_ROUND_DIR == "down":
                value = fn_down(value * multiplier) / multiplier
            else:
                value = fn_up(value * multiplier) / multiplier
        return fnum(value)

    def _render_price(self, y: float, highlights: Dict[str, str | Tuple[int, int, int]]) -> Tuple[bool, str]:
        chart_data = self.chart_data
        min_value = chart_data.visible_candle_set.min_price
        max_value = chart_data.visible_candle_set.max_price
        height = chart_data.height

        cell_min_length = constants.CHAR_PRECISION + constants.DEC_PRECISION + 1
        price = self._round_price(min_value + (y * (max_value - min_value) / height))
        price_upper = self._round_price(min_value + ((y + 1) * (max_value - min_value) / height))

        has_special_price = False
        custom_color: str | Tuple[int, int, int] = ""

        for target_price, target_color in highlights.items():
            if not (price <= target_price < price_upper):
                continue
            price = target_price
            has_special_price = True
            custom_color = target_color
            break

        price = (
            f" {color(f'├ {price:<{cell_min_length}}', custom_color)}"
            if constants.Y_AXIS_ON_THE_RIGHT
            else f"{color(f'{price:<{cell_min_length}} ┤', custom_color)}{' ' * constants.MARGIN_RIGHT}"
        )

        return has_special_price, price

    def render_empty(
        self, y: float | None = None, highlights: Dict[str, str | Tuple[int, int, int]] | None = None
    ) -> str:
        if highlights and y:
            has_special_price, price = self._render_price(y, highlights)
            if has_special_price:
                return price

        if constants.Y_AXIS_ON_THE_RIGHT:
            return " │"

        cell = " " * (constants.CHAR_PRECISION + constants.DEC_PRECISION + 2)
        margin = " " * constants.MARGIN_RIGHT
        return f"{cell}│{margin}"

    def _render_tick(self, y: int, highlights: Dict[str, str | Tuple[int, int, int]]) -> str:
        _, price = self._render_price(y, highlights)
        return price*/