#include <iostream>
#include "SFML/Graphics.hpp"

int main() {

    // SETTINGS
    int windowWidth = 1920;
    int windowHeight = 1080;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TicTacToe", sf::Style::Close, settings);
    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    background.setFillColor(sf::Color::White);
    window.setVerticalSyncEnabled(true);

    //GAME DATA STRUCTURES


    //WHILE WINDOW IS OPEN LOGIC AKA WHILE THE GAME IS RUNNING
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            }
        }

        window.clear();
        window.draw(background);
        window.display();

    }

	return 0;

}