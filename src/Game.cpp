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
    board = std::vector<std::vector<char>>(rows, std::vector<char>(cols, ' '));
}
Game::~Game(){
}

int Game::getRows(){
    return rows;
}

int Game::getCols(){
    return cols;
}


void Game::setSquare(Coordinates coord, char symbol){
    board[coord.getRow()][coord.getCol()] = symbol;
}

bool Game::isValidSquare(Coordinates move){
    if(move.getRow() < 0 || move.getRow() >= rows || move.getCol() < 0 || move.getCol() >= cols){
        return false;
    }
    return true;
}

char Game::getSquare(Coordinates coord, const BoardType& board){
    if(!isValidSquare(coord)){
        throw std::invalid_argument("Invalid square");
    }
    return board[coord.getRow()][coord.getCol()];
}

void Game::printBoard(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            std::cout << "| " << getSquare({i, j}, getBoard()) << " |"; 
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

std::vector<std::vector<char>> Game::getBoard(){
    return board;
}