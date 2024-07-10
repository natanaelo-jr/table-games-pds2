#include <iostream>
#include <string>
#include "Player.hpp"
#include "Players.hpp"
#include "TicTacToe.hpp"

int main() {
    Player* p1 = new Player("Natan", "Nana");
    Player* p2 = new Player("Julia", "Juju");

    Game* game = new TicTacToe(p1, p2);
    game->play();

    return 0;
}
