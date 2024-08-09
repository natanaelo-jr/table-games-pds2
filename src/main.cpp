#include <iostream>
#include <string>
#include <set>
#include "Players.hpp"
#include "TicTacToe.hpp"
#include "Lig4.hpp"
#include "MineField.hpp"

int main(){

    Game* game = new Lig4(new Player("p1","p1"), new Player(Player("p2","p2")));
    game->play();
    delete game;
    return 0;
}
