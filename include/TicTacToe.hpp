#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "Game.hpp"

class TicTacToe: public Game{
    public:
        TicTacToe(Player* player1, Player*player2);
        virtual void play() override;
        bool makePlay(int row, int col);
        Player* checkWinner();
        void addStats(Player* winner, Player* loser);
        bool verifySequence(int row, int col);
};

#endif