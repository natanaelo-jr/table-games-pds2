#include "Lig4.hpp"
#include <iostream>

/**
 * @file Lig4.cpp
 * 
 * @brief Implementação da classe Lig4
 */

/**
 * @brief Construtor da classe Lig4
 * inicia o tabuleiro com 6 linhas e 7 colunas e os jogadores 1 e 2
 *  
 * @param player1 Ponteiro para o jogador 1
 * @param player2 Ponteiro para o jogador 2
 */
Lig4::Lig4(Player* player1, Player* player2) : Game(player1, player2, 6, 7){}

/**
 * @brief Inicia o jogo de Lig4
 * 
 * executa o jogo de Lig4, executando o necessário para o jogo funcionar 
 * verificando se há 1 ou 2 jogadores, recebendo jogadas, testando se há vencedores
 * adicionando estatísticas etc. 
 */
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

/**
 * @brief Verifica se há um vencedor no tabuleiro atual
 * 
 * @param board Estado atual do tabuleiro
 * @return Ponteiro para o jogador vencedor ou nullptr se não houver vencedor
 */
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

/** 
 * @brief Realiza uma jogada na coluna especificada testnato se é válida
 * 
 * @return true se a jogada foi bem-sucedida, false caso contrário
 */
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

/**
 * @brief Adiciona estatísticas ao final da partida
 * 
 * @param winner Ponteiro para o jogador vencedor
 * @param loser Ponteiro para o jogador perdedor
 */
void Lig4::addStats(Player* winner, Player* loser){
    winner->winLig4();
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;
    loser->loseLig4();
}

bool Lig4::verifySequence(const BoardType& board){
    for(int row = 0; row < getRows(); row++){
        for(int col = 0; col < getCols(); col++){
            if(col <= getCols()-4){
                if(verifyRight({row, col},board, 1)){
                    return true;
                }
            }
            if(row <= getRows()-4){
                if(verifyDown({row, col}, board, 1)){
                    return true;
                }
            }
            if(row <= getRows()-4 && col <= getCols()-4){
                if(verifyDownRight({row, col}, board, 1)){
                    return true;
                }
            }
            if(row >= 3 && col <= getCols()-4){
                if(verifyUpRight({row, col}, board, 1)){
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Verificam sequencias de 4 peças iguais para alguma direção
 * 
 * @return true se a sequência foi completada, false caso contrário
 */
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
    
    return verifyDownRight({c.getRow()+1, c.getCol()+1}, board, counter+1);
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
    
    return verifyUpRight({c.getRow()-1, c.getCol()+1}, board, counter+1);
}

/**
 * @brief analisa as possíveis jogadas a serem feitas a partir de um tabuleiro
 * 
 * @param board Tabuleiro do jogo
 * 
 * @return Vetor de inteiros com as colunas possíveis de jogar
 */
std::vector<int> Lig4::possiblePlays(const BoardType& board){
    std::vector<int> plays;
    for(int col = 0; col < getCols(); col++){
        if(getSquare({0, col}, board) == ' '){
            plays.push_back(col);
        }
    }
    return plays;
}

/**
 * @brief Verifica se o estado atual do tabuleiro é terminal
 * 
 * @param board Estado atual do tabuleiro
 * 
 * @return true se o estado é terminal (vitória ou empate), false caso contrário
 */
bool Lig4::terminalState(const BoardType& board){
    return checkWinner(board) != nullptr || possiblePlays(board).empty();
}

/**
 * @brief Determina de quem é a vez de jogar
 * 
 * @param board Estado atual do tabuleiro
 * 
 * @return 1 ou 2 dependendo do jogador que deve jogar
 */
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
/**
        * @brief Aplica uma jogada e retorna o novo estado do tabuleiro.
        * 
        * @param board Estado atual do tabuleiro.
        * @param play Coluna onde a jogada será realizada.
        * @return O novo estado do tabuleiro após a jogada.
        */

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

/**
        * @brief Implementa o algoritmo Minimax para escolher a melhor jogada.
        *   
        * @param board Estado atual do tabuleiro.
        * @param alpha Valor alfa para poda alfa-beta.
        * @param beta Valor beta para poda alfa-beta.
        * @param maximizing Booleano indicando se o algoritmo deve maximizar ou minimizar.
        * @param depth Profundidade máxima da árvore de busca.
        * @return O valor da jogada calculado pelo algoritmo Minimax.
 */ 
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

 /**
        * @brief Retorna a melhor jogada calculada pelo algoritmo Minimax.
        * 
        * @param board Estado atual do tabuleiro.
        * @return Inteiro representando a coluna onde deve ser feita a melhor jogada.
        */
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