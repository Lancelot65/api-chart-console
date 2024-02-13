#ifndef Chart_HPP
#define Chart_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <outil_requete.hpp>

struct MEMORY_BACKTEST
{
	std::vector<double> pnl;
	std::vector<double> _long;
	std::vector<double> _short;
	std::vector<__int64> time_pnl;
	std::vector<__int64> time_long;
	std::vector<__int64> time_short;
	std::vector<double> fees_pnl;
	std::vector<double> fees_long;
	std::vector<double> fees_short;
	std::vector<double> evolution_capital;
};

struct POSITION_INDICE {
	std::vector<int> open_long;
	std::vector<int> close_long;
	std::vector<int> open_short;
	std::vector<int> close_short;
};


using map_ind = std::map<std::string, std::vector<double>>;


static POSITION_INDICE default_position_indice;

class Chart
{
private:
    OHLCV ohlcv;
    map_ind indicateurs;
    std::string timeframe;
    std::string symbol;
    POSITION_INDICE position_indice;
public:
    Chart(OHLCV& _ohlcv, std::string const& _timeframe, std::string const& _symbol, map_ind const& _indicateurs = map_ind(), POSITION_INDICE _position_indice = default_position_indice);

    void reticule(sf::VertexArray* cursor, sf::RenderWindow& window, bool resize = false);

    void drawCandles(std::vector<sf::RectangleShape>* rectangles, sf::VertexArray* high_low, sf::RenderWindow& window);
    void drawIndicator(std::vector<sf::VertexArray>* curves, sf::RenderWindow& window, map_ind& data_indicator);
    void drawPosition(POSITION_INDICE& data, std::vector<sf::ConvexShape>* triangles, sf::RenderWindow& window);

    void loop();
};

#endif