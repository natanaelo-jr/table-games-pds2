#include <iostream>
#include <string>
#include <set>
#include "Players.hpp"
#include "TicTacToe.hpp"
#include "Lig4.hpp"
#include "MineField.hpp"

int main(){

    Game* game = new MineField(new Player("p1","p1"));
    game->play();
    delete game;
    return 0;
}
