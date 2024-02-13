#include "graphique.hpp"
#include "parametre.hpp"
#include <SFML/Graphics.hpp>
#include <crypto.hpp>

#include <iostream>
#include <vector>
#include <string>


class chart
{
private:
    int width_screen = 1280;
    int height_screen = 720;

    int limit = 1200;
    parametre Parametre;
    graphique Graphique;

    sf::Cursor cursor_resize;
    sf::Cursor cursor_default;

    bool temp_click_resize_etat = false;

public:
    chart(OHLCV _data) :
        Parametre(this->limit, 0, this->width_screen - this->limit, this->height_screen, this->width_screen, this->height_screen), Graphique(0, 0, float(this->limit), float(this->height_screen), _data)
          
    
    {
        this->cursor_default.loadFromSystem(sf::Cursor::Arrow);
        this->cursor_resize.loadFromSystem(sf::Cursor::SizeHorizontal);
    }

    void loop()
    {
        sf::RenderWindow window(sf::VideoMode(this->width_screen, this->height_screen), "test", sf::Style::Close | sf::Style::Titlebar);

        // this->Parametre.create_parametre(window);


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseMoved)
                {
                    this->on_mouse_motion(window);
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        this->on_mouse_press(x, y);
                    }
                }
                
                

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        on_mouse_release(event.mouseButton.x);
                    }
                }
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->on_mouse_drag(sf::Mouse::getPosition(window).x);
            }

            this->draw(window);
            
            

            window.display();
        }
    }

    void draw(sf::RenderWindow& window)
    {
        this->Graphique.show(window);
        this->Parametre.show(window);

    }

    void on_mouse_motion(sf::RenderWindow& window)
    {
        int x = sf::Mouse::getPosition(window).x;
        if (x > this->limit - 3 && x < this->limit + 3)
        {
            window.setMouseCursor(this->cursor_resize);
        }
        else
        {
            window.setMouseCursor(this->cursor_default);
        }
    }

    void on_mouse_press(int x, int y)
    {
        if (x > this->limit - 3 and x < this->limit + 3)
        {
            this->temp_click_resize_etat = true;
        }
        else if (this->Parametre.collide(x, y))
            if (!this->Parametre.get_etat_view())
            {
                this->Graphique.set_size(0.0f, 0.0f, float(this->width_screen), float(this->height_screen));
            }
            else
            {
                this->Graphique.set_size(0.0f, 0.0f, float(this->limit), float(this->height_screen));
            }
        else if (this->Graphique.collide(float(x), float(y)))
        {
            return;
        }
    }

    void on_mouse_release(int x)
    {
        if (temp_click_resize_etat)
        {
            temp_click_resize_etat = false;
            this->limit = this->Parametre.check_size(x);
            this->Graphique.set_size(0.0f, 0.0f, float(this->limit), float(this->height_screen));
            this->Parametre.set_size(this->limit, 0, this->limit, this->height_screen);
        }
    }

    void on_mouse_drag(int x)
    {
        if (temp_click_resize_etat)
        {
            this->limit = this->Parametre.check_size(x);
            this->Graphique.set_size(0.0f, 0.0f, float(this->limit), float(this->height_screen));
            this->Parametre.set_size(this->limit, 0, this->limit, this->height_screen);
        }
    }
};

int main()
{
    OHLCV data = load_crypto(datetime_to_milliseconds("2024-02-01"), datetime_to_milliseconds("2024-02-11"), "BTCUSDT", "1h");
    chart obj(data);
    obj.loop();

    return 0;
}