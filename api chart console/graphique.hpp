#ifndef GRAPHIQUE_HPP
#define GRAPHIQUE_HPP

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <outil_requete.hpp>
#include <algorithm>
#include <iostream>

struct Theme
{
    sf::Color background;
    sf::Color body_down;
    sf::Color body_up;
    sf::Color border;
};

extern Theme Dark;

class graphique
{
private:
    sf::RectangleShape rect;
    OHLCV data;

    std::vector<sf::RectangleShape> body;
    sf::VertexArray shadow;

    Theme color_theme;

    int last_width = 0;
public:
    graphique(float x, float y, float width, float height, OHLCV _data);

    const void show(sf::RenderWindow& window);

    void set_size(float x, float y, float width, float height);

    bool collide(float x, float y);

    void create_candles();

    void set_theme(Theme color_theme);
};



#endif // !GRAPHIQUE_HPP
