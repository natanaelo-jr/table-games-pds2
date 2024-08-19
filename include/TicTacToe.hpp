#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP


#include "Game.hpp"
#include <vector>

/**
 * @brief Classe TicTacToe
 * 
 * Classe responsável por gerenciar o jogo TicTacToe.
 */

class TicTacToe: public Game{
    public:
        /**
         * @brief Construtor da classe TicTacToe
         * 
         * @param player1 Ponteiro para o jogador 1
         * @param player2 Ponteiro para o jogador 2
         */
        TicTacToe(Player* player1, Player*player2);
        /**
         * @brief Método play
         * 
         * Implementa a função virtual pura da classe Game.
         */
        virtual void play() override;
        /**
         * @brief Método makePlay
         * 
         * Realiza a jogada do jogador atual.
         * 
         * @param play Coordenadas da jogada
         * @return Verdadeiro se a jogada foi realizada com sucesso e falso caso contrário
         */
        bool makePlay(Coordinates play);
        /**
         * @brief Método checkWinner
         * 
         * Verifica se há um vencedor no jogo.
         * 
         * @param board Tabuleiro do jogo
         * @return Ponteiro para o jogador vencedor
         */
        Player* checkWinner(const BoardType& board);
        /**
         * @brief Método addStats
         * 
         * Adiciona as estatísticas de vitória e derrota no jogo TicTacToe dos jogadores.
         * 
         * @param winner Ponteiro para o jogador vencedor
         * @param loser Ponteiro para o jogador perdedor
         */
        void addStats(Player* winner, Player* loser);
        /**
         * @brief Método verifySequence
         * 
         * Verifica se há uma sequência de 3 peças iguais no tabuleiro.
         * 
         * @param board Tabuleiro do jogo
         * @return Verdadeiro se houver uma sequência e falso caso contrário
         */
        bool verifySequence(const BoardType& board);
        
        bool verifyRight(Coordinates c, const BoardType& board, int counter);
        bool verifyDown(Coordinates c, const BoardType& board, int counter);
        bool verifyDownRight(Coordinates c, const BoardType& board, int counter);
        bool verifyUpRight(Coordinates c, const BoardType& board, int counter);
        
        /**
         * @brief Método possiblePlays
         * 
         * armazena todas as jogadas possíveis a partir de um tabuleiro
         * 
         * @param board Tabuleiro do jogo
         * @return Vetor de coordinates com as jogadas possíveis
         */
        virtual std::vector<Coordinates> possiblePlays(const BoardType& board); 
        /**
         * @brief Método terminalState
         * 
         * Verifica se o jogo chegou a um estado terminal
         * 
         * @param board Tabuleiro do jogo
         * @return Verdadeiro se o jogo chegou a um estado terminal e falso caso contrário
         */
        bool terminalState(const BoardType &board);
        /**
         * @brief Método whoseTurn
         * 
         * Retorna o jogador que deve realizar a próxima jogada
         * 
         * @param board Tabuleiro do jogo
         * @return 1 ou 2 dependendo do jogador que deve jogar
         */
        int whoseTurn(const BoardType& board);
        /**
         * @brief Método result
         * 
         * Retorna o tabuleiro resultante de uma jogada
         * 
         * @param board Tabuleiro do jogo
         * @param play Coordenadas da jogada
         * @return Tabuleiro resultante da jogada
         */
        BoardType result(const BoardType& board, Coordinates play);
        /**
         * @brief Método minimax
         * 
         * Implementa o algoritmo minimax para o jogo TicTacToe
         * 
         * @param board Tabuleiro do jogo
         * @param alpha Valor de alpha
         * @param beta Valor de beta
         * @param maximizing Verdadeiro se é a vez do jogador maximizador e falso caso contrário
         * @return Valor da jogada (quanto maior melhor a jogada)
         */
        int minimax(const BoardType& board, int alpha, int beta, bool maximizing);
        /**
         * @brief Método bestPlay
         * 
         * Retorna a melhor jogada para o método minimax
         * 
         * @param board Tabuleiro do jogo
         * @return Coordenadas da melhor jogada encontrada
         */
        Coordinates bestPlay(const BoardType& board);
};

#endif