// Copyright 2024 Daniel Dsouza
#include "Sokoban.hpp"

#define IMG_SIZE 64

namespace SB {

Sokoban::Sokoban() {
    if (!font.loadFromFile("./arial.ttf")) {
        std::cerr << "Unable to load font arial.ttf" << std::endl;
        // exit(1);
    }

    elapsedTime = clock.getElapsedTime();
}

std::ifstream& operator>>(std::ifstream& is, Sokoban& game) {
    is >> game.heightv >> game.widthv;

    game.map = std::vector<std::vector<char>>(game.heightv, std::vector<char>(game.widthv));

    game.state.push(Grid());

    for (unsigned row = 0; row < game.heightv; row++) {
        for (unsigned col = 0; col < game.widthv; col++) {
            is >> game.map[row][col];
            sf::Vector2u loc(col, row);
            switch (game.map[row][col]) {
            case '@':
                game.state.top().playerLocation = std::make_pair(loc, SB::Down);
                game.state.top().ground.push_back(loc);
                break;
            case '#':
                game.state.top().walls.push_back(loc);
                break;
            case '1':
                game.state.top().boxes.push_back(loc);
            case 'a':
                game.state.top().goals.push_back(loc);
                break;
            case 'A':
                game.state.top().ground.push_back(loc);
                game.state.top().boxes.push_back(loc);
                break;
            case '.':
                game.state.top().ground.push_back(loc);
                break;
            default:
                break;
            }
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Sokoban& game) {
    os << game.heightv << " " << game.widthv << std::endl;

    for (unsigned row = 0; row < game.heightv; row++) {
        for (unsigned col = 0; col < game.widthv; col++) {
            os << game.map[row][col];
        }
        os << std::endl;
    }

    return os;
}

std::map<char, sf::Texture> Sokoban::loadTextures() {
    std::map<char, sf::Texture> textures;
    sf::Texture playerTexture;
    sf::Texture wallTexture;
    sf::Texture groundTexture;
    sf::Texture boxTexture;
    sf::Texture goalTexture;

    if (!playerTexture.loadFromFile("./sokoban/player_05.png")) {
        std::cerr << "Unable to load texture player_05!" << std::endl;
        // exit(1);
    }
    textures['@'] = playerTexture;
    if (!playerTexture.loadFromFile("./sokoban/player_08.png")) {
        std::cerr << "Unable to load texture player_08!" << std::endl;
        // exit(1);
    }
    textures['^'] = playerTexture;
    if (!playerTexture.loadFromFile("./sokoban/player_20.png")) {
        std::cerr << "Unable to load texture player_20!" << std::endl;
        // exit(1);
    }
    textures['<'] = playerTexture;
    if (!playerTexture.loadFromFile("./sokoban/player_17.png")) {
        std::cerr << "Unable to load texture player_17!" << std::endl;
        // exit(1);
    }
    textures['>'] = playerTexture;
    if (!wallTexture.loadFromFile("./sokoban/block_06.png")) {
        std::cerr << "Unable to load texture block_06!" << std::endl;
        // exit(1);
    }
    textures['#'] = wallTexture;
    if (!groundTexture.loadFromFile("./sokoban/ground_01.png")) {
        std::cerr << "Unable to load texture ground_01!" << std::endl;
        // exit(1);
    }
    textures['.'] = groundTexture;
    if (!goalTexture.loadFromFile("./sokoban/ground_04.png")) {
        std::cerr << "Unable to load texture ground_04!" << std::endl;
        // exit(1);
    }
    textures['a'] = goalTexture;
    if (!boxTexture.loadFromFile("./sokoban/crate_03.png")) {
        std::cerr << "Unable to load texture crate_03!" << std::endl;
        // exit(1);
    }
    textures['1'] = boxTexture;
    textures['A'] = boxTexture;

    return textures;
}

std::map<char, sf::Texture> Sokoban::textures = Sokoban::loadTextures();

void Sokoban::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite groud, wall, box, goal, player;
    groud.setTexture(textures['.']);
    wall.setTexture(textures['#']);
    box.setTexture(textures['A']);
    goal.setTexture(textures['a']);
    player.setTexture(textures[getPlayerTexture(state.top().playerLocation.second)]);

    auto spriteDrawer = [&](auto &sprite, const auto &pos) {
        sprite.setPosition(pos.x * IMG_SIZE, pos.y * IMG_SIZE);
        target.draw(sprite, states);
    };

    std::for_each(state.top().walls.begin(), state.top().walls.end(),
                    [&](const auto &wallPos)
                    { spriteDrawer(wall, wallPos); });

    std::for_each(state.top().ground.begin(), state.top().ground.end(),
                    [&](const auto &groundPos)
                    { spriteDrawer(groud, groundPos); });

    std::for_each(state.top().goals.begin(), state.top().goals.end(),
                    [&](const auto &goalPos)
                    { spriteDrawer(goal, goalPos); });

    std::for_each(state.top().boxes.begin(), state.top().boxes.end(),
                    [&](const auto &boxPos)
                    { spriteDrawer(box, boxPos); });

    player.setPosition(state.top().playerLocation.first.x * IMG_SIZE,
    state.top().playerLocation.first.y * IMG_SIZE);
    target.draw(player, states);

    std::stringstream ss;
    sf::Text text;

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    sf::Time elapsedTime = this->clock.getElapsedTime();

    text.setPosition(sf::Vector2f(IMG_SIZE * (widthv - 1) / 2,
    IMG_SIZE / 2 - text.getCharacterSize() / 2));

    ss << std::setw(2) << std::setfill('0') << static_cast<int>(elapsedTime.asSeconds()) / 60 <<
    ":" << std::setw(2) << std::setfill('0') << static_cast<int>(elapsedTime.asSeconds()) % 60;

    text.setString(ss.str());

    if (isWon()) {
        sf::Text won;
        won.setFont(font);
        won.setCharacterSize(64);
        won.setFillColor(sf::Color::Green);
        won.setString("You won!");
        won.setOrigin(won.getLocalBounds().width / 2, won.getLocalBounds().height / 2);
        won.setPosition(target.getSize().x / 2, target.getSize().y / 2);
        target.draw(won);
    }

    target.draw(text);
}


void Sokoban::movePlayer(Direction direction) {
    if (!isWon()) {
        sf::Vector2u newPlayerLocation = getNewLoc(state.top().playerLocation.first, direction);

        if (newPlayerLocation.x >= 0 && newPlayerLocation.x < width() &&
        newPlayerLocation.y >= 0 && newPlayerLocation.y < height()) {
            if (std::find(state.top().walls.begin(), state.top().walls.end(),
            newPlayerLocation) == state.top().walls.end()) {
                if (std::find(state.top().boxes.begin(), state.top().boxes.end(),
                newPlayerLocation) == state.top().boxes.end()) {
                    Grid temp;
                    temp.ground = state.top().ground;
                    temp.boxes = state.top().boxes;
                    temp.goals = state.top().goals;
                    temp.walls = state.top().walls;
                    temp.playerLocation = std::make_pair(newPlayerLocation, direction);
                    state.push(temp);
                } else {
                    auto box = std::find(state.top().boxes.begin(),
                    state.top().boxes.end(), newPlayerLocation);
                    sf::Vector2u newBoxLocation = getNewLoc(*box, direction);
                    if (newBoxLocation.x >= 0 && newBoxLocation.x < width() &&
                        newBoxLocation.y >= 0 && newBoxLocation.y < height()) {
                        if (std::find(state.top().walls.begin(), state.top().walls.end(),
                        newBoxLocation) == state.top().walls.end() &&
                        std::find(state.top().boxes.begin(), state.top().boxes.end(),
                        newBoxLocation) == state.top().boxes.end()) {
                            Grid temp;
                            temp.ground = state.top().ground;
                            temp.boxes = state.top().boxes;
                            temp.goals = state.top().goals;
                            temp.walls = state.top().walls;
                            auto tempBox = std::find
                            (temp.boxes.begin(), temp.boxes.end(), newPlayerLocation);
                            temp.boxes.erase(tempBox);
                            temp.boxes.push_back(newBoxLocation);
                            temp.playerLocation = std::make_pair(newPlayerLocation, direction);
                            state.push(temp);
                        }
                    }
                }
            }
        }
    }
}

void Sokoban::reset() {
    while (state.size() > 1) {
        state.pop();
    }
    clock.restart();
}

void Sokoban::undoMove() {
    if (state.size() > 1) {
        state.pop();
    }
}

sf::Vector2u Sokoban::getNewLoc(sf::Vector2u loc, Direction direction) {
    sf::Vector2u newLoc = loc;
    switch (direction) {
    case SB::Up:
        newLoc.y -= 1;
        break;
    case SB::Down:
        newLoc.y += 1;
        break;
    case SB::Left:
        newLoc.x -= 1;
        break;
    case SB::Right:
        newLoc.x += 1;
        break;
    }
    return newLoc;
}

char Sokoban::getPlayerTexture(Direction direction) const {
    switch (direction) {
    case SB::Up:
        return '^';
    case SB::Down:
        return '@';
    case SB::Left:
        return '<';
    case SB::Right:
        return '>';
    }
    return '@';
}

bool Sokoban::isWon() const {
    int possible = state.top().boxes.size() > state.top().goals.size()
    ? state.top().goals.size() : state.top().boxes.size();
    int count = 0;
    for (auto &box : state.top().boxes) {
        if (std::find(state.top().goals.begin(), state.top().goals.end(),
        box)!= state.top().goals.end()) {
            count++;
        }
    }

    return count == possible;
}

}  // namespace SB
