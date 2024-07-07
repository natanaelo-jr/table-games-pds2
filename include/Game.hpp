#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "Player.hpp"
//#include <SFML/Graphics.hpp>

class Game{
    private:
        int cols;
        int rows;
        char **board;
        Player player1;
        Player player2;
        Player *currentPlayer;
    
    public:
        Game();
        Game(Player player1, Player player2);
        Game(Player player1, Player player2, int rows, int cols);
        virtual ~Game();

        int getRows();
        int getCols();
        void setSquare(int row, int col, char symbol);
        char getSquare(int row, int col);
        Player* getCurrentPlayer();

        bool makePlay(int row, int col);
        void printBoard();
        void changePlayer();
        virtual void play();
};

#endif
