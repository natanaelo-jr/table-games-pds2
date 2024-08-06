#include <iostream>
#include <string>
#include <set>
#include "Player.hpp"
#include "Players.hpp"
#include "TicTacToe.hpp"
#include "Lig4.hpp"

int main(){
    Player* p1 = new Player("Jorge", "P1");
    Player* p2 = new Player("CPU", "P2");
    Game* game;
    game = new Lig4(p1, p2);
    game->play();
    delete game;


    
  
    return 0;
}
