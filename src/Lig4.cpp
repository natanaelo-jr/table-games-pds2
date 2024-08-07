#include "Lig4.hpp"
#include <iostream>

Lig4::Lig4(Player* player1, Player* player2) : Game(player1, player2, 6, 7){}

void Lig4::play(){
    Player* winner = nullptr;
    int play;
    printBoard();
    while(true){
        if(possiblePlays(getBoard()).size() == 0){
            std::cout << "Empate!" << std::endl;
            if(getPlayer1()->getName() == "CPU" || getPlayer2()->getName() == "CPU"){
                std::cout << "Partidas contra o computador não contam para as estatísticas." << std::endl;
            }
            break;
        }
        //todo: Refatorar a funcao [melhorar if else] (igual tictactoe)
        if(getCurrentPlayer()->getName() == "CPU"){
            play = bestPlay(getBoard());
            std::cout << "Best Move is: " << play << std::endl;
        }
        else{
            std::cout << "Vez de " << getCurrentPlayer()->getNickname() << std::endl;
            std::cout << "Digite a coluna da sua jogada: ";
            std::cin >> play;
        }
        if(makePlay(play)){
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

Player* Lig4::checkWinner(const BoardType& board){
    for(int row = getRows()-1; row >= 0; row--){
        for(int col = 0; col < getCols(); col++){
            if(verifySequence(board)){
                return getCurrentPlayer();
            }
        }
    }
    return nullptr;
}

bool Lig4::makePlay(int col){
    col--;
    for(int row = getRows()-1; row >= 0; row--){
        if(getSquare({row, col}, getBoard()) == ' '){
            getCurrentPlayer() == getPlayer1() ? setSquare({row, col}, 'X') : setSquare({row, col}, 'O');
            return true;
        }else if(row == 0){
            std::cout << "Coluna Cheia!" << std::endl;
            return false;
        }
    }
    return false;//todo: tratar excecao
}

void Lig4::addStats(Player* winner, Player* loser){
    winner->increaseVictories();
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;
    loser->increaseDefeats();
}

bool Lig4::verifySequence(const BoardType& board){
    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(col < getCols()-4){
                if(verifyRight({row, col},board, 1)){
                    return true;
                }
            }
            if(row < getRows()-4){
                if(verifyDown({row, col}, board, 1)){
                    return true;
                }
            }
            if(row < getRows()-4 && col < getCols()-4){
                if(verifyDownRight({row, col}, board, 1)){
                    return true;
                }
            }
            if(row >= 3 && col < getCols()-4){
                if(verifyUpRight({row, col}, board, 1)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Lig4::verifyRight(Coordinates c, const BoardType& board, int counter){
    if(counter == 4){
        return true;
    }
    if(!isValidSquare({c.getRow(), c.getCol()+1})){
        return false;
    }
    char currentSymbol = getSquare(c, board);
    char nextSymbol = getSquare({c.getRow(), c.getCol()+1}, board);

    if(currentSymbol == ' ' || currentSymbol != nextSymbol){
        return false;
    }
    
    return verifyRight({c.getRow(), c.getCol()+1}, board, counter+1);
}

bool Lig4::verifyDown(Coordinates c, const BoardType& board, int counter){
    if(counter == 4){
        return true;
    }
    if(!isValidSquare({c.getRow()+1, c.getCol()})){
        return false;
    }

    char currentSymbol = getSquare(c, board);
    char nextSymbol = getSquare({c.getRow()+1, c.getCol()}, board);

    if(currentSymbol == ' ' || currentSymbol != nextSymbol){
        return false;
    }
    return verifyDown({c.getRow()+1, c.getCol()}, board, counter+1);
}

bool Lig4::verifyDownRight(Coordinates c, const BoardType& board, int counter){
    if(counter == 4){
        return true;
    }
    if(!isValidSquare({c.getRow()+1, c.getCol()+1})){
        return false;
    }
    char currentSymbol = getSquare(c, board);
    char nextSymbol = getSquare({c.getRow()+1, c.getCol()+1}, board);

    if(currentSymbol == ' ' || currentSymbol != nextSymbol){
        return false;
    }
    
    return verifyRight({c.getRow()+1, c.getCol()+1}, board, counter+1);
}

bool Lig4::verifyUpRight(Coordinates c, const BoardType& board, int counter){
    if(counter == 4){
        return true;
    }
    if(!isValidSquare({c.getRow()-1, c.getCol()+1})){
        return false;
    }
    char currentSymbol = getSquare(c, board);
    char nextSymbol = getSquare({c.getRow()-1, c.getCol()+1}, board);

    if(currentSymbol == ' ' || currentSymbol != nextSymbol){
        return false;
    }
    
    return verifyRight({c.getRow()-1, c.getCol()+1}, board, counter+1);
}

std::vector<int> Lig4::possiblePlays(const BoardType& board){
    std::vector<int> plays;
    for(int col = 0; col < getCols(); col++){
        if(getSquare({0, col}, board) == ' '){
            plays.push_back(col);
        }
    }
    return plays;
}

bool Lig4::terminalState(const BoardType& board){
    return checkWinner(board) != nullptr || possiblePlays(board).empty();
}

int Lig4::whoseTurn(const BoardType& board){
    int x = 0;
    int o = 0;

    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(getSquare({row, col}, board) == 'X'){
                x++;
            }
            else if(getSquare({row, col}, board) == 'O'){
                o++;
            }
        }
    }
    return x == o ? 1 : 2;
}

BoardType Lig4::result(const BoardType& board, int play){
    BoardType newBoard = board;
    for(int row = getRows()-1; row >= 0; row--){
        if(getSquare({row, play}, board) == ' '){
            whoseTurn(board) == 1 ? newBoard[row][play] = 'X' : newBoard[row][play] = 'O';
            break;
        }
    }
    return newBoard;
}

int Lig4::minimax(const BoardType& board, int alpha, int beta, bool maximizing, int depth){
    std::vector<int> plays = possiblePlays(board);
    if(terminalState(board) || depth == MINIMAX_DEPTH){
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
        for(int play : plays){
            value = std::max(value, minimax(result(board, play), alpha, beta, false, depth+1));
            alpha = std::max(alpha, value);
            if(beta <= alpha){
                break;
            }
        }
        return value;
    }
    else{
        int value = 1000;
        for(int play : plays){
            value = std::min(value, minimax(result(board, play), alpha, beta, true, depth+1));
            beta = std::min(beta, value);
            if(beta <= alpha){
                break;
            }
        }
        return value;
    }
    throw std::runtime_error("Erro no minimax!");
    return 0;
}

int Lig4::bestPlay(const BoardType& board){
    std::vector<int> plays = possiblePlays(board);
    int value = -1000;
    int bestPlay = -1;

    if(whoseTurn(board) == 1){
        for(int play : plays){
            int moveValue = minimax(result(board, play), -1000, 1000, false, 0);
            if(moveValue > value){
                value = moveValue;
                bestPlay = play;
            }
        }
    }
    else{
        value = 1000;
        for(int play : plays){
            int moveValue = minimax(result(board, play), -1000 ,1000, true, 0);
            if(moveValue < value){
                value = moveValue;
                bestPlay = play;
            }
        }
    }
    bestPlay++;
    return bestPlay;
}