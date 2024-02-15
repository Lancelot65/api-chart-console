#include "graphique.hpp"
#include <SFML/Graphics.hpp>
#include <crypto.hpp>

#include <iostream>
#include <vector>
#include <string>


class chart
{
private:
    float width_screen = 1280;
    float height_screen = 720;

    graphique Graphique;

    sf::Cursor cursor_resize;
    sf::Cursor cursor_default;

    bool temp_click_resize_etat = false;

public:
    chart(OHLCV _data) :
        Graphique(0, 0, this->width_screen, this->height_screen, _data) {}

    void loop()
    {
        sf::RenderWindow window(sf::VideoMode(u_int(this->width_screen), u_int(this->height_screen)), "candlestick chart", sf::Style::Close | sf::Style::Titlebar);

        sf::Image icon;
        icon.loadFromFile("logo.png");
        
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        int i = 0;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:

                    if (event.key.control)
                    {
                        bool fPressed = event.key.code == sf::Keyboard::F;

                        if (fPressed)
                        {
                            Graphique.set_theme(Dark);
                        }
                    }
                    break;
                }
            }

            window.clear(sf::Color::White);

            this->draw(window);


            window.display();
        }
    }

    void draw(sf::RenderWindow& window)
    {
        this->Graphique.show(window);
    }
};

int main()
{
    OHLCV data = load_crypto(datetime_to_milliseconds("2024-02-01"), datetime_to_milliseconds("2024-02-02"), "BTCUSDT", "1h");
    chart obj(data);
    obj.loop();

    return 0;
}