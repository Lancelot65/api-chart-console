#ifndef CANDLE_HPP
#define CANDLE_HPP

#include <vector>
#include <string>
#include <sstream>


#define bearish 0
#define bullish 1


class Candle
{
private:
    double open;
    double high;
    double low;
    double close;
    double volume;
    std::string timestamp;
    int type;

public:
    Candle(double _open, double _high, double _low, double _close, double _volume, std::string _timestamp) :
        open(_open), high(_high), low(_low), close(_close), volume(_volume), timestamp(_timestamp),
        type(_open < _close ? bullish : bearish) {}


    Candle(const Candle& copy) :
        open(copy.open), high(copy.high), low(copy.low), close(copy.close),
        volume(copy.volume), timestamp(copy.timestamp), type(copy.type) {}

    bool operator==(const Candle& other) const {
        return (open == other.open && high == other.high && low == other.low &&
            close == other.close && volume == other.volume &&
            timestamp == other.timestamp && type == other.type);
    }

    std::string to_tstring() const {
        std::stringstream ss;
        ss << "type : Candle\nopen = " << open << ", low = " << low;
        ss << ", high = " << high << ", close = " << close << ", volume = ";
        ss << volume << ", timestamp = " << timestamp << ", type = " << (type == bearish ? "bearish" : "bullish");
        return ss.str();
    }

    double getOpen() const {
        return open;
    }

    double getHigh() const {
        return high;
    }

    double getLow() const {
        return low;
    }

    double getClose() const {
        return close;
    }

    double getVolume() const {
        return volume;
    }

    std::string getTimestamp() const {
        return timestamp;
    }

    int getType() const {
        return type;
    }
};

using Candles = std::vector<Candle>;
using empty_candle = Candles;

#endif