#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <SFML/Graphics/Font.hpp>

class ComboBox {
public:
    ComboBox(sf::Vector2f position, sf::Font& font) : m_position(position), m_font(font), m_isOpen(false) {}

    void addItem(const std::string& item) {
        m_items.push_back(item);
    }

    void draw(sf::RenderWindow& window) {
        // Draw the selected item
        sf::RectangleShape selectedItemBox(sf::Vector2f(200.f, 30.f));
        selectedItemBox.setFillColor(sf::Color::White);
        selectedItemBox.setOutlineThickness(1.f);
        selectedItemBox.setOutlineColor(sf::Color::Black);
        selectedItemBox.setPosition(m_position);

        sf::Text selectedItemText(m_items[m_selectedIndex], m_font, 20);
        selectedItemText.setPosition(m_position.x + 5.f, m_position.y + 5.f);

        window.draw(selectedItemBox);
        window.draw(selectedItemText);

        if (m_isOpen) {
            sf::RectangleShape dropdownBox(sf::Vector2f(200.f, 30.f * m_items.size()));
            dropdownBox.setFillColor(sf::Color::White);
            dropdownBox.setOutlineThickness(1.f);
            dropdownBox.setOutlineColor(sf::Color::Black);
            dropdownBox.setPosition(m_position.x, m_position.y + 30.f);

            window.draw(dropdownBox);

            for (size_t i = 0; i < m_items.size(); ++i) {
                sf::Text itemText(m_items[i], m_font, 20);
                itemText.setPosition(m_position.x + 5.f, m_position.y + 30.f * (i + 1) + 5.f);

                window.draw(itemText);
            }
        }
    }

    void toggleOpen() {
        m_isOpen = !m_isOpen;
    }

    bool isOpen() const {
        return m_isOpen;
    }

    void setSelectedIndex(size_t index) {
        if (index < m_items.size())
            m_selectedIndex = index;
    }

private:
    sf::Vector2f m_position;
    sf::Font& m_font;
    std::vector<std::string> m_items;
    size_t m_selectedIndex = 0;
    bool m_isOpen;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML ComboBox");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
        return 1;
    }

    ComboBox comboBox(sf::Vector2f(100.f, 100.f), font);
    comboBox.addItem("Option 1");
    comboBox.addItem("Option 2");
    comboBox.addItem("Option 3");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (comboBox.isOpen()) {
                        comboBox.toggleOpen();
                    }
                    else {
                        comboBox.toggleOpen();
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        comboBox.draw(window);
        window.display();
    }

    return 0;
}
