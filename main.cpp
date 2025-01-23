// Copyright 2024 Daniel Dsouza
#include <sstream>
#include <iomanip>
#include "Sokoban.hpp"

#define IMG_SIZE 64

using std::cerr, std::cin, std::cout, std::endl;

int main(int argc, char *argv[]) {
    SB::Sokoban game;

    std::ifstream fp(argv[1]);
    if (fp.fail()) {
        cerr << "Unable to open file " << argv[1] << endl;
        exit(1);
    }

    fp >> game;

    sf::RenderWindow window(sf::VideoMode(game.width()
     * IMG_SIZE, game.height() * IMG_SIZE), "Sokoban");
    sf::Event event;

    bool keyPressed = false;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                window.close();
                break;
                case sf::Event::KeyPressed:
                    if (!keyPressed) {
                        switch (event.key.code) {
                            case sf::Keyboard::Escape:
                                window.close();
                                break;
                            case sf::Keyboard::U:
                                game.undoMove();
                                break;
                            case sf::Keyboard::R:
                                game.reset();
                                break;
                            case sf::Keyboard::W:
                                game.movePlayer(SB::Up);
                                keyPressed = true;
                                break;
                            case sf::Keyboard::S:
                                game.movePlayer(SB::Down);
                                keyPressed = true;
                                break;
                            case sf::Keyboard::A:
                                game.movePlayer(SB::Left);
                                keyPressed = true;
                                break;
                            case sf::Keyboard::D:
                                game.movePlayer(SB::Right);
                                keyPressed = true;
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case sf::Event::KeyReleased:
                    keyPressed = false;
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color::Black);

        window.draw(game);

        window.display();
    }

    fp.close();

    return 0;
}
