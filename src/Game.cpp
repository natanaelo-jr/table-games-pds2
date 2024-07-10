#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

//todo: Refatorar os construtores.
Game::Game() : Game(new Player("Player 1", "P1"), new Player("Player 2", "P2")){}

Game::Game(Player* player1, Player* player2) : Game(player1, player2, 3, 3){}
    
Game::Game(Player* player1, Player* player2, int cols, int rows){
    this->player1 = player1;
    this->player2 = player2;
    this->currentPlayer = this->player1;
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

bool Game::makePlay(int row, int col){
    row--;
    col--;

    if((row < rows && row >= 0) && (col < cols && col >= 0)){
        if(getSquare(row, col) != ' '){
            std::cout << "Casa já preenchida" << std::endl;
            return false;
        }

        if(getSquare(row, col) == ' '){
            if(getCurrentPlayer() == player1){
                setSquare(row, col, 'X');
                return true;
            }
            if(getCurrentPlayer() == player2){
                setSquare(row, col, 'O');
                return true;
            }
        }
    }
    std::cout << "Erro na jogada" << std::endl;
    return false;
}

char Game::getSquare(int row, int col){
    if((row < rows && row >= 0) && (col < cols && col >= 0)){
        return board[row][col];
    }
    return 'E';
}

void Game::printBoard(){
    std::cout << player1->getNickname() << " X " << player2->getName() << std::endl;
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
        return;
    }
    if(currentPlayer == player2){
        this->currentPlayer = player1;
        return;
    }
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

void Game::play(){
    while(true){
        int row, col;
        printBoard();
        std::cin >> row >> col;
        makePlay(row, col);
        changePlayer();

    }
}