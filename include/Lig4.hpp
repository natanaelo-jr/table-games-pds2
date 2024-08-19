#ifndef LIG4_HPP
#define LIG4_HPP

#include "Game.hpp"
#include <unordered_map>

class Lig4 : public Game{
    private:
        std::unordered_map<std::string, int> transpositionTable;

    public:
        Lig4(Player* player1, Player* player2);
        virtual void play() override;
        bool makePlay(int col);
        Player* checkWinner(const BoardType& board);
        void addStats(Player* winner, Player* loser)override;
        bool verifySequence(const BoardType& board);
        bool verifyRight(Coordinates c, const BoardType& board, int counter);
        bool verifyDown(Coordinates c, const BoardType& board, int counter);
        bool verifyDownRight(Coordinates c, const BoardType& board, int counter);
        bool verifyUpRight(Coordinates c, const BoardType& board, int counter);

        std::string boardToString(const BoardType& board);
        virtual std::vector<int> possiblePlays(const BoardType& board);
        bool terminalState(const BoardType &board);
        int whoseTurn(const BoardType& board);
        BoardType result(const BoardType& board, int play);
        int minimax(const BoardType& board, int alpha, int beta, bool maximizing, int depth);
        int bestPlay(const BoardType& board);
};

#endif