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
// TODO: Change from arrays to vectors -> DONE
// TODO: Make the ball bounce off the players' bars -> DONE
// TODO: Check how the events work for inputs because if I move the bar too close to the ball colliding the ball goes through the bar -> DONE
// TODO: Make the ball stop when it hits the left or right outer limits of the screen (goal)
// TODO: Make the ball reset into the middle of the screen and start a new round
// TODO: Make each bar independent -> DONE
// TODO: Research threads for paralel processing of inputs of the different bars


void drawPlayerBar(sf::RenderWindow& window, vector<int> player1Coords, vector<int> player2Coords) {

    int length = 100;

    sf::RectangleShape playerBar(sf::Vector2f(length, 20.f));
    playerBar.setFillColor(sf::Color::Blue);
    playerBar.setPosition(player1Coords[0], player1Coords[1]);
    playerBar.rotate(-90.f);
    
    sf::RectangleShape playerBar2(sf::Vector2f(length, 20.f));
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

void drawBall(sf::RenderWindow& window, vector<int> ballCoords, bool colision1, bool colision2) {

    sf::RectangleShape ball(sf::Vector2f(12, 12));
    ball.setPosition(ballCoords[0], ballCoords[1]);
    ball.setFillColor(sf::Color::White);

    if (colision1) {cout << "Colision Left happened!" << endl;}
    if (colision2) { cout << "Colision Right happened!" << endl; }

    window.draw(ball);
}


vector<int> ballMovement(vector<int> ballCoords, sf::Time time) {

    float speed = 200;

    ballCoords[0] + speed * ballCoords[2] * time.asSeconds() <= 1900 && ballCoords[0] + speed * ballCoords[2] * time.asSeconds() >= 0 ? ballCoords[0] += speed * ballCoords[2] * time.asSeconds() : ballCoords[2] = -ballCoords[2];
    ballCoords[1] + speed * ballCoords[3] * time.asSeconds() <= 1060 && ballCoords[1] + speed * ballCoords[3] * time.asSeconds() >= 0 ? ballCoords[1] += speed * ballCoords[3] * time.asSeconds() : ballCoords[3] = -ballCoords[3];    
    
    return ballCoords;
}

bool ballBarCollision(vector<int> ballDirections, vector<int> playersBarCoords) {

    return playersBarCoords[0] < ballDirections[0]+12 && playersBarCoords[0]+20 > ballDirections[0] && playersBarCoords[1]-100 < ballDirections[1]+12 && playersBarCoords[1] > ballDirections[1];
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
    vector<int> player1BarCoords = { 150, 590 };
    vector<int> player2BarCoords = { 1770, 590 };
    vector<int> ballCoords = { 960, 540, 1, 1 };
    int score[2] = { 0,0 };
    sf::Clock clock;
    bool bColided1;
    bool bColided2;
    float delay = 0;

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
                        player1BarCoords[1] - 150 < 0 ? player1BarCoords[1] = 100 : player1BarCoords[1] -= 50;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        player1BarCoords[1] + 50 > 1080 ? player1BarCoords[1] = 1080 : player1BarCoords[1] += 50;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        player2BarCoords[1] - 150 < 0 ? player2BarCoords[1] = 100 : player2BarCoords[1] -= 50;
                    }

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        player2BarCoords[1] + 50 > 1080 ? player2BarCoords[1] = 1080 : player2BarCoords[1] += 50;
                    }
                    break;
            }
            
        }

        delay += clock.getElapsedTime().asSeconds();
        sf::Time elapsed = clock.restart();

        ballCoords = ballMovement(ballCoords, elapsed);

        bColided1 = ballBarCollision(ballCoords, player1BarCoords);
        bColided2 = ballBarCollision(ballCoords, player2BarCoords);
        if ((bColided1 || bColided2) && delay > 1) { ballCoords[2] = -ballCoords[2]; delay = 0; }


        window.clear();
        window.draw(background);

        drawPlayerBar(window, player1BarCoords, player2BarCoords);

        drawScoreAndCenterLine(window, score);

        drawBall(window, ballCoords, bColided1, bColided2);

        window.display();

    }

	return 0;

}