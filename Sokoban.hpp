// Copyright 2024 Daniel Dsouza
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <utility>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace SB {
enum Direction { Up, Down, Left, Right };

struct Grid {
    std::vector<sf::Vector2u> walls;
    std::vector<sf::Vector2u> boxes;
    std::vector<sf::Vector2u> goals;
    std::vector<sf::Vector2u> ground;
    std::pair<sf::Vector2u, Direction> playerLocation;
};

class Sokoban : public sf::Drawable {
 private:
    unsigned heightv, widthv;
    std::stack<Grid> state;
    sf::Clock clock;
    sf::Time elapsedTime;
    sf::Font font;
    std::vector<std::vector<char>> map;
    static std::map<char, sf::Texture> textures;
    static std::map<char, sf::Texture> loadTextures();
    sf::Vector2u getNewLoc(sf::Vector2u loc, Direction direction);
    char getPlayerTexture(Direction direction) const;

 protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 public:
    Sokoban();
    unsigned height() const { return heightv; }
    unsigned width() const { return widthv; }
    sf::Vector2u playerLoc() const { return state.top().playerLocation.first; }
    void movePlayer(Direction direction);
    void reset();
    void undoMove();
    bool isWon() const;

    friend std::ifstream& operator>>(std::ifstream& is, Sokoban& game);
    friend std::ostream& operator<<(std::ostream& os, const Sokoban& game);
};
}  // namespace SB
