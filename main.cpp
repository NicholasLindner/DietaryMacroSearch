#include <SFML/Graphics.hpp> 
#include "Text.h"
#include "Data.h"
#include "Dropdown.h"

using namespace std;

void adjustDropdownTextPosition(const Dropdown& dropdown, sf::Text& text, float offset) {
    sf::Vector2f dropdownPos = dropdown.getPosition();
    float textYPos = dropdownPos.y - offset;
    float textWidth = text.getLocalBounds().width;
    float textXPos = dropdownPos.x + (dropdown.getWidth() / 2.0f) - (textWidth / 2.0f);
    text.setPosition(sf::Vector2f(textXPos, textYPos));
}

int main() {
    int width = 2000;
    int height = 2000;
    int resultScrollOffset = 0;
    const int lineHeight = 24;
    const int MAX_RESULT_LINES = 20;
    sf::FloatRect resultArea(100, 800, width - 200, MAX_RESULT_LINES * lineHeight);

    Data data("2019-2020-FNDDS-At-A-Glance-Ingredient-Nutrient-Values.csv");
    data.organizeData();
  
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        cout << "Error loading font!" << endl;
    }
    Text text;
    sf::Text header = text.setText(font, sf::String("Dietary Macro Search :)"), 60, sf::Color::White, sf::Vector2f(width / 2.0f, height / 50), true, false);
    sf::Text names = text.setText(font, sf::String("Project by Stephanie Fong, Nicholas Lindner, Matthew Rionda"), 40, sf::Color::White, sf::Vector2f(width / 2.0f, 80), false, true);

    Dropdown dropdown(500, 50, data.getMacros());
    dropdown.setPosition(100, 400);

    Dropdown dropdown2(500, 50, data.getMacros());
    dropdown2.setPosition(width - 600, 400);

    // Text for the first dropdown
    sf::Text dropdownOne = text.setText(font, sf::String("Choose a Macro:"), 40, sf::Color::White, sf::Vector2f(0, 0), false, true);
    adjustDropdownTextPosition(dropdown, dropdownOne, 50);

    // Text for the second dropdown
    sf::Text dropdownTwo = text.setText(font, sf::String("Don't include Macro(optional):"), 40, sf::Color::White, sf::Vector2f(0, 0), false, true);
    adjustDropdownTextPosition(dropdown2, dropdownTwo, 50);

    // Dropdown for merge sort or heap sort
    vector<string> sortingMethods = { "Heap", "Merge" };
    Dropdown sortMethodDropdown(500, 50, sortingMethods);
    sortMethodDropdown.setPosition(width / 2 - 250, 600);
    sf::Text sortMethodText = text.setText(font, sf::String("Choose Sorting Method:"), 40, sf::Color::White, sf::Vector2f(0, 0), false, true);
    adjustDropdownTextPosition(sortMethodDropdown, sortMethodText, 50);

    sf::RectangleShape searchButton(sf::Vector2f(200, 50));
    searchButton.setPosition(width / 2 - 100, 700);
    searchButton.setFillColor(sf::Color::Blue);

    sf::Text searchButtonText;
    searchButtonText.setFont(font);
    searchButtonText.setString("Search");
    searchButtonText.setCharacterSize(24);
    searchButtonText.setFillColor(sf::Color::White);

    sf::FloatRect buttonTextRect = searchButtonText.getLocalBounds();
    searchButtonText.setOrigin(buttonTextRect.left + buttonTextRect.width / 2.0f, buttonTextRect.top + buttonTextRect.height / 2.0f);
    searchButtonText.setPosition(width / 2, 725);

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setCharacterSize(30);
    resultText.setFillColor(sf::Color::Black);
    resultText.setPosition(100, 800);
    sf::RenderTexture resultTexture;
    resultTexture.create(resultArea.width, resultArea.height);

    sf::RenderWindow window(sf::VideoMode(width, height), "Dietary Macro Search!");


    sf::Event event;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::MouseWheelScrolled) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (resultArea.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    int totalLines = std::count(resultText.getString().begin(), resultText.getString().end(), '\n') + 1;
                    int totalHeight = totalLines * lineHeight - resultArea.height;

                    resultScrollOffset -= static_cast<int>(event.mouseWheelScroll.delta) * lineHeight;
                    resultScrollOffset = std::max(0, resultScrollOffset);
                    resultScrollOffset = std::min(totalHeight, resultScrollOffset);
                }
            }

            dropdown.handleEvent(event);
            dropdown2.handleEvent(event);
            sortMethodDropdown.handleEvent(event);


            if (event.type == sf::Event::MouseButtonPressed) {

                if (searchButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                    string selectedMacro1 = dropdown.getSelectedItem();
                    string selectedMacro2 = dropdown2.getSelectedItem();
                    string selectedSortMethod = sortMethodDropdown.getSelectedItem();


                    if (!selectedMacro1.empty() && !selectedSortMethod.empty()) {
                        vector<pair<string, float>> results;


                        if (selectedSortMethod == "Heap") {
                            results = data.heapSort(selectedMacro1, selectedMacro2);
                        }
                        else if (selectedSortMethod == "Merge") {
                            results = data.mergeSort(selectedMacro1, selectedMacro2);
                        }


                        stringstream resultStream;
                        for (const auto& pair : results) {
                            resultStream << pair.first << " - " << pair.second << "\n";
                        }
                        resultText.setString(resultStream.str());
                    }
                    else {

                        resultText.setString("Error: Please select at least one macro and a sorting method.");
                    }
                }
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(167, 162, 168));
        window.draw(header);
        window.draw(names);
        window.draw(dropdownOne);
        window.draw(dropdownTwo);
        window.draw(sortMethodText);
        dropdown.draw(window);
        dropdown2.draw(window);
        sortMethodDropdown.draw(window);
        window.draw(searchButton);
        window.draw(searchButtonText);
        float lineHeight = resultText.getCharacterSize() + 5;
        resultTexture.clear(sf::Color::Transparent);
        resultText.setPosition(0, -resultScrollOffset);
        resultTexture.draw(resultText);
        resultTexture.display();

        sf::Sprite resultSprite(resultTexture.getTexture());
        resultSprite.setPosition(resultArea.left, resultArea.top);
        window.draw(resultSprite);
        window.display();
    }

    return 0;
}