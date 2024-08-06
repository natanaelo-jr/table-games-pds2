#ifndef GAME_HPP
#define GAME_HPP
#define BoardType std::vector<std::vector<char>>
#define MINIMAX_DEPTH 8

#include <vector>
#include <string>
#include "Player.hpp"
//#include <SFML/Graphics.hpp>

class Coordinates {
    public:
        int row;
        int col;
};

class Game{
    private:
        int cols;
        int rows;
        std::vector<std::vector<char>> board;
        Player* player1;
        Player* player2;
        Player* currentPlayer;
        Player* waitingPlayer;
    
    public:
        Game();
        Game(Player* player1, Player* player2);
        Game(Player* player1, Player* player2, int rows, int cols);
        virtual ~Game();

        std::vector<std::vector<char>> getBoard();
        int getRows();
        int getCols();
        void setSquare(int row, int col, char symbol);
        char getSquare(int row, int col, const BoardType& board);
                
        Player* getWaitingPlayer();
        Player* getCurrentPlayer();
        Player* getPlayer1();
        Player* getPlayer2();

        void printBoard();
        void changePlayer();
        virtual void play() = 0;
};

#endif