#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

Game::Game(){
    Player player1;
    Player player2;
    this->player1 = player1;
    this->player2 = player2;
    this->currentPlayer = player1;
    cols = 3;
    rows = 3;
    board = new char[cols*rows];
}

Game::Game(Player player1, Player player2){
    this->player1 = player1;
    this->player2 = player2;
    this->currentPlayer = player1;
    cols = 3;
    rows = 3;
    board = new char[cols*rows];
    
}
Game::Game(Player player1, Player player2, int cols, int rows){
    this->player1 = player1;
    this->player2 = player2;
    this->currentPlayer = player1;
    this->cols = cols;
    this->rows = rows;
    board = new char[cols*rows];
}

void Game::printBoard(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << "| " << board[i*cols + j] << " |"; 
        }
        std::cout << std::endl;
    }
}