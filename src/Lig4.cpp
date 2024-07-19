#include "Lig4.hpp"
#include <iostream>

Lig4::Lig4(Player* player1, Player* player2) : Game(player1, player2, 6, 7){}

void Lig4::play(){
    Player* winner = nullptr;
    printBoard();
    while(true){
        if(isFull()){
            //todo: implementar a saída de empate. (igual tictactoe)
            break;
        }

        //todo: Refatorar a funcao [melhorar if else] (igual tictactoe)
        int col;
        std::cin >> col;
        if(makePlay(col)){
            winner = checkWinner();
            if(winner != nullptr){
                printBoard();
                addStats(winner, getWaitingPlayer());
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

Player* Lig4::checkWinner(){
    for(int row = getRows()-1; row >= 0; row--){
        for(int col = 0; col < getCols(); col++){
            if(verifySequence(row, col)){
                return getCurrentPlayer();
            }
        }
    }
    return nullptr;
}

bool Lig4::makePlay(int col){
    col--;
    for(int row = getRows()-1; row >= 0; row--){
        if(getSquare(row, col) == ' '){
            getCurrentPlayer() == getPlayer1() ? setSquare(row, col, 'X') : setSquare(row, col, 'O');
            return true;
        }else if(row == 0){
            std::cout << "Coluna Cheia!" << std::endl;
            return false;
        }
    }
    std::cout << "Erro na jogada!" << std::endl;
    return false;
}

void Lig4::addStats(Player* winner, Player* loser){
    winner->increaseVictories();
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;
    loser->increaseDefeats();
}

bool Lig4::verifySequence(int row, int col){
    bool horizontal = true;
    bool vertical = true;
    bool upDiagonal = true;
    bool downDiagonal = true;
    char symbol = getSquare(row, col);

    if(symbol == 'E' || symbol == ' '){
        return false;
    }

    for(int i = 1; i < 4; i++){
        if(getSquare(row+i, col) != symbol){
            horizontal = false;
            break;
        }
    }

    for(int i = 1; i < 4; i++){
        if(getSquare(row, col+i) != symbol){
            vertical = false;
            break;
        }
    }

    for(int i = 1; i < 4; i++){
        if(getSquare(row+i, col+i)){
            downDiagonal = false;
            break;
        }
    }

    for(int i = 1; i < 4; i++){
        if(getSquare(row-i, col+i)){
            upDiagonal = false;
            break;
        }
    }
    return horizontal || vertical || upDiagonal || downDiagonal;
}
