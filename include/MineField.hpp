#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP
#include "Game.hpp"

class MineField : public Game{
    private:
        std::vector<std::vector<int>> referenceField;
        int fieldSize;
        int numberOfBombs;
        bool versusGame;
    
    public:
        MineField(Player* player);
        MineField(Player* player, int fieldSize, int bombs);
        MineField(Player* player1, Player* player2);
        MineField(Player* player1, Player* player2, int fieldSize, int bombs);
        int getFieldSize();
        int getReference(Coordinates reference);
        int getNumberOfBombs();
        virtual void play() override;
        bool makePlay(Coordinates move);
        void setReferenceField(Coordinates firstPlay);
        void recursiveOpen(Coordinates reference);
        bool isVersusGame();
        bool isGameOver();
        void resetGame();
};

#endif