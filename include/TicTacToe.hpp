#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP


#include "Game.hpp"
#include <vector>


class TicTacToe: public Game{
    public:
        TicTacToe(Player* player1, Player*player2);
        virtual void play() override;
        bool makePlay(int row, int col);
        Player* checkWinner(const BoardType& board);
        void addStats(Player* winner, Player* loser);
        bool verifySequence(int row, int col, const BoardType& board);

        virtual std::vector<Coordinates> possiblePlays(const BoardType& board);
        bool terminalState(const BoardType &board);
        int whoseTurn(const BoardType& board);
        BoardType result(const BoardType& board, Coordinates play);
        int minimax(const BoardType& board, int alpha, int beta, bool maximizing);
        Coordinates bestPlay(const BoardType& board);
};

#endif