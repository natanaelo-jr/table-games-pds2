#include <iostream>
#include "Game.hpp"
#include "Player.hpp"

/**
 * @brief Construtor padrão da classe Game
 * 
 * Inicializa um jogo com dois jogadores, P1 e P2
 */
Game::Game() : Game(new Player("Player 1", "P1"), new Player("Player 2", "P2")){}

/**
 * @brief Construtor da classe Game
 * 
 * Inicializa um jogo com dois jogadores e um tabuleiro 3x3.
 * @param player1 Ponteiro para o jogador 1.
 * @param player2 Ponteiro para o jogador 2.
 */
Game::Game(Player* player1, Player* player2) : Game(player1, player2, 3, 3){}

/**
 * @brief Construtor da classe Game
 * 
 * Inicializa um jogo com dois jogadores, um tabuleiro de tamanho cols x rows.
 * @param player1 Ponteiro para o jogador 1.
 * @param player2 Ponteiro para o jogador 2.
 * @param cols Número de colunas do tabuleiro.
 * @param rows Número de linhas do tabuleiro.
 */    
Game::Game(Player* player1, Player* player2, int cols, int rows){
    this->player1 = player1;
    this->player2 = player2;
    this->currentPlayer = this->player1;
    this->waitingPlayer = this->player2;
    this->cols = cols;
    this->rows = rows;
    board = std::vector<std::vector<char>>(rows, std::vector<char>(cols, ' '));
}
/**
 * @brief Destrutor da classe Game
 */
Game::~Game(){
}

/**
 * @brief Métodos getters que retornam o número de linhas e colunas do tabuleiro
 * 
 * @return Número de linhas e número de colunas do tabuleiro
 */
int Game::getRows(){
    return rows;
}

int Game::getCols(){
    return cols;
}

/**
 * @brief Método setter que modifica o valor de uma posição do tabuleiro
 */
void Game::setSquare(Coordinates coord, char symbol){
    board[coord.getRow()][coord.getCol()] = symbol;
}

/**
 * @brief Método que verifica se uma jogada é válida
 * 
 * @param move Coordenadas da jogada
 * @return true se a jogada é válida, false caso contrário
 */
bool Game::isValidSquare(Coordinates move){
    if(move.getRow() < 0 || move.getRow() >= rows || move.getCol() < 0 || move.getCol() >= cols){
        return false;
    }
    return true;
}

/**
 * @brief Método que retorna o valor de uma posição do tabuleiro
 */
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

/**
 * @brief Método que troca o jogador atual
 * 
 * Esse método troca o jogador atual pelo jogador que está esperando a jogada.
 */
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

/**
 * @brief Métodos getters que retornam os jogadores e o tabuleiro
 * 
 * @return Ponteiro para o jogador que está esperando a jogada, ponteiro para o jogador atual, ponteiro para o jogador 1, ponteiro para o jogador 2 e tabuleiro
 */
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