#include "TicTacToe.hpp"
#include <iostream>

TicTacToe::TicTacToe(Player* player1, Player* player2) : Game(player1, player2, 3, 3){}

void TicTacToe::play(){
    Player* winner = nullptr;
    Coordinates currentPlay;
    printBoard();
    while(true){
        if(possiblePlays(getBoard()).size() == 0){
            std::cout << "Empate!" << std::endl;
            if(getPlayer1()->getName() == "CPU" || getPlayer2()->getName() == "CPU"){
                std::cout << "Partidas contra o computador não contam para as estatísticas." << std::endl;
            }
            break;
        }
        if(getCurrentPlayer()->getName() == "CPU"){
            currentPlay = bestPlay(getBoard());
            std::cout << "Best Move is: " << currentPlay.row << " " << currentPlay.col << std::endl;
        }
        else{
            std::cout << "Vez de " << getCurrentPlayer()->getNickname() << std::endl;
            std::cout << "Digite a linha e a coluna da sua jogada: ";
            std::cin >> currentPlay.row >> currentPlay.col;
        }

        if(makePlay(currentPlay.row, currentPlay.col)){
            winner = checkWinner(getBoard());
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

bool TicTacToe::makePlay(int row, int col){
    row--;
    col--;

    if((row < getRows() && row >= 0) && (col < getCols() && col >= 0)){
        if(getSquare(row, col, getBoard()) != ' '){
            std::cout << "Casa já preenchida!" << std::endl;
            return false;
        }
        if(getSquare(row, col, getBoard()) == ' '){
            if(getCurrentPlayer() == getPlayer1()){
                setSquare(row, col, 'X');
                return true;
            }
            if(getCurrentPlayer() == getPlayer2()){
                setSquare(row, col, 'O');
                return true;
            }
        }
    }
    std::cout << "Erro na jogada!" << std::endl;
    return false;
}

void TicTacToe::addStats(Player* winner, Player* loser){
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;
    if(winner->getName() == "CPU" || loser->getName() == "CPU"){
        std::cout << "Partidas contra o computador não contam para as estatísticas." << std::endl;
        return;
    }
    winner->increaseVictories();
    loser->increaseDefeats();
}

bool TicTacToe::verifySequence(int row, int col, const BoardType &board){
    char symbol = getSquare(row, col, board);
    bool vertical = true;
    bool horizontal = true;
    bool downDiagonal = true;
    bool upDiagonal = true;

    if(symbol == 'E' || symbol == ' '){
        return false;
    }

    //verifyVertical
    for(int i = 1; i < 3; i++){
        if(getSquare(row+i, col, board) != symbol){
            vertical = false;
            break;
        }
    }
    //verifyHorizontal
    for(int i = 1; i < 3; i++){
        if(getSquare(row, col+i, board) != symbol){
            horizontal = false;
            break;
        }
    }
    //verifyDiagonals
    for(int i = 1; i < 3; i++){
        if(getSquare(row+i, col+i, board) != symbol){
            downDiagonal = false;
            break;
        }
    }
    for(int i = 1; i < 3; i++){
        if(getSquare(row-i, col+i, board) != symbol){
            upDiagonal = false;
            break;
        }
    }

    return vertical || horizontal || downDiagonal || upDiagonal;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
}

Player* TicTacToe::checkWinner(const BoardType& board){
    for(int row = 0; row < getRows(); row++){
        if(verifySequence(row, 0, board)){
            return getCurrentPlayer();
        }
    }

    for(int col = 1; col < getCols(); col++){
        if(verifySequence(0, col, board)){
            return getCurrentPlayer();
        }
    }
    return nullptr;
}

std::vector<Coordinates> TicTacToe::possiblePlays(const BoardType &board){
    std::vector<Coordinates> plays;
    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(board[row][col] == ' '){
                Coordinates play;
                play.row = row;
                play.col = col;
                plays.push_back(play);
            }
        }
    }
    return plays;
}

bool TicTacToe::terminalState(const BoardType& board){
    return checkWinner(board) != nullptr || possiblePlays(board).empty();
}

int TicTacToe::whoseTurn(const BoardType& board){
    int x = 0;
    int o = 0;
    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(board[row][col] == 'X'){
                x++;
            }
            if(board[row][col] == 'O'){
                o++;
            }
        }
    }
    return x == o ? 1 : 2;
}

BoardType TicTacToe::result(const BoardType& board, Coordinates play){
    BoardType newBoard = board;
    
    if(whoseTurn(board) == 1){
        newBoard[play.row][play.col] = 'X';
    }
    else{
        newBoard[play.row][play.col] = 'O';
    }
    return newBoard;
}

int TicTacToe::minimax(const BoardType& board, int alpha, int beta, bool maximizing){
    std::vector<Coordinates> plays = possiblePlays(board);
    if(terminalState(board)){
        if(plays.empty()){
            return 0;
        }
        if(whoseTurn(board) == 1){
            return -1;
        }
        if(whoseTurn(board) == 2){
            return 1;
        }
        return 0;
    }
    if(maximizing){
        int value = -1000;
        for(auto play : plays){
            value = std::max(value, minimax(result(board, play), alpha, beta, false));
            alpha = std::max(alpha, value);
            if(beta < alpha){
                break;
            }
        }
        return value;
    }
    else{
        int value = 1000;
        for(auto play : plays){
            value = std::min(value, minimax(result(board, play), alpha, beta, true));
            beta = std::min(beta, value);
            if(beta < alpha){
                break;
            }
        }
        return value;
    }
    throw std::runtime_error("Erro no minimax!");
    return 0;
}

Coordinates TicTacToe::bestPlay(const BoardType& board){
    std::vector<Coordinates> plays = possiblePlays(board);
    Coordinates bestPlay = plays[0];
    int value = -1000;
    
    if(whoseTurn(board) == 1){
        for(auto play : plays){
            int moveValue = minimax(result(board, play), -1000, 1000, false);
            if(moveValue > value){
                value = moveValue;
                bestPlay = play;
            }
        }
    }
    else{
        value = 1000;
        for(auto play : plays){
            int moveValue = minimax(result(board, play), -1000, 1000, true);
            if(moveValue < value){
                value = moveValue;
                bestPlay = play;
            }
        }
    }
    bestPlay.row++;
    bestPlay.col++;
    return bestPlay;
}