#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Reversi.hpp"

TEST_CASE("Testando a inicialização do tabuleiro") {
    Player player1("Jogador1", "X");
    Player player2("Jogador2", "O");
    Reversi game(&player1, &player2);

    SUBCASE("O tabuleiro inicial está configurado corretamente") {
        CHECK(game.getSquare({3, 3}, game.getBoard()) == 'X');
        CHECK(game.getSquare({4, 4}, game.getBoard()) == 'X');
        CHECK(game.getSquare({3, 4}, game.getBoard()) == 'O');
        CHECK(game.getSquare({4, 3}, game.getBoard()) == 'O');
    }
}

TEST_CASE("Testando jogadas válidas e inválidas") {
    Player player1("Jogador1", "X");
    Player player2("Jogador2", "O");
    Reversi game(&player1, &player2);

    SUBCASE("Tentando uma jogada inválida") {
        // tentativa de jogar em uma posição  ocupada ou fora das jogadas possíveis
        CHECK_FALSE(game.makePlay(3, 3));  // ocupado
        CHECK_FALSE(game.makePlay(7, 7));  // jogada inválida
    }

    SUBCASE("Tentando uma jogada válida") {
        //  Jogada válida que resulta na captura de peças
        CHECK(game.makePlay(4, 2));  //  X joga nesta posição
        CHECK(game.getSquare({4, 2}, game.getBoard()) == 'X');  //  peça  colocada corretamente
        CHECK(game.getSquare({4, 3}, game.getBoard()) == 'X');  //  peça do lado foi revertida
    }
}

TEST_CASE("Testando verificação de jogadas possíveis") {
    Player player1("Jogador1", "X");
    Player player2("Jogador2", "O");
    Reversi game(&player1, &player2);

    SUBCASE("Jogadas possíveis para o jogador X") {
        std::vector<Coordinates> possiblePlays = game.getPossiblePlays('X', game.getBoard());
        std::set<Coordinates> expectedPlays = {{2, 4}, {4, 2}, {5, 3}, {3, 5}};
        
        CHECK_EQ(possiblePlays.size(), expectedPlays.size());
        for(auto& play : possiblePlays){
            CHECK(expectedPlays.find(play) != expectedPlays.end());
        }
    }

    SUBCASE("Jogadas possíveis para o jogador O") {
        std::vector<Coordinates> possiblePlays = game.getPossiblePlays('O', game.getBoard());
        std::set<Coordinates> expectedPlays = {{2, 3}, {5, 4}, {4, 5}, {3, 2}};
        
        CHECK_EQ(possiblePlays.size(), expectedPlays.size());
        for(auto& play : possiblePlays){
            CHECK(expectedPlays.find(play) != expectedPlays.end());
        }
    }
}

TEST_CASE("Testando o estado terminal e o vencedor") {
    Player player1("Jogador1", "X");
    Player player2("Jogador2", "O");
    Reversi game(&player1, &player2);

    SUBCASE("O jogo não está em estado terminal") {
        CHECK_FALSE(game.terminalState(game.getBoard()));
    }

    SUBCASE("Estado terminal quando não há mais jogadas") {
        // Removendo as 4 casas iniciais para não gerar possibilidade de jogada
        game.setSquare({4, 3}, ' ');
        game.setSquare({3, 3}, ' ');
        game.setSquare({3, 4}, ' ');
        game.setSquare({4, 4}, ' ');        
        
        // Simulação de jogadas que não permitem mais jogadas
        game.makePlay(1, 1);
        game.makePlay(4, 2); 

        CHECK(game.terminalState(game.getBoard()));
    }
}


TEST_CASE("Testando a determinação do ganhador") {
    Player player1("Jogador1", "X");
    Player player2("Jogador2", "O");
    Reversi game(&player1, &player2);

    SUBCASE("Jogador X vence com mais peças no tabuleiro") {
        // X tem mais peças do que O
        game.setSquare({0, 0}, 'X');
        game.setSquare({0, 1}, 'X');
        game.setSquare({0, 2}, 'X');
        game.setSquare({0, 3}, 'X');
        game.setSquare({0, 4}, 'X');
        game.setSquare({0, 5}, 'X');
        game.setSquare({0, 6}, 'X');
        game.setSquare({0, 7}, 'X');

        game.setSquare({1, 0}, 'O');
        game.setSquare({1, 1}, 'O');
        game.setSquare({1, 2}, 'O');
        game.setSquare({1, 3}, 'O');

        // verificando do vencedor
        Player* winner = game.checkWinner();
        CHECK(winner == &player1);  // X ganha
    }

    SUBCASE("Jogador O vence com mais peças no tabuleiro") {
        // O tem mais peças do que X
        game.setSquare({0, 0}, 'O');
        game.setSquare({0, 1}, 'O');
        game.setSquare({0, 2}, 'O');
        game.setSquare({0, 3}, 'O');
        game.setSquare({0, 4}, 'O');
        game.setSquare({0, 5}, 'O');
        game.setSquare({0, 6}, 'O');
        game.setSquare({0, 7}, 'O');

        game.setSquare({1, 0}, 'X');
        game.setSquare({1, 1}, 'X');
        game.setSquare({1, 2}, 'X');
        game.setSquare({1, 3}, 'X');


        // verificando o vencedor
        Player* winner = game.checkWinner();
        CHECK(winner == &player2);  // Y ganha
    }

    SUBCASE("Empate no jogo") {
        // X e Y com o mesmo número de casas
        game.setSquare({0, 0}, 'X');
        game.setSquare({0, 1}, 'X');
        game.setSquare({0, 2}, 'X');
        game.setSquare({0, 3}, 'X');

        game.setSquare({0, 4}, 'O');
        game.setSquare({0, 5}, 'O');
        game.setSquare({0, 6}, 'O');
        game.setSquare({0, 7}, 'O');


        // verificando o vencedor
        Player* winner = game.checkWinner();
        CHECK(winner == nullptr);
    }
}
