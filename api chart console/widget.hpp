#pragma once 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

static bool collision_point(sf::RectangleShape& rect, sf::Vector2i position)
{
    return (rect.getPosition().x < position.x && position.x < rect.getPosition().x + rect.getSize().x && rect.getPosition().y < position.y && position.y < rect.getPosition().y + rect.getSize().y);
}

static int findIndex(const std::vector<std::string>& vec, std::string target)
{
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == target)
        {
            return i;
        }
    }
    return -1;
}

class Combobox
{
private:
    float x, y, width, height;
    sf::RenderWindow* window;

    sf::Font font;
    sf::Text text;

    std::vector<std::string> items;
    std::vector<std::string> items_not_select;

    sf::RectangleShape base_rect;
    std::vector< sf::RectangleShape> items_rect;

    sf::RectangleShape rect_option;
    std::vector<sf::Text> text_option;

    int seleted_index;

    bool is_open = false;

    float Thickness = 1;


public:
    Combobox(float x, float y, float width, float height, std::vector<std::string> items, sf::RenderWindow* window, int seleted_index = 0) :
        x(x), y(y), width(width), height(height), items(items), base_rect(sf::Vector2f(width, height)), window(window), seleted_index(seleted_index)
    {
        this->set_rect(x, y, width, height);
        this->update_items_not_select();

    }

    void set_rect(float x, float y, float width, float height)
    {
        this->base_rect.setPosition(sf::Vector2f(x, y));
        this->base_rect.setFillColor(sf::Color::White);
        this->base_rect.setOutlineColor(sf::Color::Black);
        this->base_rect.setOutlineThickness(this->Thickness);

        sf::RectangleShape itemBox(sf::Vector2f(this->width, this->height));
        itemBox.setFillColor(sf::Color::White);
        itemBox.setOutlineThickness(Thickness);
        itemBox.setOutlineColor(sf::Color::Black);
        for (size_t i = 0; i < this->items.size() - 1; i++)
        {
            itemBox.setPosition(this->x, this->y + this->height * (i + 1) + this->Thickness);
            this->items_rect.push_back(itemBox);
        }

        this->font.loadFromFile("c:/Windows/Fonts/arial.ttf");

        this->text.setFont(this->font);
        this->text.setCharacterSize(14);
        this->text.setFillColor(sf::Color::Black);

        this->update_items_not_select();
    }

    void update_items_not_select()
    {
        rect_option.setSize(sf::Vector2f(width, height * this->items.size()));
        rect_option.setPosition(sf::Vector2f(x, y + height));
        items_not_select.clear();
        for (std::string elem : this->items)
        {
            if (elem != this->items[seleted_index])
            {
                items_not_select.push_back(elem);
            }
        }
        for (size_t i = 0; i < this->items.size() - 1; i++)
        {
            this->text.setPosition(this->x + 5, this->y + this->height * (i + 1) + this->Thickness);
            this->text.setString(this->items_not_select[i]);
            this->text_option.push_back(this->text);
        }
    }

    void event_onpress(sf::Event event)
    {
        sf::Vector2i position(event.mouseButton.x, event.mouseButton.y);
        if (collision_point(this->base_rect, position))
        {
            this->is_open = !this->is_open;
        }
    }

    void event_release(sf::Event event)
    {
        if (this->is_open)
        {
            sf::Vector2i position = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            if (collision_point(this->rect_option, position))
            {
                sf::RectangleShape temp_rect(sf::Vector2f(this->width, this->height));
                for (size_t i = 0; i < this->items_not_select.size(); i++)
                {
                    temp_rect.setPosition(this->x, this->y + this->height * (i + 1) + this->Thickness);
                    if (collision_point(temp_rect, position))
                    {
                        this->seleted_index = findIndex(this->items, this->items_not_select[i]);
                        this->update_items_not_select();
                        this->is_open = false;
                        break;
                    }
                }
            }
        }
    }

    void show()
    {
        this->window->draw(this->base_rect);
        this->text.setPosition(this->x + 5, y);
        this->text.setString(this->items[this->seleted_index]);
        this->window->draw(this->text);

        if (this->is_open)
        {
            for (size_t i = 0; i < this->items_not_select.size(); i++)
            {
                this->window->draw(this->items_rect[i]);
                this->window->draw(this->text_option[i]);
            }
        }

    }

    std::string get_value()
    {
        return this->items[this->seleted_index];
    }

};

class Button
{
private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Color color;
    sf::Color outine_color;
public:
    Button(float x, float y, float width, float height, std::string text, sf::Font& font, sf::Color color, sf::Color outine_color) :
        m_shape(sf::Vector2f(width, height)), m_text(text, font), color(color), outine_color(outine_color)
    {
        this->m_shape.setPosition(x, y);
        this->m_text.setPosition(x + (width - m_text.getLocalBounds().width) / 2, y + (height - m_text.getLocalBounds().height) / 2);

        this->m_shape.setFillColor(color);
        this->m_shape.setOutlineThickness(2.f);
        this->m_shape.setOutlineColor(outine_color);

        m_text.setFillColor(sf::Color::Black);
        m_text.setCharacterSize(20);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(this->m_shape);
        window.draw(this->m_text);
    }

    void moussepress(sf::Event event) {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "click";
        }
    }
};