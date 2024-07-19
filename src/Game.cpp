#include <iostream>
#include "Game.hpp"
#include "Player.hpp"


Game::Game() : Game(new Player("Player 1", "P1"), new Player("Player 2", "P2")){}

Game::Game(Player* player1, Player* player2) : Game(player1, player2, 3, 3){}
    
Game::Game(Player* player1, Player* player2, int cols, int rows){
    this->player1 = player1;
    this->player2 = player2;
    this->currentPlayer = this->player1;
    this->waitingPlayer = this->player2;
    this->cols = cols;
    this->rows = rows;

    board = new char*[rows];
    for(int i = 0; i < rows; i++){
        board[i] = new char[cols];
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
            board[i][j] = ' ';
    }
}

Game::~Game(){
    for(int i = 0; i < rows; i++){
        delete[] board[i];
    }
    delete board;
}

int Game::getRows(){
    return rows;
}

int Game::getCols(){
    return cols;
}


void Game::setSquare(int row, int col, char symbol){
    board[row][col] = symbol;
}



char Game::getSquare(int row, int col){
    if((row < rows && row >= 0) && (col < cols && col >= 0)){
        return board[row][col];
    }
    return 'E';
}

bool Game::isFull(){
    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(getSquare(row, col) == ' '){
                return false;
            }
        }
    }
    return true;
}

void Game::printBoard(){
    std::cout << player1->getNickname() << " X " << player2->getNickname() << std::endl;
    std::cout << "Vez de " << currentPlayer->getNickname() << std::endl;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << "| " << getSquare(i, j) << " |"; 
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

void Game::changePlayer(){
    if(currentPlayer == player1){
        this->currentPlayer = player2;
        this->waitingPlayer = player1;
        return;
    }
    if(currentPlayer == player2){
        this->currentPlayer = player1;
        this->waitingPlayer = player2;
        return;
    }
}

Player* Game::getWaitingPlayer(){
    return waitingPlayer;
}

Player* Game::getCurrentPlayer(){
    return currentPlayer;
}

Player* Game::getPlayer1(){
    return player1;
}

Player* Game::getPlayer2(){
    return player2;
}
