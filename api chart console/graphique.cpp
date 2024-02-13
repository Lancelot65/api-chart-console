#include "graphique.hpp"

sf::Color DARK = sf::Color(0, 0, 0);
sf::Color WHITE = sf::Color(238, 238, 238);
sf::Color RED = sf::Color(242, 54, 69);
sf::Color GREEN = sf::Color(8, 153, 129);

static bool collision_point(sf::RectangleShape& rect, float x_point, float y_point)
{
    return (rect.getPosition().x < x_point && x_point < rect.getPosition().x + rect.getSize().x && rect.getPosition().y < y_point && y_point < rect.getPosition().y + rect.getSize().y);
}


graphique::graphique(float x, float y, float width, float height, OHLCV _data) :
    data(_data)
    {
        this->rect.setPosition(sf::Vector2f(x, y));
        this->rect.setSize(sf::Vector2f(width, height));
        this->rect.setFillColor(WHITE);
        this->create_candles();
        this->shadow.setPrimitiveType(sf::Lines);
    }

const void graphique::show(sf::RenderWindow& window)
{
    window.draw(this->rect);
    window.draw(this->shadow);
    for (auto &candle : this->body)
    {
        window.draw(candle);
    }
}

void graphique::set_size(float x, float y, float width, float height)
{
    this->rect.setPosition(sf::Vector2f(x, y));
    this->rect.setSize(sf::Vector2f(width, height));
    this->create_candles();
}

bool graphique::collide(float x, float y)
{
    if (collision_point(this->rect, x, y))
    {
        return true;
    }
    return false;
}

void graphique::create_candles()
{
    if (this->rect.getSize().x != this->last_width)
    {
        this->last_width = this->rect.getSize().x;
        float x_frame = this->rect.getSize().x - 20;
        float y_frame = this->rect.getSize().y - 20;

        this->body.clear();
        this->shadow.clear();

        const double max = *std::max_element(this->data.high.begin(), this->data.high.end());
        const double min = *std::min_element(this->data.low.begin(), this->data.low.end());
        const double diff_opp = max - min;

        const double size = this->data.open.size();

        int largeur = (x_frame / size) / 1.5;

        if ((int)largeur % 2 == 0) {
            largeur = largeur - 1;
        }

        for (size_t i = 0; i < size; ++i) {
            auto color = this->data.open[i] < this->data.close[i] ? sf::Color(8, 153, 129) : sf::Color(242, 54, 69);

            double hauteur = (this->data.close[i] - this->data.open[i]) * (y_frame / diff_opp);
            int x = i * (x_frame / size) + (x_frame / size) / 2 - largeur / 2 + 10;
            double baseY = y_frame - ((this->data.open[i] + this->data.close[i]) / 2) * ((y_frame) / diff_opp) - hauteur / 2;
            double y = baseY + (min / (diff_opp)) * (y_frame)+10;

            int plus = 1 + (largeur - 1) / 2;

            this->shadow.append(sf::Vertex(sf::Vector2f(x + plus, (y_frame)-((this->data.high[i] - min) * (y_frame / diff_opp)) + 10), color));
            this->shadow.append(sf::Vertex(sf::Vector2f(x + plus, (y_frame)-((this->data.low[i] - min) * (y_frame / diff_opp)) + 10), color));

            if (hauteur < 0 && hauteur > -1) {
                hauteur = -1;
            }
            else if (hauteur > 0 && hauteur < 1) {
                hauteur = 1;
            }

            sf::RectangleShape rectangle(sf::Vector2f(largeur, hauteur));
            rectangle.setPosition(x, y);
            rectangle.setFillColor(color);
            this->body.push_back(rectangle);
        }
    }
}