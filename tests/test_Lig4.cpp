#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Lig4.hpp"
#include "doctest.h"

// Testes para a classe Lig4

TEST_CASE("Testando se a coluna está cheia") {
    Player* p1 = new Player("Jogador 1", "P1");
    Player* p2 = new Player("Jogador 2", "P2");
    Lig4 game(p1, p2);
    BoardType board = game.getBoard();

    // Simula preenchimento da coluna 1
    for (int row = 0; row < game.getRows(); row++) {
        game.makePlay(1);
    }

    CHECK(game.makePlay(1) == false);  // Coluna 1 está cheia
    CHECK_THROWS(game.makePlay(-1));   // Jogada fora dos limites
    CHECK_THROWS(game.makePlay(8));    // Jogada fora dos limites
}

TEST_CASE("Testando verificação de sequência (vitória horizontal)") {
    Player* p1 = new Player("Jogador 1", "P1");
    Player* p2 = new Player("Jogador 2", "P2");
    Lig4 game(p1, p2);
    BoardType board = game.getBoard();

    // Simulando uma vitória horizontal
    board[5][0] = 'X';
    board[5][1] = 'X';
    board[5][2] = 'X';
    board[5][3] = 'X';

    CHECK(game.verifySequence(board) == true);  // Deve retornar true, pois há uma sequência
}

TEST_CASE("Testando verificação de sequência (vitória vertical)") {
    Player* p1 = new Player("Jogador 1", "P1");
    Player* p2 = new Player("Jogador 2", "P2");
    Lig4 game(p1, p2);
    BoardType board = game.getBoard();

    // Simulando uma vitória vertical
    board[5][0] = 'O';
    board[4][0] = 'O';
    board[3][0] = 'O';
    board[2][0] = 'O';

    CHECK(game.verifySequence(board) == true);  // Deve retornar true, pois há uma sequência
}

TEST_CASE("Testando verificação de sequência (vitória diagonal)") {
    Player* p1 = new Player("Jogador 1", "P1");
    Player* p2 = new Player("Jogador 2", "P2");
    Lig4 game(p1, p2);
    BoardType board = game.getBoard();

    // Simulando uma vitória diagonal
    board[5][0] = 'X';
    board[4][1] = 'X';
    board[3][2] = 'X';
    board[2][3] = 'X';

    CHECK(game.verifySequence(board) == true);  // Deve retornar true, pois há uma sequência
}

TEST_CASE("Testando minimax") {
    Player* p1 = new Player("Jogador 1", "P1");
    Player* p2 = new Player("Jogador 2", "P2");
    Lig4 game(p1, p2);
    BoardType board = game.getBoard();

    // Simulando uma situação no tabuleiro onde a CPU precisa escolher o melhor movimento
    game.makePlay(1);
    game.makePlay(2);
    game.makePlay(3);
    // CPU joga como 'X', melhor jogada é bloquear na coluna 4

    game.changePlayer();
    int bestMove = game.bestPlay(board);
    CHECK(bestMove == 4);  // CPU deve bloquear a jogada da coluna 4
}

TEST_CASE("Testando acesso a posições inválidas") {
    Player* p1 = new Player("Jogador 1", "P1");
    Player* p2 = new Player("Jogador 2", "P2");
    Lig4 game(p1, p2);
    BoardType board = game.getBoard();

    // Testa acesso a posições fora do tabuleiro
    CHECK_THROWS(game.getSquare({-1, 0}, board));
    CHECK_THROWS(game.getSquare({0, -1}, board));
}


TEST_CASE("Testando detecção de ganhador no Lig4") {
    Player* p1 = new Player("Jogador 1", "P1");
    Player* p2 = new Player("Jogador 2", "P2");
    Lig4 game(p1, p2);

    // Teste: Vitória horizontal
    game.makePlay(1); // P1 joga na coluna 1
    game.makePlay(1); // P2 joga na coluna 1
    game.makePlay(2); // P1 joga na coluna 2
    game.makePlay(2); // P2 joga na coluna 2
    game.makePlay(3); // P1 joga na coluna 3
    game.makePlay(3); // P2 joga na coluna 3
    game.makePlay(4); // P1 joga na coluna 4 (P1 vence horizontalmente)

    CHECK(game.checkWinner(game.getBoard()) == p1); // Verifica se p1 é o vencedor

    // Reinicializar o tabuleiro para testar a vitória vertical
    game = Lig4(p1, p2);

    // Teste: Vitória vertical
    game.makePlay(1); // P1 joga na coluna 1
    game.makePlay(2); // P2 joga na coluna 2
    game.makePlay(1); // P1 joga na coluna 1
    game.makePlay(2); // P2 joga na coluna 2
    game.makePlay(1); // P1 joga na coluna 1
    game.makePlay(2); // P2 joga na coluna 2
    game.makePlay(1); // P1 joga na coluna 1 (P1 vence verticalmente)

    CHECK(game.checkWinner(game.getBoard()) == p1); // Verifica se p1 é o vencedor

    // Reinicializar o tabuleiro para testar a vitória diagonal descendente
    game = Lig4(p1, p2);

    // Teste: Vitória diagonal descendente
    game.makePlay(1); // P1 joga na coluna 1
    game.makePlay(2); // P2 joga na coluna 2
    game.makePlay(2); // P1 joga na coluna 2
    game.makePlay(3); // P2 joga na coluna 3
    game.makePlay(3); // P1 joga na coluna 3
    game.makePlay(4); // P2 joga na coluna 4
    game.makePlay(3); // P1 joga na coluna 3
    game.makePlay(4); // P2 joga na coluna 4
    game.makePlay(4); // P1 joga na coluna 4
    game.makePlay(4); // P2 joga na coluna 4 (P1 vence diagonalmente descendente)

    CHECK(game.checkWinner(game.getBoard()) == p1); // Verifica se p1 é o vencedor

    // Reinicializar o tabuleiro para testar a vitória diagonal ascendente
    game = Lig4(p1, p2);

    // Teste: Vitória diagonal ascendente
    game.makePlay(4); // P1 joga na coluna 4
    game.makePlay(3); // P2 joga na coluna 3
    game.makePlay(3); // P1 joga na coluna 3
    game.makePlay(2); // P2 joga na coluna 2
    game.makePlay(2); // P1 joga na coluna 2
    game.makePlay(1); // P2 joga na coluna 1
    game.makePlay(2); // P1 joga na coluna 2
    game.makePlay(1); // P2 joga na coluna 1
    game.makePlay(1); // P1 joga na coluna 1
    game.makePlay(1); // P2 joga na coluna 1 (P1 vence diagonalmente ascendente)

    CHECK(game.checkWinner(game.getBoard()) == p1); // Verifica se p1 é o vencedor

    delete p1;
    delete p2;
}