#include "Lig4.hpp"
#include <iostream>

Lig4::Lig4(Player* player1, Player* player2) : Game(player1, player2, 7, 6){}

void Lig4::play(){
    Player* winner = nullptr;
    //todo: Implementar
}

Player* Lig4::checkWinner(){
    //todo Implementar
}

bool Lig4::makePlay(int col){
    col--;
    if(getSquare(0 ,col) == 'E'){ //todo: Tratar melhor o erro
        return false;
    }
    for(int row = getRows(); row >= 0; row--){
        if(getSquare(row, col) == ' '){
            getCurrentPlayer() == getPlayer1() ? setSquare(row, col, 'X') : setSquare(row, col, 'O');
            return true;
        }else if(row == 0){
            std::cout << "Coluna Cheia" << std::endl;
            return false;
        }
    }
}

void Lig4::addStats(Player* winner, Player* loser){
    winner->increaseVictories();
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;
    loser->increaseDefeats();
}

bool Lig4::verifySequence(){
    //todo: Implementar
    return false;
}
