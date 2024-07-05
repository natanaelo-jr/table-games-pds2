#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
//#include <SFML/Graphics.hpp>

class Game{

    private:
        int cols;
        int rows;
        char *board;
        Player player1;
        Player player2;
        Player currentPlayer;
    
    public:
        Game();
        Game(Player player1, Player player2);
        Game(Player player1, Player player2, int rows, int cols);
        void printBoard();

    

};

#endif
