#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "Game.hpp"

class Reversi : public Game{
    public:
        Reversi(Player* player1, Player* player2);
        virtual void play() override;
        bool makePlay(int row, int col);
        Player* checkWinner();
        void addStats(Player* winner, Player* loser);
        int countSymbols(char symbol);
        void reverseSymbols(int row, int col);
        void initializeBoard();
        bool verifyPlay(int row, int col, char symbol); // é pra verificar se a jogada é permitida 
};

#endif