#ifndef LIG4_HPP
#define LIG4_HPP

#include "Game.hpp"

class Lig4 : public Game{
    public:
        Lig4(Player* player1, Player* player2);
        virtual void play() override;
        bool makePlay(int col);
        Player* checkWinner(const BoardType& board);
        void addStats(Player* winner, Player* loser);
        bool verifySequence(int row, int col, const BoardType& board);

        virtual std::vector<int> possiblePlays(const BoardType& board);
        bool terminalState(const BoardType &board);
        int whoseTurn(const BoardType& board);
        BoardType result(const BoardType& board, int play);
        int minimax(const BoardType& board, int alpha, int beta, bool maximizing, int depth);
        int bestPlay(const BoardType& board);
};

#endif