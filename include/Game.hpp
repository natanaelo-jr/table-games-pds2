#ifndef GAME_HPP
#define GAME_HPP
#define BoardType std::vector<std::vector<char>>
#define MINIMAX_DEPTH 8

#include <vector>
#include <string>
#include "Player.hpp"
#include "Coordinates.hpp"
//#include <SFML/Graphics.hpp>

class Game{
    private:
        int cols;
        int rows;
        BoardType board;
        Player* player1;
        Player* player2;
        Player* currentPlayer;
        Player* waitingPlayer;
    
    public:
        Game();
        Game(Player* player1, Player* player2);
        Game(Player* player1, Player* player2, int rows, int cols);
        virtual ~Game();

        BoardType getBoard();
        int getRows();
        int getCols();
        void setSquare(Coordinates coord, char symbol);
        char getSquare(Coordinates coord, const BoardType& board);
        bool isValidSquare(Coordinates move);
                
        Player* getWaitingPlayer();
        Player* getCurrentPlayer();
        Player* getPlayer1();
        Player* getPlayer2();

        void printBoard();
        void changePlayer();
        virtual void play() = 0;
};

#endif