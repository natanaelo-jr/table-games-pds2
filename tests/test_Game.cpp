// Tests for the Game class
#include "Game.hpp"
#include "TicTacToe.hpp"
#include "Player.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Testando a classe Game"){
    Player* player1 = new Player("Player 1", "P1");
    Player* player2 = new Player("Player 2", "P2");
    TicTacToe* game = new TicTacToe(player1, player2);
    CHECK(game->getRows() == 3);
    CHECK(game->getCols() == 3);
    game->setSquare({0, 0}, 'X');
    CHECK(game->getSquare({0, 0}, game->getBoard()) == 'X');
    CHECK(game->isValidSquare({0, 0}) == true);
    CHECK(game->isValidSquare({-1, 0}) == false);
    CHECK(game->isValidSquare({0, -1}) == false);
    CHECK(game->isValidSquare({3, 0}) == false);
    CHECK(game->isValidSquare({0, 3}) == false);
    game->changePlayer();
    CHECK(game->getCurrentPlayer() == player2);
    CHECK(game->getWaitingPlayer() == player1);
    delete game;
    delete player1;
    delete player2;
}