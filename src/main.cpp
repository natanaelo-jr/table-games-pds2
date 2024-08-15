#include <iostream>
#include <string>
#include <set>
#include "Players.hpp"
#include "TicTacToe.hpp"
#include "Lig4.hpp"
#include "MineField.hpp"
#include "Reversi.hpp"

int main(){
    Reversi* game = new Reversi(new Player("p1", "p1"), new Player("p2", "p2"));
    
    game->printBoard();
    
    for(auto play : game->getPossiblePlays('X', game->getBoard())){
        std::cout << play.getRow() << " " << play.getCol() << std::endl;
    }
}
