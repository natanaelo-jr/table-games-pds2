#include "Reversi.hpp"
#include <iostream>
#include <vector>
#include <iterator>

Reversi::Reversi(Player* player1, Player* player2) : Game(player1, player2, 8, 8) {
    initializeBoard();
}

void Reversi::initializeBoard() {
    setSquare({4, 3}, 'O');
    setSquare({3, 3}, 'X');
    setSquare({3, 4}, 'O');
    setSquare({4, 4}, 'X');
}

void Reversi::play(){
    /*Player* winner = nullptr;
    printBoard();
    while(true){
        if(getPossiblePlays('X', getBoard()).size() == 0){
            winner = checkWinner();
        break;
        }
        
        int row, col;
        std::cin >> row >> col;
    }*/
}
// passedOpponent inciar como false no primeira chamada
Coordinates Reversi::searcherForPlay(int row, int col, int dRow, int dCol, char symbol, char opposite, bool passedOpponent, const BoardType &board) {
    if (row > 7 || row < 0 || col > 7 || col < 0)
        return {-1, -1};
    if (getSquare({row, col}, board) == ' ' && passedOpponent) {
        Coordinates validPlay (row, col);
        return validPlay;
    }
    // Se encontrar uma casa vazia sem passar por uma peça do oponente, a jogada não é válida
    if (getSquare({row, col}, board) == ' ') {
        return {-1, -1};
    }
    // Se encontrar uma peça do próprio jogador antes de passar por uma peça do oponente, a jogada não é válida
    if (getSquare({row, col}, board) == symbol) {
        return {-1, -1};
    }
    // Se encontrar uma peça do oponente, continua a busca na mesma direção
    if (getSquare({row, col}, board) == opposite) {
        return searcherForPlay(row + dRow, col + dCol, dRow, dCol, symbol, opposite, true, board);
    }
    return {-1, -1};
}


std::vector<Coordinates> Reversi::getPossiblePlays(char symbol, const BoardType &board){
    std::vector<Coordinates> validPlays;
    char opposite = (symbol == 'X') ? 'O' : 'X';
    // PROCURANDO O SÍMBOLO NO BOARD
    for (int row = 0; row < 7; row++) 
    {
        for (int col = 0; col < 7; col++)
        {
            if (getSquare({row, col}, board) == symbol)
            {
                // Array de direções: {dRow, dCol}
                int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};

                for (int i = 0; i < 8; i++) {
                    int dRow = directions[i][0];
                    int dCol = directions[i][1];

                    Coordinates aux = searcherForPlay(row + dRow, col + dCol, dRow, dCol, symbol, opposite, false, board);
                    if (aux.getRow() != -1 && aux.getCol() != -1) {
                        validPlays.push_back(aux);
                    }       
                }
            } 
        }
    } 
    return validPlays;
}
bool Reversi::verifyPlay(int row, int col, char symbol){
    std::vector<Coordinates> validPlays = getPossiblePlays(symbol, getBoard());
    if (validPlays.size() == 0) {
        return false;
    }
    for (auto play : validPlays) {
        if (play.getRow() == row && play.getCol() == col) {
            return true;
        }
    }
    return false;
}

void Reversi::reverseSymbols(int row, int col){
    char symbol = getSquare({row, col}, getBoard());
    if (symbol == 'X')
        setSquare ({row, col}, 'O');
    else if (symbol == 'O')
        setSquare ({row, col}, 'X');
    else 
        setSquare ({row, col}, ' ');
}



int Reversi::countSymbols(char symbol){
    int counter = 0;
    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(getSquare({row, col}, getBoard()) == symbol){
                counter++;
            }
        }
    }
    return counter;
}


Player* Reversi::checkWinner(){
    int xCount = countSymbols('X');
    int oCount = countSymbols('O');

    if (xCount > oCount) {
        return getPlayer1(); 
    } 
    else if (oCount > xCount) {
        return getPlayer2();
    } 
    else {
        return nullptr;
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                  