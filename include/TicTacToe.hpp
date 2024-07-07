#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "Game.hpp"

class TicTacToe: public Game{
    public:
        TicTacToe();
        TicTacToe(Player player1, Player player2);
        TicTacToe(Player player1, Player player2, int cols, int rows);

        void play();
        Player* checkWinner();
        bool verifySequence(int row, int col);
        bool isFull();
};
#endif