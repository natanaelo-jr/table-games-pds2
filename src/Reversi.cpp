#include "Reversi.hpp"
#include <iostream>

Reversi::Reversi(Player* player1, Player* player2) : Game(player1, player2, 8, 8) {
    initializeBoard();
}

void Reversi::initializeBoard() {
    setSquare(4, 4, 'O');
    setSquare(4, 5, 'X');
    setSquare(5, 4, 'O');
    setSquare(5, 5, 'X');
}

void Reversi::play(){
    Player* winner = nullptr;
    printBoard();
    while(true){
        if(isFull()){
        winner = checkWinner();
        break;
        }

        int row, col;
        std::cin >> row >> col;
        if(verifyPlay(row, col, 'X')){ // MUDAR DPS PRA COLOCAR O SÍMBOLO COMO O DO JOGADOR DA JOGADA AAAAAAAAA
            makePlay(row, col);
            changePlayer();
            printBoard();
        }
        else
        std::cout << "JOGADA INVALIDA" << std::endl;

    }
}

bool Reversi::verifyPlay(int row, int col, char symbol) {
    bool valid = false;
    // DEFININDO O SÍMBOLO OPOSTO AO PROCURADO
    char opposite = (symbol == 'X') ? 'O' : 'X';

    // Verificando se a jogada é válida verificando as casas ao redor 
    if (getSquare(row-1, col) == opposite || getSquare(row+1, col) == opposite) // VERIFICA SE HÁ SIMBOLO OPOSTO NAS LATERAIS  
    //POSSIVEL ACCESO INVALIDO? - BRUNO
    {
        // VERIFICAR SE DEPOIS DO SÍMBOLO OPOSTO HÁ UM DO MESMO SÍMBOLO NA MESMA LINHA
        for (int i = row -1; i > 0; i--)
        {
            if (getSquare(i, col)== symbol)
            {
                valid = true; 
                reverseSymbols(i, col);
            }
        }
        for (int i = row + 1; i < 8; i++)
        {
            if (getSquare(i, col)== symbol)
            {
                valid = true; 
                reverseSymbols(i, col);
            }
        }

    }

    if (getSquare(row, col-1) == opposite || getSquare(row, col+1) == opposite) // VERIFICA SE HÁ SIMBOLO OPOSTO NAS EM CIMA OU EM BAIXO
    //POSSIVEL ACESSO INVALIDO EM -1? - BRUNO
    {
        // VERIFICAR SE DEPOIS DO SÍMBOLO OPOSTO HÁ UM DO MESMO SÍMBOLO NA MESMA COLUNA
        for (int i = col -1; i > 0; i--)
        {
            if (getSquare(row, i)== symbol)
            {
                valid = true; 
                reverseSymbols(row, i);
            }
        }
        for (int i = col + 1; i < 8; i++)
        {
            if (getSquare(row, i)== symbol)
            {
                valid = true; 
                reverseSymbols(row, i);
            }
        }

    }
    if (getSquare(row-1, col-1) == opposite || getSquare(row+1, col+1) == opposite) // VERIFICA SE HÁ SIMBOLO OPOSTO NA DIAGONAL
    {
        // VERIFICAR SE DEPOIS DO SÍMBOLO OPOSTO HÁ UM DO MESMO SÍMBOLO NA MESMA DIAGONAL
        for (int i = row -1, j = col -1; i > 0 && j > 0; i--, j--) //VERIFICA A ESQUERDA E CIMA
        {
            if (getSquare(i, j)== symbol)
            {
                valid = true; 
                reverseSymbols(i, j);
            }
        }
        for (int i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) //VERIFICA A DIREITA E BAIXO
        {
            if (getSquare(i, j)== symbol)
            {
                valid = true; 
                reverseSymbols(i, j);
            }
        }
        // VERIFICA A DIREITA PRA CIMA  
        for (int i = row - 1, j = col + 1; i > 0 && j < 8; i--, j++)
        {
            if (getSquare(i, j)== symbol)
            {
                valid = true; 
                reverseSymbols(i, j);
            }
        }
        for (int i = row + 1, j = col - 1; i < 8 && j > 0; i++, j--) //VERIFICA A ESQUERDA E BAIXO
        {
            if (getSquare(i, j)== symbol)
            {
                valid = true; 
                reverseSymbols(i, j);
            }
        }
    }
    return valid;
}

void Reversi::reverseSymbols(int row, int col){
    char symbol = getSquare(row, col);
    if (symbol == 'X')
        setSquare (row, col, 'O');
    else if (symbol == 'O')
        setSquare (row, col, 'X');
    else 
        setSquare (row, col, 'L');

}



int Reversi::countSymbols(char symbol){
    int counter = 0;
    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(getSquare(row, col) == symbol){
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

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  

