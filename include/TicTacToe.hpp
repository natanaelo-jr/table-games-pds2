#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "Game.hpp"

class TicTacToe: public Game{
    public:
        //todo: Fazer os construtores reaproveitando a papai.

        void play();
        Player* checkWinner();
        bool verifySequence(int row, int col);
        bool isFull();
};
#endif