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
        virtual void play() override;
        bool makePlay(Coordinates play);
        Player* checkWinner(const BoardType& board);
        void addStats(Player* winner, Player* loser);
        bool verifySequence(const BoardType& board);
        bool verifyRight(Coordinates c, const BoardType& board, int counter);
        bool verifyDown(Coordinates c, const BoardType& board, int counter);
        bool verifyDownRight(Coordinates c, const BoardType& board, int counter);
        bool verifyUpRight(Coordinates c, const BoardType& board, int counter);
        
        virtual std::vector<Coordinates> possiblePlays(const BoardType& board);
        bool terminalState(const BoardType &board);
        int whoseTurn(const BoardType& board);
        BoardType result(const BoardType& board, Coordinates play);
        
        int minimax(const BoardType& board, int alpha, int beta, bool maximizing);
        Coordinates bestPlay(const BoardType& board);
};

#endif