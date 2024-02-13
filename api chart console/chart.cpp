#include "chart.hpp"


Chart::Chart(OHLCV& _ohlcv, std::string const& _timeframe, std::string const& _symbol, map_ind const& _indicateurs, POSITION_INDICE _position_indice) :
    ohlcv(_ohlcv), indicateurs(_indicateurs), timeframe(_timeframe), symbol(_symbol), position_indice(_position_indice)
{
    this->loop();
}

void Chart::drawCandles(std::vector<sf::RectangleShape>* rectangles, sf::VertexArray* high_low, sf::RenderWindow& window) {
    float x_frame = window.getSize().x - 20;
    float y_frame = window.getSize().y - 20;

    rectangles->clear();
    high_low->clear();

    const double max = *std::max_element(this->ohlcv.high.begin(), this->ohlcv.high.end());
    const double min = *std::min_element(this->ohlcv.low.begin(), this->ohlcv.low.end());
    const double diff_opp = max - min;

    const double size = this->ohlcv.open.size();

    int largeur = (x_frame / size) / 1.5;

    if ((int)largeur % 2 == 0) {
        largeur = largeur - 1;
    }

    for (size_t i = 0; i < size; ++i) {
        auto color = this->ohlcv.open[i] < this->ohlcv.close[i] ? sf::Color(8, 153, 129) : sf::Color(242, 54, 69);

        double hauteur = (this->ohlcv.close[i] - this->ohlcv.open[i]) * (y_frame / diff_opp);
        int x = i * (x_frame / size) + (x_frame / size) / 2 - largeur / 2 + 10;
        double baseY = y_frame - ((this->ohlcv.open[i] + this->ohlcv.close[i]) / 2) * ((y_frame) / diff_opp) - hauteur / 2;
        double y = baseY + (min / (diff_opp)) * (y_frame)+10;

        int plus = 1 + (largeur - 1) / 2;

        high_low->append(sf::Vertex(sf::Vector2f(x + plus, (y_frame)-((this->ohlcv.high[i] - min) * (y_frame / diff_opp)) + 10), color));
        high_low->append(sf::Vertex(sf::Vector2f(x + plus, (y_frame)-((this->ohlcv.low[i] - min) * (y_frame / diff_opp)) + 10), color));

        if (hauteur < 0 && hauteur > -1) {
            hauteur = -1;
        }
        else if (hauteur > 0 && hauteur < 1) {
            hauteur = 1;
        }

        sf::RectangleShape rectangle(sf::Vector2f(largeur, hauteur));
        rectangle.setPosition(x, y);
        rectangle.setFillColor(color);
        rectangles->push_back(rectangle);
    }
}

// pas yrès utile pour l'instant... -> n'indique rien
void Chart::reticule(sf::VertexArray* cursor, sf::RenderWindow& window, bool resize)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2u windowSize = window.getSize();


    if (mousePosition.x >= 0 && mousePosition.y >= 0 && mousePosition.x < windowSize.x && mousePosition.y < windowSize.y || resize)
    {
        cursor->clear();

        cursor->append(sf::Vertex(sf::Vector2f(0, mousePosition.y), sf::Color::Black));
        cursor->append(sf::Vertex(sf::Vector2f(windowSize.x, mousePosition.y), sf::Color::Black));

        cursor->append(sf::Vertex(sf::Vector2f(mousePosition.x, 0), sf::Color::Black));
        cursor->append(sf::Vertex(sf::Vector2f(mousePosition.x, windowSize.y), sf::Color::Black));
    }
}

void Chart::drawPosition(POSITION_INDICE& data, std::vector<sf::ConvexShape>* triangles, sf::RenderWindow& window)
{
    float x_frame = window.getSize().x - 20;
    float y_frame = window.getSize().y - 20;

    triangles->clear();

    const double max = *std::max_element(this->ohlcv.high.begin(), this->ohlcv.high.end());
    const double min = *std::min_element(this->ohlcv.low.begin(), this->ohlcv.low.end());
    const double diff_opp = max - min;

    const double size = this->ohlcv.open.size();

    int largeur = (x_frame / size) / 1.5;


    for (int i : data.open_long)
    {

        int x = i * ((x_frame) / size) + ((x_frame) / size) / 2 - largeur / 2 + 10;
        int plus = 1 + (largeur - 1) / 2;

        int y = (y_frame)-((this->ohlcv.low[i] - min) * (y_frame / diff_opp)) + 5 + 10;

        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(x + plus + 1, y));
        triangle.setPoint(1, sf::Vector2f(x - 10 + plus + 1, y + 20));
        triangle.setPoint(2, sf::Vector2f(x + 10 + plus + 1, y + 20));
        triangle.setFillColor(sf::Color::Green);

        triangles->push_back(triangle);
    }
    for (int i : data.close_long)
    {
        int x = i * ((x_frame) / size) + ((x_frame) / size) / 2 - largeur / 2 + 10;
        int plus = 1 + (largeur - 1) / 2;

        int y = (y_frame)-((this->ohlcv.low[i] - min) * (y_frame / diff_opp)) + 5 + 10;

        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(x + plus + 1, y));
        triangle.setPoint(1, sf::Vector2f(x - 10 + plus + 1, y + 20));
        triangle.setPoint(2, sf::Vector2f(x + 10 + plus + 1, y + 20));
        triangle.setFillColor(sf::Color::Red);

        triangles->push_back(triangle);
    }
    for (int i : data.open_short)
    {
        int x = i * ((x_frame) / size) + ((x_frame) / size) / 2 - largeur / 2 + 10;
        int plus = 1 + (largeur - 1) / 2;

        int y = (y_frame)-((this->ohlcv.high[i] - min) * (y_frame / diff_opp)) - 5 + 10;

        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(x + plus + 1, y));
        triangle.setPoint(1, sf::Vector2f(x - 10 + plus + 1, y - 20));
        triangle.setPoint(2, sf::Vector2f(x + 10 + plus + 1, y - 20));
        triangle.setFillColor(sf::Color::Green);

        triangles->push_back(triangle);
    }
    for (int i : data.close_short)
    {
        int x = i * ((x_frame) / size) + ((x_frame) / size) / 2 - largeur / 2 + 10;
        int plus = 1 + (largeur - 1) / 2;

        int y = (y_frame)-((this->ohlcv.high[i] - min) * (y_frame / diff_opp)) - 5 + 10;

        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(x + plus + 1, y));
        triangle.setPoint(1, sf::Vector2f(x - 10 + plus + 1, y - 20));
        triangle.setPoint(2, sf::Vector2f(x + 10 + plus + 1, y - 20));
        triangle.setFillColor(sf::Color::Red);

        triangles->push_back(triangle);
    }
}

void Chart::loop() {

    if (ohlcv.close.empty())
    {
        std::cerr << "OHLCV is empty" << std::endl;
        return;
    }

    sf::RenderWindow window(sf::VideoMode(800, 500), this->symbol + " " + this->timeframe);
    sf::VertexArray high_low(sf::Lines);
    std::vector<sf::RectangleShape> rectangles_views;
    std::vector<sf::VertexArray> curves;

    sf::VertexArray cursor(sf::Lines);

    std::vector<sf::ConvexShape> position;

    this->drawPosition(this->position_indice, &position, window);

    if (this->indicateurs.size() != 0)
    {
        this->drawIndicator(&curves, window, this->indicateurs);
    }

    this->drawCandles(&rectangles_views, &high_low, window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                this->drawCandles(&rectangles_views, &high_low, window);
                if (this->indicateurs.size() != 0)
                {
                    this->drawIndicator(&curves, window, this->indicateurs);
                }
                reticule(&cursor, window, true);
                this->drawPosition(position_indice, &position, window);

            }
            if (event.type == sf::Event::MouseMoved)
            {
                reticule(&cursor, window);
            }
        }

        window.clear(sf::Color(255, 255, 255));
        window.draw(high_low);

        for (auto& i : curves)
        {
            window.draw(i);
        }

        for (auto rect : rectangles_views) {
            window.draw(rect);
        }

        for (auto& i : position)
        {
            window.draw(i);
        }

        window.draw(cursor);
        window.display();
    }
}

void Chart::drawIndicator(std::vector<sf::VertexArray>* curves, sf::RenderWindow& window, map_ind& data_indicator)
{
    const float x_frame = window.getSize().x - 20;
    const float y_frame = window.getSize().y - 20;

    const double max = *std::max_element(this->ohlcv.high.begin(), this->ohlcv.high.end());
    const double min = *std::min_element(this->ohlcv.low.begin(), this->ohlcv.low.end());
    const double diff_opp = max - min;

    const double size = this->ohlcv.open.size();

    int largeur = (x_frame / size) / 1.5;

    if ((int)largeur % 2 == 0) {
        largeur = largeur - 1;
    }

    curves->clear();

    for (auto& ind : data_indicator)
    {
        sf::VertexArray curve(sf::LineStrip);


        for (size_t i = 0; i < size; ++i) {
            if (data_indicator[ind.first][i] == -1) {
                continue;
            }

            int plus = (largeur - 1) / 2;

            int x = i * ((x_frame) / size) + ((x_frame) / size) / 2 - largeur / 2 + 10;

            curve.append(sf::Vertex(sf::Vector2f(x + plus, (y_frame)-((data_indicator[ind.first][i] - min) * (y_frame / diff_opp) - 10)), sf::Color::Black));
        }
        curves->push_back(curve);
    }
}