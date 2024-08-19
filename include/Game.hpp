#ifndef GAME_HPP
#define GAME_HPP
#define BoardType std::vector<std::vector<char>>
#define MINIMAX_DEPTH 7

#include <vector>
#include <string>
#include <vector>
#include "Player.hpp"
#include "Coordinates.hpp"
//#include <SFML/Graphics.hpp>


/**
 * @brief Classe Game
 * 
 * A classe Game é responsável por gerenciar o tabuleiro, os jogadores e os acontecimentos de um jogo.
 */

class Game{
    private:
        int cols; /**<Número de colunas do tabuleiro */
        int rows; /**<Número de linhas do tabuleiro */
        BoardType board; /**<Matriz que representa o tabuleiro do jogo */
        Player* player1; /**<Ponteiro para o Jogador 1 */
        Player* player2; /**<Ponteiro para o Jogador 2 */
        Player* currentPlayer; /**<Ponteiro para o jogador atual */
        Player* waitingPlayer; /**<Ponteiro para o jogador que está esperando a jogada */
    
    public:
        /**
         * @brief Construtor padrão da classe Game
         */
        Game();
      
        /**
         * @brief Construtor da classe Game
         * 
         * @param player1 Ponteiro para o jogador 1
         * @param player2 Ponteiro para o jogador 2
         */
        Game(Player* player1, Player* player2);
      
        /**
         * @brief Construtor da classe Game
         * 
         * @param player1 Ponteiro para o jogador 1
         * @param player2 Ponteiro para o jogador 2
         * @param rows Número de linhas do tabuleiro
         * @param cols Número de colunas do tabuleiro
         */
        Game(Player* player1, Player* player2, int rows, int cols);
      
        /**
         * @brief Destrutor da classe Game
         */
        virtual ~Game();

        /**
         * @brief Métodos getters para os atributos da classe Game
         * 
         * Esses métodos retornam o valor dos atributos da classe Game. 
         * 
         * @return O valor do atributo correspondente
         */
        BoardType getBoard();
        int getRows();
        int getCols();
      
        /**
         * @brief Métodos setters para os atributos da classe Game
         * 
         * Esses métodos atribuem um valor para os atributos da classe Game.
         *  
         */
        void setSquare(Coordinates coord, char symbol);
        char getSquare(Coordinates coord, const BoardType& board);

        /**
         * @brief Verifica se a jogada é válida
         * 
         * @param move Coordenadas da jogada
         * @return true se a jogada é válida, false caso contrário
         */
        bool isValidSquare(Coordinates move);
  
        /**
        *@brief Atualiza os status dos players
        *
        * @param Jogador vencedor e perdedor
        */
        virtual void addStats(Player* winner, Player* loser) = 0;
        /**
         * @brief Retorna o jogador que está esperando a jogada
         * 
         * @return Ponteiro para o jogador que está esperando a jogada
         */        

        Player* getWaitingPlayer();

        /**
         * @brief Retorna o jogador atual
         * 
         * @return Ponteiro para o jogador atual
         */
        Player* getCurrentPlayer();
        
        /**
         * @brief Ponteiro para os jogadores
         * 
         * @return Ponteiro para o jogador 1
         * @return Ponteiro para o jogador 2
         */
        Player* getPlayer1();
        Player* getPlayer2();

        /**
         * @brief Imprime o tabuleiro do jogo
         */
        void printBoard();
        
        /**
         * @brief Troca o jogador atual com o jogador que está esperando a jogada
         * 
         * Esse método é responsável por trocar o jogador atual com o jogador que está esperando a jogada.
         * 
         */
        void changePlayer();


        virtual void play() = 0;
};

#endif