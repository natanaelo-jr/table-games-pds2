#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "Game.hpp"
#include "Coordinates.hpp"


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
        Coordinates searcherForPlay(int row, int col, int dRow, int dCol, char symbol, char opposite, bool passedOpponent, const BoardType &board);
        std::vector<Coordinates> getPossiblePlays(char symbol, const BoardType& board);
        bool verifyPlay(int row, int col, char symbol);
};

#endif