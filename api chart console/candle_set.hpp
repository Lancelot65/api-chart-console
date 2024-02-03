#ifndef  CANDLE_SET_HPP
#define CANDLE_SET_HPP

#include "candle.hpp"
#include <limits>

class CandleSet
{
private:
    Candles candles;
    float min_price = 0.0f;
    float max_price = 0.0f;
    float min_volume = 0.0f;
    float max_volume = 0.0f;
    float variation = 0.0f;
    float average = 0.0f;
    float last_price = 0.0f;
    float cumulative_volume = 0.0f;

    CandleSet()
    {
        this->_compute_all();
    }

    void _compute_all()
    {
        if (this->candles.empty())
        {
            return;
        }

        Candles _candles = this->candles;

        float open_value = _candles[0].getOpen();
        
        float close_value = candles.back().getClose();
        this->last_price = close_value;

        float cumulative_volume = 0.0f;
        float average = 0.0f;
        float max_price = 0.0f;
        float min_price = std::numeric_limits<float>::infinity();
        float max_volume = 0.0f;
        float min_volume = 0.0f;

        
        for (size_t i = 0; i < _candles.size(); i++)
        {
            cumulative_volume += _candles[i].getVolume();
            average += _candles[i].getClose();
            if (_candles[i].getHigh() > max_price)
            {
                max_price = _candles[i].getHigh();
            }
            if (_candles[i].getLow() < min_price)
            {
                min_price = _candles[i].getLow();
            }
            if (_candles[i].getVolume() > max_volume)
            {
                max_volume = _candles[i].getVolume();
            }
            else if (_candles[i].getVolume() < min_volume)
            {
                min_volume = _candles[i].getVolume();
            }
        }

        this->cumulative_volume = cumulative_volume;
        this->average = average / _candles.size();
        this->max_price = max_price;
        this->min_price = min_price;
        this->max_volume = max_volume;
        this->min_volume = min_volume;



    }

    void add_candles(Candles _candles)
    {
        this->candles.insert(this->candles.end(), _candles.begin(), _candles.end());
        this->_compute_all();
        return;

    }

    void set_candles(Candles _candles)
    {
        this->candles = _candles;
        this->_compute_all();
        return;
    }


};
    

#endif // ! CANDLES_HPP
