#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;

// TODO: Place the bars equally spaced from the borders of the screen -> DONE
// TODO: Allign scoreboard to the center -> DONE
// TODO: Draw center line -> DONE
// TODO: Add functionality to the different bars -> DONE
// TODO: Create the ball -> DONE
// TODO: Make the ball move in a random direction to start -> DONE
// TODO: Make the ball bounce off the upper and lower limits of the screen -> DONE
// TODO: Make the ball bounce off the players' bars
// TODO: Make the ball stop when it hits the left or right outer limits of the screen (goal)
// TODO: Make the ball reset into the middle of the screen and start a new round
// TODO: Make each bar independent -> DONE
// TODO: Research threads for paralel processing of inputs of the different bars


void drawPlayerBar(sf::RenderWindow& window, int playersCoords[4]) {

    int length = 100;

    sf::RectangleShape playerBar(sf::Vector2f(length, 12.f));
    playerBar.setFillColor(sf::Color::Blue);
    playerBar.setPosition(playersCoords[0], playersCoords[1]);
    playerBar.rotate(-90.f);
    
    sf::RectangleShape playerBar2(sf::Vector2f(length, 12.f));
    playerBar2.setFillColor(sf::Color::Red);
    playerBar2.setPosition(playersCoords[2], playersCoords[3]);
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

int* drawBall(sf::RenderWindow& window, int ballCoords[2], sf::Time time, int ballDirections[2]) {

    sf::RectangleShape ball(sf::Vector2f(20, 20));
    ball.setFillColor(sf::Color::White);

    float speed = 200;

    ballCoords[0] + speed * ballDirections[0] * time.asSeconds() <= 1900 && ballCoords[0] + speed * ballDirections[0] * time.asSeconds() >= 0 ? ballCoords[0] += speed * ballDirections[0] * time.asSeconds() : ballDirections[0] = -ballDirections[0];
    ballCoords[1] + speed * ballDirections[1] * time.asSeconds() <= 1060 && ballCoords[1] + speed * ballDirections[1] * time.asSeconds() >= 0 ? ballCoords[1] += speed * ballDirections[1] * time.asSeconds() : ballDirections[1] = -ballDirections[1];

    ball.setPosition(ballCoords[0], ballCoords[1]);

    window.draw(ball);

    int* movementDirections = new int[2];
    movementDirections[0] = ballDirections[0];
    movementDirections[1] = ballDirections[1];
    
    return movementDirections;
}

void checkBallBarCollision() {

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
    int playersBarCoords[4] = { 150, 590, 1770, 590 };
    int ballCoords[2] = { 960, 540 };
    int score[2] = { 0,0 };
    sf::Clock clock;
    int initDirections[2] = { 1,1 };
    int* ballDirections = initDirections;

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
                        playersBarCoords[1] - 125 < 0 ? playersBarCoords[1] = 100 : playersBarCoords[1] -= 25;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        playersBarCoords[1] + 25 > 1080 ? playersBarCoords[1] = 1080 : playersBarCoords[1] += 25;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        playersBarCoords[3] - 125 < 0 ? playersBarCoords[3] = 100 : playersBarCoords[3] -= 25;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        playersBarCoords[3] + 25 > 1080 ? playersBarCoords[3] = 1080 : playersBarCoords[3] += 25;
                    }
                    break;
            }
            
        }

        window.clear();

        window.draw(background);

        drawPlayerBar(window, playersBarCoords);

        drawScoreAndCenterLine(window, score);

        sf::Time elapsed = clock.restart();

        ballDirections = drawBall(window, ballCoords, elapsed, ballDirections);
        
        window.display();

    }

	return 0;

}