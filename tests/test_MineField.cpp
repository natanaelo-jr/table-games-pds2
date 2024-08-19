#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MineField.hpp"
#include "Player.hpp"

TEST_CASE("Testando o tamanho do campo: se for menor ou igual a 5 o tamanho é invalido"){
    Player* p1 = new Player("Player 1", "P1");
    CHECK_THROWS(new MineField(p1, 5, 10));
    CHECK_THROWS(new MineField(p1, 4, 10));
    CHECK_THROWS(new MineField(p1, 0, 10));
    CHECK_THROWS(new MineField(p1, -1, 10)); 
}

TEST_CASE("Testando o número de bombas: se for menor que 1 é invalido"){
    Player* p1 = new Player("Player 1", "P1");
    CHECK_THROWS(new MineField(p1, 10, 0));
    CHECK_THROWS(new MineField(p1, 10, -1));
}

TEST_CASE("Testando se a CPU pode jogar campo minado"){
    Player* p1 = new Player("Player 1", "P1");
    Player* p2 = new Player("CPU", "CPU");
    CHECK_THROWS(new MineField(p1, p2));
    CHECK_THROWS(new MineField(p2, p1));
    CHECK_THROWS(new MineField(p2, p2));
}

TEST_CASE("Testando se o campo minado foi criado corretamente"){
    Player* p1 = new Player("Player 1", "P1");
    MineField* m = new MineField(p1);
    CHECK(m->getFieldSize() == 9);
    CHECK(m->getNumberOfBombs() == 10);
    CHECK(m->isVersusGame() == false);
    delete m;
    Player* p2 = new Player("Player 2", "P2");
    m = new MineField(p1, p2);
    CHECK(m->getFieldSize() == 9);
    CHECK(m->getNumberOfBombs() == 10);
    CHECK(m->isVersusGame() == true);
    delete m;
}

TEST_CASE("Testando se o campo minado foi resetado corretamente"){
    Player* p1 = new Player("Player 1", "P1");
    MineField* m = new MineField(p1);
    m->resetGame();
    CHECK(m->getFieldSize() == 9);
    CHECK(m->getNumberOfBombs() == 10);
    CHECK(m->isVersusGame() == false);
    delete m;
    Player* p2 = new Player("Player 2", "P2");
    m = new MineField(p1, p2);
    m->resetGame();
    CHECK(m->getFieldSize() == 9);
    CHECK(m->getNumberOfBombs() == 10);
    CHECK(m->isVersusGame() == true);
    delete m;
}

TEST_CASE("Testando se o campo minado está finalizado"){
    Player* p1 = new Player("Player 1", "P1");
    MineField* m = new MineField(p1);
    CHECK(m->isGameOver() == false);
    delete m;
    m = new MineField(p1, 10, 20);
    CHECK(m->isGameOver() == false);
    delete m;
    Player* p2 = new Player("Player 2", "P2");
    m = new MineField(p1, p2);
    CHECK(m->isGameOver() == false);
    delete m;
    m = new MineField(p1, p2, 10, 20);
    CHECK(m->isGameOver() == false);
    delete m;
}

TEST_CASE("Testando se a jogada é válida"){
    Player* p1 = new Player("Player 1", "P1");
    MineField* m = new MineField(p1);
    CHECK(m->makePlay({1, 1}) == true); 
    CHECK_THROWS_WITH(m->makePlay({1, 1}), "Casa já aberta."); 
    delete m;
}