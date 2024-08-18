#include <iostream>
#include "SFML/Graphics.hpp"

// TODO: Place the bars equally spaced from the borders of the screen -> DONE
// TODO: Allign scoreboard to the center -> DONE
// TODO: Draw center line -> DONE
// TODO: Add functionality to the different bars -> DONE
// TODO: Create the ball
// TODO: Make each bar independent -> DONE
// TODO: Research threads for paralel processing of inputs of the different bars


void drawPlayerBar(sf::RenderWindow& window, int player1Coords[2], int player2Coords[2]) {

    int length = 100;

    sf::RectangleShape playerBar(sf::Vector2f(length, 12.f));
    playerBar.setFillColor(sf::Color::Blue);
    playerBar.setPosition(player1Coords[0], player1Coords[1]);
    playerBar.rotate(-90.f);
    
    sf::RectangleShape playerBar2(sf::Vector2f(length, 12.f));
    playerBar2.setFillColor(sf::Color::Red);
    playerBar2.setPosition(player2Coords[0], player2Coords[1]);
    playerBar2.rotate(-90.f);

    window.draw(playerBar);
    window.draw(playerBar2);

}

void drawScoreAndCenterLine(sf::RenderWindow& window, int score[2]) {

    sf::Font font;
    font.loadFromFile("C:\\Users\\gonca\\source\\repos\\Pong\\assets\\PressStart2P-vaV7.ttf");

    sf::Text player1Score;
    sf::Text player2Score;

    player1Score.setFont(font);
    player1Score.setString(std::to_string(score[0]));
    player1Score.setCharacterSize(60); // in pixels, not points!
    player1Score.setFillColor(sf::Color::White);
    player1Score.setStyle(sf::Text::Bold);
    player1Score.setPosition(860, 100);

    player2Score.setFont(font);
    player2Score.setString(std::to_string(score[1]));
    player2Score.setCharacterSize(60); // in pixels, not points!
    player2Score.setFillColor(sf::Color::White);
    player2Score.setStyle(sf::Text::Bold);
    player2Score.setPosition(995, 100);

    sf::RectangleShape middleLine(sf::Vector2f(30, 7.f));

    sf::Color middleBarCollor(255,255,255,120);
    middleLine.setFillColor(middleBarCollor);
    
    middleLine.rotate(90.f);

    int middleLineY = 0; 
    while (middleLineY < 1080) {
        middleLine.setPosition(960, middleLineY);
        window.draw(middleLine);

        middleLineY += 50;
    }

    window.draw(player1Score);
    window.draw(player2Score);
    

}


int main() {

    // SETTINGS
    int windowWidth = 1920;
    int windowHeight = 1080;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //RENDER WINDOW
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TicTacToe", sf::Style::Close, settings);
    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    background.setFillColor(sf::Color::Black);
    window.setVerticalSyncEnabled(true);

    //GAME DATA STRUCTURES
    int player1BarCoords[2] = { 150,590 };
    int player2BarCoords[2] = { 1770, 590 };
    int ballCoords[2];
    int score[2] = { 0,0 };

    //WHILE WINDOW IS OPEN LOGIC AKA WHILE THE GAME IS RUNNING
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        player1BarCoords[1] -= 25;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        player1BarCoords[1] += 25;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        player2BarCoords[1] -= 25;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        player2BarCoords[1] += 25;
                    }
                    break;
            }
            
        }



        window.clear();

        window.draw(background);
        //drawPlayerBar(window);

        drawPlayerBar(window, player1BarCoords, player2BarCoords);

        drawScoreAndCenterLine(window, score);
        
        window.display();

    }

	return 0;

}