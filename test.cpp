// Copyright 2024 Daniel Dsouza
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Sokoban.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using SB::Sokoban;

BOOST_AUTO_TEST_CASE(test_player_move) {
    std::ifstream fp("./test.lvl");
    Sokoban game;
    fp >> game;

    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
    game.movePlayer(SB::Direction::Up);
    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 0));
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
}

BOOST_AUTO_TEST_CASE(test_player_box) {
    std::ifstream fp("./test.lvl");
    Sokoban game;
    fp >> game;

    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
    game.movePlayer(SB::Direction::Left);
    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
}

BOOST_AUTO_TEST_CASE(test_box_wall) {
    std::ifstream fp("./test.lvl");
    Sokoban game;
    fp >> game;

    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK(game.playerLoc() == sf::Vector2u(2, 1));
}

BOOST_AUTO_TEST_CASE(test_box_box) {
    std::ifstream fp("./test.lvl");
    Sokoban game;
    fp >> game;

    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
    game.movePlayer(SB::Direction::Down);
    game.movePlayer(SB::Direction::Right);
    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 2));
}

BOOST_AUTO_TEST_CASE(test_player_move_off_screen) {
    std::ifstream fp("./test.lvl");
    Sokoban game;
    fp >> game;

    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Up);
    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 0));
}

BOOST_AUTO_TEST_CASE(test_player_push_off_screen) {
    std::ifstream fp("./test.lvl");
    Sokoban game;
    fp >> game;

    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
    game.movePlayer(SB::Direction::Left);
    BOOST_CHECK(game.playerLoc() == sf::Vector2u(1, 1));
}

BOOST_AUTO_TEST_CASE(test_many_boxes) {
    std::ifstream fp("./test2.lvl");
    Sokoban game;
    fp >> game;

    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(test_many_goals) {
    std::ifstream fp("./test3.lvl");
    Sokoban game;
    fp >> game;

    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(test_missing_symbol) {
    std::ifstream fp("./sokoban/autowin.lvl");
    Sokoban game;
    fp >> game;

    fp.close();

    std::stringstream ss;

    ss << game;

    BOOST_CHECK(game.isWon());
}
