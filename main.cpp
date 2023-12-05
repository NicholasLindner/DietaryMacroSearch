#include <SFML/Graphics.hpp> 
#include <iomanip>
#include "Text.h"
#include "Data.h"
#include "Dropdown.h"

using namespace std;

void adjustDropdownTextPosition(const Dropdown& dropdown, sf::Text& text, float offset) {
    sf::Vector2f dropdownPos = dropdown.getPosition();
    float textYPos = dropdownPos.y - offset;
    float textWidth = text.getLocalBounds().width;
    float textXPos = dropdownPos.x + (dropdown.getWidth() / 2.0f);
    text.setPosition(sf::Vector2f(textXPos, textYPos));
}

int main() {
    int width = 800;
    int height = 1000;
    int resultScrollOffset = 0;
    const int lineHeight = 24;
    const int MAX_RESULT_LINES = 20;
    sf::FloatRect resultArea(10, 600, width - 20, MAX_RESULT_LINES * lineHeight);
  
    Data data("2019-2020-FNDDS-At-A-Glance-Ingredient-Nutrient-Values.csv");
    data.organizeData();

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        cout << "Error loading font!" << endl;
    }
    Text text;
    sf::Text header = text.setText(font, sf::String("Dietary Macro Search!"), 40, sf::Color::White, sf::Vector2f(width / 2.0f, height / 50 + 20), true, false, false);
    sf::Text names = text.setText(font, sf::String("Project by Stephanie Fong, Nicholas Lindner, Matthew Rionda"), 20, sf::Color::White, sf::Vector2f(width / 2.0f, height / 50 + 75), false, true, false);

    Dropdown dropdown(300, 50, data.getMacros());
    dropdown.setPosition(width / 2.0f - 350, height / 50 + 150);

    Dropdown dropdown2(300, 50, data.getMacros());
    dropdown2.setPosition(width / 2.0f + 50, height / 50 + 150);

    // Text for the first dropdown
    sf::Text dropdownOne = text.setText(font, sf::String("Choose a Macro:"), 20, sf::Color::White, sf::Vector2f(0, 0), false, false, true);
    adjustDropdownTextPosition(dropdown, dropdownOne, 20);

    // Text for the second dropdown
    sf::Text dropdownTwo = text.setText(font, sf::String("Don't include Macro (optional):"), 20, sf::Color::White, sf::Vector2f(0, 0), false, false, true);
    adjustDropdownTextPosition(dropdown2, dropdownTwo, 20);

    // Dropdown for merge sort or heap sort
    vector<string> sortingMethods = { "Heap", "Merge" };
    Dropdown sortMethodDropdown(300, 50, sortingMethods);
    sortMethodDropdown.setPosition(width / 2 - 150, height / 50 + 375);
    sf::Text sortMethodText = text.setText(font, sf::String("Choose Sorting Method:"), 20, sf::Color::White, sf::Vector2f(0, 0), false, false, true);
    adjustDropdownTextPosition(sortMethodDropdown, sortMethodText, 20);

    sf::RectangleShape searchButton(sf::Vector2f(200, 50));
    searchButton.setPosition(width / 2.0f - 300, height / 50 + 500);
    searchButton.setFillColor(sf::Color::White);
    sf::Text searchButtonText = text.setText(font, "Search", 20, sf::Color(32, 161, 146), sf::Vector2f(width / 2.0f - 200, height / 50 + 525), false, false, false);

    sf::RectangleShape clearButton(sf::Vector2f(200, 50));
    clearButton.setPosition(width / 2.0f + 100, height / 50 + 500);
    clearButton.setFillColor(sf::Color::White);
    sf::Text clearButtonText = text.setText(font, "Clear", 20, sf::Color(32, 161, 146), sf::Vector2f(width / 2.0f + 200, height / 50 + 525), false, false, false);

    sf::Text resultText = text.setText(font, "", 15, sf::Color::Black, sf::Vector2f(100, height / 50 + 750), false, false, false);
    sf::RenderTexture resultTexture;
    resultTexture.create(resultArea.width, resultArea.height);

    sf::Text errorText = text.setText(font, "", 20, sf::Color::Black, sf::Vector2f(width / 2 - 250, 800), false, false, false);

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

                    if (selectedMacro1 == selectedMacro2) {
                        resultText.setString("");
                        errorText.setString("Error: Please select one distinct macro.");
                        errorText.setPosition(sf::Vector2f(width / 2.0f - errorText.getGlobalBounds().width / 2, 700));
                    }
                    else if (!selectedMacro1.empty() && !selectedSortMethod.empty()) {
                        vector<pair<string, float>> results;
                        errorText.setString("");

                        if (selectedSortMethod == "Heap") {
                            results = data.heapSort(selectedMacro1, selectedMacro2);
                        }
                        else if (selectedSortMethod == "Merge") {
                            results = data.mergeSort(selectedMacro1, selectedMacro2);
                        }

                        stringstream resultStream;
                        int num = 1;
                        for (const auto& pair : results) {
                            resultStream << num << ". " << pair.first << ": " << pair.second << '\n';
                            num++;
                            if (num == 31) {
                                break;
                            }
                        }
                        resultText.setString(resultStream.str());
                    }
                    else if (selectedMacro1.empty()) {
                        resultText.setString("");
                        errorText.setString("Error: Please select a macro to sort by.");
                        errorText.setPosition(sf::Vector2f(width / 2.0f - errorText.getGlobalBounds().width / 2, 700));
                    }
                    else if (selectedSortMethod.empty()) {
                        resultText.setString("");
                        errorText.setString("Error: Please select a sort method.");
                        errorText.setPosition(sf::Vector2f(width / 2.0f - errorText.getGlobalBounds().width / 2, 700));
                    }
                }
                else if (clearButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    dropdown.clear(window);
                    dropdown2.clear(window);
                    sortMethodDropdown.clear(window);
                    resultText.setString("");

                }
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(32, 161, 146));
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
        window.draw(clearButton);
        window.draw(clearButtonText);
        float lineHeight = resultText.getCharacterSize() + 5;
        resultTexture.clear(sf::Color::Transparent);
        resultText.setPosition(0, -resultScrollOffset);
        resultTexture.draw(resultText);
        window.draw(errorText);
        resultTexture.display();

        sf::Sprite resultSprite(resultTexture.getTexture());
        resultSprite.setPosition(resultArea.left, resultArea.top);
        window.draw(resultSprite);
        window.display();
    }

    return 0;
}