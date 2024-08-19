#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Player.hpp"
#include "doctest.h"


TEST_CASE("Testando a classe Player"){
    Player* player = new Player("Player 1", "P1");
    CHECK(player->getName() == "Player 1");
    CHECK(player->getNickname() == "P1");
    CHECK(player->getVictories() == 0);
    CHECK(player->getDefeats() == 0);
    player->setName("Player 2");
    CHECK(player->getName() == "Player 2");
    player->setNickname("P2");
    CHECK(player->getNickname() == "P2");
    player->winTicTacToe();
    CHECK(player->getTicTacToeVictories() == 1);
    player->loseTicTacToe();
    CHECK(player->getTicTacToeDefeats() == 1);
    player->winLig4();
    CHECK(player->getLig4Victories() == 1);
    player->loseLig4();
    CHECK(player->getLig4Defeats() == 1);
    player->winReversi();
    CHECK(player->getReversiVictories() == 1);
    player->loseReversi();
    CHECK(player->getReversiDefeats() == 1);
    player->winMinefield();
    CHECK(player->getMinefieldVictories() == 1);
    player->loseMinefield();
    CHECK(player->getMinefieldDefeats() == 1);
    delete player;
}

TEST_CASE("Testando entradas de name e nickname quando nome é vazio e nickname é vazio"){
    CHECK_THROWS(new Player("", "P1"));
    CHECK_THROWS(new Player("Player 1", ""));
    CHECK_THROWS(new Player("Player 1", "Nomemuitogrande"));   
}







