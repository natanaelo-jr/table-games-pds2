#include "TicTacToe.hpp"
#include <iostream>

TicTacToe::TicTacToe(Player* player1, Player* player2) : Game(player1, player2, 3, 3){}

void TicTacToe::play(){
    Player* winner = nullptr;
    printBoard();

    while(true){
        if(isFull()){
            //todo: Refatorar a verificação de empate.
            break;
        }

        //todo: Refatorar a funcao [melhorar if else]
        int row, col;
        std::cin >> row >>  col;
        if(makePlay(row, col)){
            winner = checkWinner();
            if(winner != nullptr){
                printBoard();
                win(winner);
                break;
            }
            else{
                changePlayer();
                printBoard();
            }
        }
        else{
            printBoard();
        }
    }
}

void TicTacToe::win(Player* winner){
    winner->increaseVictories();
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;

    if(winner == getPlayer1()){
        getPlayer2()->increaseDefeats();
    }
    if(winner == getPlayer2()){
        getPlayer1()->increaseDefeats();
    }
}

bool TicTacToe::isFull(){
    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(getSquare(row, col) == ' '){
                return false;
            }
        }
    }
    return true;
}

bool TicTacToe::verifySequence(int row, int col){
    char symbol = getSquare(row, col);
    bool vertical = true;
    bool horizontal = true;
    bool diagonaldown = true;
    bool diagonalup = true;

    if(symbol == 'E'){
        //todo Exception error
    }
    if(symbol == ' '){
        return false;
    }
    //verifyVertical
    for(int i = 0; i < 3; i++){
        if(getSquare(row+i,col) != symbol){
            vertical = false;
            break;
        }
    }
    //verifyHorizontal
    for(int i = 0; i < 3; i++){
        if(getSquare(row,col+i) != symbol){
            horizontal = false;
            break;
        }
    }
    //verifyDiagonals
    for(int i = 0; i < 3; i++){
        if(getSquare(row+i,col+i) != symbol){
            diagonaldown = false;
            break;
        }
    }
    for(int i = 0; i < 3; i++){
        if(getSquare(row-i,col+i) != symbol){
            diagonalup = false;
            break;
        }
    }

    return vertical || horizontal || diagonaldown || diagonalup;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
}

Player* TicTacToe::checkWinner(){
    for(int row = 0; row < getRows(); row++){
        if(verifySequence(row, 0)){
            return getCurrentPlayer();
        }    
    }

    for(int col = 1; col < getCols(); col++){
        if(verifySequence(0, col)){
            return getCurrentPlayer();
        }
    }
    return nullptr;
}