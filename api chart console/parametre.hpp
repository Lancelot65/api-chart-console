#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <outil_requete.hpp>
#include <algorithm>
#include "widget.hpp"


static bool collision_point(sf::RectangleShape& rect, float x_point, float y_point)
{
    return (rect.getPosition().x < x_point && x_point < rect.getPosition().x + rect.getSize().x && rect.getPosition().y < y_point && y_point < rect.getPosition().y + rect.getSize().y);
}

class parametre
{
private:
    int screen_height;
    int screen_width;

    int min_width = 15;
    int max_width = 140;

    bool etat_view = true;

    sf::RectangleShape rect;
    sf::RectangleShape rect_croix;

    sf::VertexArray croix_line;
    sf::VertexArray liste_line;

    std::vector<Combobox> liste_combobox;

public:
    parametre(int x, int y, int width, int height, int _screen_width, int _screen_height) :
    screen_height(_screen_height), screen_width(_screen_width)
    {
        this->rect.setPosition(sf::Vector2f(float(x), float(y)));
        this->rect.setSize(sf::Vector2f(float(width), float(height)));
        this->rect.setFillColor(sf::Color(0, 0, 0));
     
        this->rect_croix.setPosition(sf::Vector2f(float(this->screen_width - 13), 5.0f));
        this->rect_croix.setSize(sf::Vector2f(10.0f, 10.0f));


        this->croix_line.setPrimitiveType(sf::Lines);
        this->liste_line.setPrimitiveType(sf::Lines);

        this->croix_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 5), 5.0f), sf::Color(255, 255, 255)));
        this->croix_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 15), 15.0f), sf::Color(255, 255, 255)));

        this->croix_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 15), 5.0f), sf::Color(255, 255, 255)));
        this->croix_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 5), 15.0f), sf::Color(255, 255, 255)));

    
        this->liste_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 5), 5.0f), sf::Color(0, 0, 0)));
        this->liste_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 15), 5.0f), sf::Color(0, 0, 0)));

        this->liste_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 5), 9.0f), sf::Color(0, 0, 0)));
        this->liste_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 15), 9.0f), sf::Color(0, 0, 0)));

        this->liste_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 5), 13.0f), sf::Color(0, 0, 0)));
        this->liste_line.append(sf::Vertex(sf::Vector2f(float(this->screen_width - 15), 13.0f), sf::Color(0, 0, 0)));
    }

    void show(sf::RenderWindow &window)
    {
        if (this->etat_view)
        {
            window.draw(this->rect);
            window.draw(this->croix_line);
            for (auto combobox : liste_combobox)
            {
                combobox.show();
            }
        }
        else
        {
            window.draw(this->liste_line);
        }
    }

    bool collide(int x, int y)
    {
        if (collision_point(this->rect, float(x), float(y)))
        {
            if (collision_point(this->rect_croix, float(x), float(y)))
            {
                this->etat_view = !this->etat_view;
                return true;
            }
        }
        return false;
    }

    int check_size(int x)
    {
        if (x >= this->screen_width - this->min_width)
        {
            return this->screen_width - this->min_width;
        }
        else if (x <= this->screen_width - this->max_width)
        {
            return this->screen_width - this->max_width;
        }
        return x;
    }

    void set_size(int x, int y, int width, int height)
    {
        this->rect.setSize(sf::Vector2f(float(width), float(height)));
        this->rect.setPosition(sf::Vector2f(float(x), float(y)));
    }

    bool get_etat_view()
    {
        return this->etat_view;
    }

    void create_parametre(sf::RenderWindow& window)
    {
        std::vector <std::string> options = { "BTCUSDT", "EURUSD" };
        Combobox combobox(this->rect.getPosition().x + 10, 10, 40, 8, options, &window);
        this->liste_combobox.push_back(combobox);
    }
};