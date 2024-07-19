#ifndef LIG4_HPP
#define LIG4_HPP

#include "Game.hpp"

class Lig4 : public Game{
    public:
        Lig4(Player* player1, Player* player2);
        virtual void play() override;
        bool makePlay(int col);
        Player* checkWinner();
        void addStats(Player* winner, Player* loser);
        bool verifySequence(int row, int col);
};

#endif