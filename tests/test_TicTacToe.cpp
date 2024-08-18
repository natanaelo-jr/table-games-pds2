#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//tests for the TicTacToe class
#include "TicTacToe.hpp"
#include "doctest.h"

TEST_CASE("Testando a classe TicTacToe"){
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

TEST_CASE("Testando a função makePlay"){
    Player* player1 = new Player("Player 1", "P1");
    Player* player2 = new Player("Player 2", "P2");
    TicTacToe* game = new TicTacToe(player1, player2);
    CHECK(game->makePlay({1, 1}) == true);
    CHECK(game->makePlay({1, 1}) == false);
    CHECK(game->makePlay({1, 2}) == true);
    CHECK(game->makePlay({1, 3}) == true);
    CHECK(game->makePlay({2, 1}) == true);
    CHECK(game->makePlay({2, 2}) == true);
    CHECK(game->makePlay({2, 3}) == true);
    CHECK(game->makePlay({3, 1}) == true);
    CHECK(game->makePlay({3, 2}) == true);
    CHECK(game->makePlay({3, 3}) == true);
    CHECK(game->makePlay({3, 3}) == false);
    delete game;
    delete player1;
    delete player2;
}


TEST_CASE("Testando a função terminalState"){
    Player* player1 = new Player("Player 1", "P1");
    Player* player2 = new Player("Player 2", "P2");
    TicTacToe* game = new TicTacToe(player1, player2);
    CHECK(game->terminalState(game->getBoard()) == false);
    game->setSquare({0, 0}, 'X');
    game->setSquare({0, 1}, 'X');
    game->setSquare({0, 2}, 'X');
    CHECK(game->terminalState(game->getBoard()) == true);
    delete game;
    delete player1;
    delete player2;
}


TEST_CASE("Testando a função verifySequence"){
    Player* player1 = new Player("Player 1", "P1");
    Player* player2 = new Player("Player 2", "P2");
    TicTacToe* game = new TicTacToe(player1, player2);
    game->setSquare({0, 0}, 'X');
    game->setSquare({0, 1}, 'X');
    game->setSquare({0, 2}, 'X');
    CHECK(game->verifySequence(game->getBoard()) == true);
    game->setSquare({0, 0}, 'O');
    game->setSquare({1, 0}, 'O');
    game->setSquare({2, 0}, 'O');
    CHECK(game->verifySequence(game->getBoard()) == true);
    game->setSquare({0, 0}, 'X');
    game->setSquare({1, 1}, 'X');
    game->setSquare({2, 2}, 'X');
    CHECK(game->verifySequence(game->getBoard()) == true);
    game->setSquare({0, 2}, 'O');
    game->setSquare({1, 1}, 'O');
    game->setSquare({2, 0}, 'O');
    CHECK(game->verifySequence(game->getBoard()) == true);
    delete game;
    delete player1;
    delete player2;
}


TEST_CASE("Testando a função whoseTurn"){
    Player* player1 = new Player("Player 1", "P1");
    Player* player2 = new Player("Player 2", "P2");
    TicTacToe* game = new TicTacToe(player1, player2);
    CHECK(game->whoseTurn(game->getBoard()) == 1);
    game->setSquare({0, 0}, 'X');
    CHECK(game->whoseTurn(game->getBoard()) == 2);
    game->setSquare({0, 1}, 'O');
    CHECK(game->whoseTurn(game->getBoard()) == 1);
    game->setSquare({0, 2}, 'X');
    CHECK(game->whoseTurn(game->getBoard()) == 2);
    game->setSquare({1, 0}, 'O');
    CHECK(game->whoseTurn(game->getBoard()) == 1);
    game->setSquare({1, 1}, 'X');
    CHECK(game->whoseTurn(game->getBoard()) == 2);
    game->setSquare({1, 2}, 'O');
    CHECK(game->whoseTurn(game->getBoard()) == 1);
    game->setSquare({2, 0}, 'X');
    CHECK(game->whoseTurn(game->getBoard()) == 2);
    game->setSquare({2, 1}, 'O');
    CHECK(game->whoseTurn(game->getBoard()) == 1);
    game->setSquare({2, 2}, 'X');
    CHECK(game->whoseTurn(game->getBoard()) == 2);
    delete game;
    delete player1;
    delete player2;
}   






