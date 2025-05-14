#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

#define WindowHeight 550
#define WindowWidth 900
#define PaddleWidth WindowWidth * 0.012
#define PaddleHeight WindowHeight * 0.15
#define BallRadius WindowWidth * 0.01

int Player1Score = 0;
int Player2Score = 0;

float Paddle1_X = WindowWidth * 0.018;
float Paddle1_Y = WindowHeight * 0.417;
float Paddle2_X = WindowWidth - PaddleWidth - Paddle1_X;
float Paddle2_Y = WindowHeight * 0.416;
float Ball_X = WindowWidth / 2;
float Ball_Y = WindowHeight / 2;

float BallSpeedX = 5.0f;
float BallSpeedY = 3.0f;

bool GameEnded = false;

int main() {
    RenderWindow GameWindow(VideoMode(WindowWidth, WindowHeight), "BroxGaming");
    GameWindow.setFramerateLimit(60);

    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("game_bg.png")) {
        return 1;
    }
    Sprite BackGround(backgroundTexture);
    Vector2f scale(static_cast<float>(WindowWidth) / backgroundTexture.getSize().x,
                   static_cast<float>(WindowHeight) / backgroundTexture.getSize().y);
    BackGround.setScale(scale);

    Font font;
    if (!font.loadFromFile("Watanabe.ttf")) {
        return -1;
    }

    Text Score1(std::to_string(Player1Score), font, 60);
    Score1.setFillColor(Color::Red);
    Score1.setPosition(WindowWidth / 2 - 100, 25);

    Text Score2(std::to_string(Player2Score), font, 60);
    Score2.setFillColor(Color::Blue);
    Score2.setPosition(WindowWidth / 2 + 50, 25);

    Text GameResult("", font, 50);
    GameResult.setPosition(WindowWidth / 2 - 150, WindowHeight / 2);

    RectangleShape Paddle1(Vector2f(PaddleWidth, PaddleHeight));
    Paddle1.setFillColor(Color::Red);
    Paddle1.setPosition(Paddle1_X, Paddle1_Y);

    RectangleShape Paddle2(Vector2f(PaddleWidth, PaddleHeight));
    Paddle2.setFillColor(Color::Blue);
    Paddle2.setPosition(Paddle2_X, Paddle2_Y);

    CircleShape Ball(BallRadius);
    Ball.setFillColor(Color::Yellow);
    Ball.setPosition(Ball_X, Ball_Y);

    bool W_Pressed = false;
    bool S_Pressed = false;
    bool Up_Pressed = false;
    bool Down_Pressed = false;

    while (GameWindow.isOpen() && !GameEnded) {
        Event event;
        while (GameWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                GameWindow.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    GameWindow.close();
                }
                if (event.key.code == Keyboard::W) {
                    W_Pressed = true;
                }
                if (event.key.code == Keyboard::S) {
                    S_Pressed = true;
                }
                if (event.key.code == Keyboard::Up) {
                    Up_Pressed = true;
                }
                if (event.key.code == Keyboard::Down) {
                    Down_Pressed = true;
                }
            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::W) {
                    W_Pressed = false;
                }
                if (event.key.code == Keyboard::S) {
                    S_Pressed = false;
                }
                if (event.key.code == Keyboard::Up) {
                    Up_Pressed = false;
                }
                if (event.key.code == Keyboard::Down) {
                    Down_Pressed = false;
                }
            }
        }

        if (W_Pressed && Paddle1.getPosition().y > 0) {
            Paddle1.move(0, -5.0f);
        }
        if (S_Pressed && Paddle1.getPosition().y + PaddleHeight < WindowHeight) {
            Paddle1.move(0, 5.0f);
        }
        if (Up_Pressed && Paddle2.getPosition().y > 0) {
            Paddle2.move(0, -5.0f);
        }
        if (Down_Pressed && Paddle2.getPosition().y + PaddleHeight < WindowHeight) {
            Paddle2.move(0, 5.0f);
        }

        Ball.move(BallSpeedX, BallSpeedY);

        if (Ball.getPosition().y <= 0 || Ball.getPosition().y + BallRadius * 2 >= WindowHeight) {
            BallSpeedY *= -1;
        }

        if (Ball.getGlobalBounds().intersects(Paddle1.getGlobalBounds()) ||
            Ball.getGlobalBounds().intersects(Paddle2.getGlobalBounds())) {
            BallSpeedX *= -1;
        }

        if (Ball.getPosition().x <= 0) {
            Player2Score++;
            Score2.setString(std::to_string(Player2Score));
            Ball.setPosition(Ball_X, Ball_Y);
            BallSpeedX = 5.0f;
        } else if (Ball.getPosition().x + BallRadius * 2 >= WindowWidth) {
            Player1Score++;
            Score1.setString(std::to_string(Player1Score));
            Ball.setPosition(Ball_X, Ball_Y);
            BallSpeedX = -5.0f;
        }

        if (Player1Score >= 10) {
            GameResult.setString("Player 1 Wins!");
            GameResult.setFillColor(Color::Red);
            GameEnded = true;
        } else if (Player2Score >= 10) {
            GameResult.setString("Player 2 Wins!");
            GameResult.setFillColor(Color::Blue);
            GameEnded = true;
        }

        GameWindow.clear();
        GameWindow.draw(BackGround);
        GameWindow.draw(Paddle1);
        GameWindow.draw(Paddle2);
        GameWindow.draw(Ball);
        GameWindow.draw(Score1);
        GameWindow.draw(Score2);
        if (GameEnded) {
            GameWindow.draw(GameResult);
        }
        GameWindow.display();
    }

    if (GameEnded) {
        sf::sleep(sf::seconds(3));
    }

    return 0;
}
