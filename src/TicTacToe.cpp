#include "TicTacToe.hpp"
#include <iostream>

/**
 * @brief Construtor da classe TicTacToe.
 * 
 * @param player1 Primeiro jogador.
 * @param player2 Segundo jogador.
 */
TicTacToe::TicTacToe(Player* player1, Player* player2) : Game(player1, player2, 3, 3){}

/**
 * @brief Função principal que executa o ciclo do jogo.
 */
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
        }
        else{
            std::cout << "Vez de " << getCurrentPlayer()->getNickname() << std::endl;
            std::cout << "Digite a linha e a coluna da sua jogada: ";
            std::cin >> currentPlay.row >> currentPlay.col;
        }

        if(makePlay(currentPlay)){
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
* @brief Realiza uma jogada no tabuleiro.
* 
* @param play Coordenadas da jogada.
* @return true Se a jogada foi realizada com sucesso.
* @return false Se a jogada foi inválida.
 */
bool TicTacToe::makePlay(Coordinates play){
    play.setRow(play.getRow() - 1);
    play.setCol(play.getCol() - 1);

    if((isValidSquare(play))){
        if(getSquare(play, getBoard()) != ' '){
            std::cout << "Casa já preenchida!" << std::endl;
            return false;
        }
        if(getSquare(play, getBoard()) == ' '){
            if(getCurrentPlayer() == getPlayer1()){
                setSquare(play, 'X');
                return true;
            }
            if(getCurrentPlayer() == getPlayer2()){
                setSquare(play, 'O');
                return true;
            }
        }
    }
    std::cout << "Erro na jogada!" << std::endl;
    return false;
}

/**
* @brief Atualiza as estatísticas do jogador após uma vitória.
* 
* @param winner Jogador vencedor.
* @param loser Jogador perdedor.
 */
void TicTacToe::addStats(Player* winner, Player* loser){
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;
    if(winner->getName() == "CPU" || loser->getName() == "CPU"){
        std::cout << "Partidas contra o computador não contam para as estatísticas." << std::endl;
        return;
    }
    winner->winTicTacToe();
    loser->loseTicTacToe();
}

/**
* @brief Verifica se há uma sequência de três símbolos iguais.
* 
* @param board Tabuleiro atual.
* @return true Se existe uma sequência.
* @return false Se não há sequência.
 */
bool TicTacToe::verifySequence(const BoardType &board){
    bool result = false;
    for(int i = 0; i < getRows(); i++){
        if(verifyRight({i, 0}, board, 1)){
            result = true;
        }
    }
    for(int i = 0; i < getCols(); i++){
        if(verifyDown({0, i}, board, 1)){
            result = true;
        }
    }

    if(verifyDownRight({0, 0}, board, 1)){
        result = true;
    }
    if(verifyUpRight({2, 0}, board, 1)){
        result = true;
    }
    return result;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
}

/**
* @brief Verifica uma sequência horizontal de símbolos.
* 
* @param coord Coordenadas da peça inicial.
* @param board Tabuleiro atual.
* @param counter Contador de símbolos na sequência.
* @return true Se existe uma sequência completa.
* @return false Se não há sequência.
 */
bool TicTacToe::verifyRight(Coordinates coord, const BoardType &board, int counter){
    if(counter == 3){
        return true;
    }
    if(!isValidSquare({coord.row, coord.col+1})){
        return false;
    }
    char currentSymbol = getSquare(coord, board);
    char nextSymbol = getSquare({coord.row, coord.col+1}, board);

    if(currentSymbol == ' ' || currentSymbol != nextSymbol){
        return false;
    }
    return verifyRight({coord.row, coord.col+1}, board, counter + 1);
}

/**
* @brief Verifica uma sequência vertical de símbolos.
* 
* @param coord Coordenadas da peça inicial.
* @param board Tabuleiro atual.
* @param counter Contador de símbolos na sequência.
* @return true Se existe uma sequência completa.
* @return false Se não há sequência.
*/
bool TicTacToe::verifyDown(Coordinates coord, const BoardType &board, int counter){
    if(counter == 3){
        return true;
    }
    if(!isValidSquare({coord.row+1, coord.col})){
        return false;
    }
    char currentSymbol = getSquare(coord, board);
    char nextSymbol = getSquare({coord.row+1, coord.col}, board);

    if(currentSymbol == ' ' || currentSymbol != nextSymbol){
        return false;
    }
    return verifyDown({coord.row+1, coord.col}, board, counter + 1);
}

/**
* @brief Verifica uma sequência diagonal para baixo e à direita de símbolos.
* 
* @param coord Coordenadas da peça inicial.
* @param board Tabuleiro atual.
* @param counter Contador de símbolos na sequência.
* @return true Se existe uma sequência completa.
* @return false Se não há sequência.
 */
bool TicTacToe::verifyDownRight(Coordinates coord, const BoardType &board, int counter){
    if(counter == 3){
        return true;
    }
    if(!isValidSquare({coord.row+1, coord.col+1})){
        return false;
    }
    char currentSymbol = getSquare(coord, board);
    char nextSymbol = getSquare({coord.row+1, coord.col+1}, board);

    if(currentSymbol == ' ' || currentSymbol != nextSymbol){
        return false;
    }
    return verifyDownRight({coord.row+1, coord.col+1}, board, counter+1);
}

/**
 * @brief Verifica uma sequência diagonal para cima e à direita de símbolos.
 * 
 * @param coord Coordenadas da peça inicial.
 * @param board Tabuleiro atual.
 * @param counter Contador de símbolos na sequência.
 * @return true Se existe uma sequência completa.
 * @return false Se não há sequência.
 */
bool TicTacToe::verifyUpRight(Coordinates coord, const BoardType &board, int counter){
    if(counter == 3){
        return true;
    }
    if(!isValidSquare({coord.row-1, coord.col+1})){
        return false;
    }
    char currentSymbol = getSquare(coord, board);
    char nextSymbol = getSquare({coord.row-1, coord.col+1}, board);

    if(currentSymbol == ' ' || currentSymbol != nextSymbol){
        return false;
    }
    return verifyUpRight({coord.row-1, coord.col+1}, board, counter+1);
}

/**
 * @brief Verifica se existe um vencedor.
 * 
 * @param board Tabuleiro atual.
 * @return Player* Jogador vencedor ou nullptr em caso de empate ou sem vencedor.
 */
Player* TicTacToe::checkWinner(const BoardType& board){
    if(verifySequence(board)){
        Player* winner = whoseTurn(board) == 1 ? getPlayer1() : getPlayer2();
        return winner;
    }
    return nullptr;
}

/**
 * @brief Retorna todas as jogadas possíveis no tabuleiro.
 * 
 * @param board Tabuleiro atual.
 * @return std::vector<Coordinates> Vetor com as coordenadas das jogadas possíveis.
 */
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

/**
 * @brief Verifica se o estado do jogo é terminal (fim de jogo).
 * 
 * @param board Tabuleiro atual.
 * @return true Se o jogo chegou ao estado terminal.
 * @return false Se o jogo ainda não terminou.
 */
bool TicTacToe::terminalState(const BoardType& board){
    return checkWinner(board) != nullptr || possiblePlays(board).empty();
}

/**
 * @brief Verifica de quem é a vez no jogo.
 * 
 * @param board Tabuleiro atual 
 * 
 * @return 1 se é a vez do jogador 1
 * @return 2 se é a vez do jogador 2
 */
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


/**
* @brief Implementa o algoritmo Minimax para escolher a melhor jogada.
*   
* @param board Estado atual do tabuleiro.
* @param alpha Valor alfa para poda alfa-beta.
* @param beta Valor beta para poda alfa-beta.
* @param maximizing Booleano indicando se o algoritmo deve maximizar ou minimizar.
* @param depth Profundidade máxima da árvore de busca.
* 
* @return O valor da jogada calculado pelo algoritmo Minimax se o algoritmo rodar corretamente.
* @return 0 se ocorrer um erro
 */ 
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

/**
* @brief Retorna a melhor jogada calculada pelo algoritmo Minimax.
* 
* @param board Estado atual do tabuleiro.
* @return Inteiro representando a coluna onde deve ser feita a melhor jogada.
*/

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

