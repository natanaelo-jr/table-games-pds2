#include "Reversi.hpp"
#include <iostream>
#include <vector>
#include <set>
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



bool Reversi::makePlay(int row, int col) {
    char symbol;
    getCurrentPlayer() == getPlayer1() ? symbol = 'X' : symbol = 'O';

    // Verifica se a jogada é válida
    if (!verifyPlay(row, col, symbol))
        return false;

    // Coloca a peça no tabuleiro
    setSquare({row, col}, symbol);

    // Direções para verificar as peças adjacentes
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    
    // Percorre todas as direções e tenta virar as peças do oponente
    for (int i = 0; i < 8; i++) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];
        turnPieces(row + dRow, dRow, col + dCol, dCol, symbol, true, getBoard());


    }
    return true;
}


void Reversi::play() {
    int row; 
    int col;
    Player* winner = nullptr;

    printBoard(); // Imprime o tabuleiro no início do jogo
    while(true){
        char symbol;
        getCurrentPlayer() == getPlayer1() ? symbol = 'X' : symbol = 'O';
        std::cout << "Vez de " << getCurrentPlayer()->getNickname() << std::endl;

        // Verifica se o jogador tem jogadas válidas
        if(getPossiblePlays(symbol, getBoard()).empty()){
            std::cout << getCurrentPlayer()->getNickname() << " não possui jogadas" << std::endl;
            changePlayer();
        }


        // Exibe as jogadas possíveis e solicita ao jogador que faça uma jogada
        std::cout << "Digite a linha e a coluna da sua jogada: " << std::endl;
        if(getCurrentPlayer() == getPlayer1()){
            std::cout << "Jogadas Possíveis: " << std::endl;
            for(auto play : getPossiblePlays('X', getBoard())){
                std::cout << play.getRow() << " " << play.getCol() << std::endl;
            }
        } else {
            std::cout << "Jogadas Possíveis: " << std::endl;
            for(auto play : getPossiblePlays('O', getBoard())){
                std::cout << play.getRow() << " " << play.getCol() << std::endl;
            }
        }

        std::cin >> row >> col;

        //  Realiza a jogada e verifica se o jogo chegou ao estado terminal
        if(makePlay(row, col)){
            winner = checkWinner();
            if(terminalState(getBoard()) && winner != nullptr){
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


Coordinates Reversi::searcherForPlay(int row, int col, int dRow, int dCol, char symbol, char opposite, bool passedOpponent, const BoardType &board) {
    if (row > 7 || row < 0 || col > 7 || col < 0)
        return {-1, -1};

    if (getSquare({row, col}, board) == ' ' && passedOpponent) {
        Coordinates validPlay(row, col);
        return validPlay;
    }

    if (getSquare({row, col}, board) == ' ')
        return {-1, -1};

    if (getSquare({row, col}, board) == symbol)
        return {-1, -1};

    if (getSquare({row, col}, board) == opposite)
        return searcherForPlay(row + dRow, col + dCol, dRow, dCol, symbol, opposite, true, board);

    return {-1, -1};
}


std::vector<Coordinates> Reversi::getPossiblePlays(char symbol, const BoardType &board) {
    std::vector<Coordinates> validPlays;
    char opposite = (symbol == 'X') ? 'O' : 'X';

    // Percorre o tabuleiro em busca das jogadas possíveis
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 7; col++) {
            if (getSquare({row, col}, board) == symbol) {
                int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
                for (int i = 0; i < 8; i++) {
                    int dRow = directions[i][0];
                    int dCol = directions[i][1];
                    Coordinates aux = searcherForPlay(row + dRow, col + dCol, dRow, dCol, symbol, opposite, false, board);
                    if (aux.getRow() != -1 && aux.getCol() != -1)
                        validPlays.push_back(aux);
                }
            }
        }
    }
    return validPlays;
}


bool Reversi::verifyPlay(int row, int col, char symbol) {
    std::vector<Coordinates> validPlays = getPossiblePlays(symbol, getBoard());
    if (validPlays.size() == 0) 
        return false;

    for (auto play : validPlays) {
        if (play.getRow() == row && play.getCol() == col) 
            return true;
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




int Reversi::countSymbols(char symbol) {
    int counter = 0;
    for(int row = 0; row < getRows(); row++) {
        for(int col = 0; col < getCols(); col++) {
            if(getSquare({row, col}, getBoard()) == symbol)
                counter++;
        }
    }
    return counter;
}


Player* Reversi::checkWinner() {
    int xCount = countSymbols('X');
    int oCount = countSymbols('O');

    if (xCount > oCount) {

        return getPlayer1();
    } else if (oCount > xCount) {
        return getPlayer2();
    } else {
        return nullptr; // Empate
    }
}


bool Reversi::turnPieces(int row, int dRow, int col, int dCol, char symbol, bool isOriginalTile, const BoardType &board) {
    if (!isValidSquare({row, col})) 
        return false;

    if (getSquare({row, col}, board) == symbol && !isOriginalTile) 
        return true;

    if (getSquare({row, col}, board) == ' ' && !isOriginalTile) 
        return false;

    if (turnPieces(row + dRow, dRow, col + dCol, dCol, symbol, false, board)) {
        setSquare({row, col}, symbol);
        return true;
    }

    return false;
}


void Reversi::addStats(Player* winner, Player* loser) {
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;
    winner->winReversi();
    loser->loseReversi();
}

bool Reversi::terminalState(const BoardType &board) {
    if (getPossiblePlays('X', board).size() == 0 && getPossiblePlays('O', board).size() == 0)
        return true;

    return false;
}

