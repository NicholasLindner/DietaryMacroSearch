#include <SFML/Graphics.hpp> 
#include "Text.h"
#include "Data.h"

using namespace std;

int main() {
    int width = 800;
    int height = 800;

    Data data("2019-2020-FNDDS-At-A-Glance-Ingredient-Nutrient-Values.csv");
    data.organizeData();
    data.heapSort("Carbohydrate", "hi", "no");

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        cout << "Error loading font!" << endl;
    }
    Text text;
    sf::Text header = text.setText(font, sf::String("Dietary Macro Search :)"), 24, sf::Color::White, sf::Vector2f(width / 2.0f, height / 2.0f - 350));
    sf::Text names = text.setText(font, sf::String("Project by Stephanie Fong, Nicholas Lindner, Matthew Rionda"), 14, sf::Color::White, sf::Vector2f(width / 2.0f, height / 2.0f - 325));

    sf::RenderWindow window(sf::VideoMode(width, height), "Dietary Macro Search!");

    sf::Event event;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
            }
        }
        window.clear(sf::Color(167, 162, 168));
        window.draw(header);
        window.draw(names);
        window.display();
    }

    return 0;
}