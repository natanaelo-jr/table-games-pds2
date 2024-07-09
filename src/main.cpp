#include <iostream>
#include "Player.hpp"
#include "Game.hpp"
#include "TicTacToe.hpp"

int main(){
    
    TicTacToe *game = new TicTacToe();
    game->play();
    
    return 0;
}