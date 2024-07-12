#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "Game.hpp"

class TicTacToe: public Game{
    public:
        TicTacToe();
        TicTacToe(Player* player1, Player*player2);

        void play();
        Player* checkWinner();
        void win(Player* player);
        bool verifySequence(int row, int col);
        bool isFull();
};
#endif