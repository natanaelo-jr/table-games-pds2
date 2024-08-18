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
    
    
    for(auto play : game->getPossiblePlays('O', game->getBoard())){
        game->setSquare(play, '.');
    }

    game->printBoard();
    game->turnPieces(3, 0, 5, -1, 'X', true, game->getBoard());
    game->printBoard();
}
