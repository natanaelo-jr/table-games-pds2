#include <iostream>
#include <string>
#include "Player.hpp"

/**
 * @brief Construtor padrão da classe Player.
 * Inicializa um jogador quando os dados não foram fornecidos com nome e apelido padrão "undefined".
 */
Player::Player() : Player("undefined", "undefined") {}

/**
 * @brief Construtor da classe Player com parâmetros.
 * 
 * @param name Nome do jogador.
 * @param nickname Apelido do jogador.
 * @throws std::invalid_argument Se o apelido tiver mais de 10 caracteres ou se o nome ou apelido estiver vazio.
 */
Player::Player(std::string name, std::string nickname){
    if(nickname.length() > 10){
        throw std::invalid_argument("Apelido maior que 10 caracteres");
    }
    if(nickname.length() == 0 || name.length() == 0){
        throw std::invalid_argument("Nome ou apelido vazio");
    }

    this->name = name;
    this->nickname = nickname;
    tictactoeVictories = 0;
    tictactoeDefeats = 0;
    lig4Victories = 0;
    lig4Defeats = 0;
    reversiVictories = 0;
    reversiDefeats = 0;
    minefieldVictories = 0;
    minefieldDefeats = 0;
}

/**
 * @brief Obtém o nome do jogador.
 * 
 * @return std::string Nome do jogador.
 */
std::string Player::getName() const {
    return name;
}

/**
 * @brief Obtém o apelido do jogador.
 * 
 * @return std::string Apelido do jogador.
 */
std::string Player::getNickname() const {
    return nickname;
}

/**
 * @brief Define o nome do jogador.
 * 
 * @param name Novo nome do jogador.
 * @throws std::invalid_argument Se o nome for vazio.
 */
void Player::setName(std::string name) {
    if(name.length() == 0){
        throw std::invalid_argument("Nome vazio");
    }
    this->name = name;
}

/**
 * @brief Define o apelido do jogador.
 * 
 * @param nickname Novo apelido do jogador.
 * @throws std::invalid_argument Se o apelido tiver mais de 10 caracteres ou for vazio.
 */
void Player::setNickname(std::string nickname) {
    if(nickname.length() > 10){
        throw std::invalid_argument("Apelido maior que 10 caracteres");
    }
    if(nickname.length() == 0){
        throw std::invalid_argument("Apelido vazio");
    }
    this->nickname = nickname;
}

/**
 * @brief Obtém o total de vitórias do jogador em todos os jogos.
 * 
 * @return int Total de vitórias.
 */
int Player::getVictories() const {
    return tictactoeVictories + lig4Victories + reversiVictories + minefieldVictories;
}

/**
 * @brief Obtém o total de derrotas do jogador em todos os jogos.
 * 
 * @return int Total de derrotas.
 */
int Player::getDefeats() const {
    return tictactoeDefeats + lig4Defeats + reversiDefeats + minefieldDefeats;
}

/**
 * @brief Incrementa o número de vitórias do jogador em Tic Tac Toe.
 */
void Player::winTicTacToe() {
    tictactoeVictories++;
}

/**
 * @brief Incrementa o número de derrotas do jogador em Tic Tac Toe.
 */
void Player::loseTicTacToe() {
    tictactoeDefeats++;
}

/**
 * @brief Incrementa o número de vitórias do jogador em Lig4.
 */
void Player::winLig4() {
    lig4Victories++;
}

/**
 * @brief Incrementa o número de derrotas do jogador em Lig4.
 */
void Player::loseLig4() {
    lig4Defeats++;
}

/**
 * @brief Incrementa o número de vitórias do jogador em Reversi.
 */
void Player::winReversi() {
    reversiVictories++;
}

/**
 * @brief Incrementa o número de derrotas do jogador em Reversi.
 */
void Player::loseReversi() {
    reversiDefeats++;
}

/**
 * @brief Incrementa o número de vitórias do jogador em Minefield.
 */
void Player::winMinefield() {
    minefieldVictories++;
}

/**
 * @brief Incrementa o número de derrotas do jogador em Minefield.
 */
void Player::loseMinefield() {
    minefieldDefeats++;
}

/**
 * @brief Obtém o número de vitórias do jogador em Tic Tac Toe.
 * 
 * @return int Número de vitórias em Tic Tac Toe.
 */
int Player::getTicTacToeVictories() const {
    return tictactoeVictories;
}

/**
 * @brief Obtém o número de derrotas do jogador em Tic Tac Toe.
 * 
 * @return int Número de derrotas em Tic Tac Toe.
 */
int Player::getTicTacToeDefeats() const {
    return tictactoeDefeats;
}

/**
 * @brief Obtém o número de vitórias do jogador em Lig4.
 * 
 * @return int Número de vitórias em Lig4.
 */
int Player::getLig4Victories() const {
    return lig4Victories;
}

/**
 * @brief Obtém o número de derrotas do jogador em Lig4.
 * 
 * @return int Número de derrotas em Lig4.
 */
int Player::getLig4Defeats() const {
    return lig4Defeats;
}

/**
 * @brief Obtém o número de vitórias do jogador em Reversi.
 * 
 * @return int Número de vitórias em Reversi.
 */
int Player::getReversiVictories() const {
    return reversiVictories;
}

/**
 * @brief Obtém o número de derrotas do jogador em Reversi.
 * 
 * @return int Número de derrotas em Reversi.
 */
int Player::getReversiDefeats() const {
    return reversiDefeats;
}

/**
 * @brief Obtém o número de vitórias do jogador em Minefield.
 * 
 * @return int Número de vitórias em Minefield.
 */
int Player::getMinefieldVictories() const {
    return minefieldVictories;
}

/**
 * @brief Obtém o número de derrotas do jogador em Minefield.
 * 
 * @return int Número de derrotas em Minefield.
 */
int Player::getMinefieldDefeats() const {
    return minefieldDefeats;
}


/** 
* @brief Métodos setters de vitórias e derrotas de cada jogo específico
*/

void Player::setTicTacToeVictories(int victories){
    tictactoeVictories = victories;
}

void Player::setTicTacToeDefeats(int defeats){
    tictactoeDefeats = defeats;
}

void Player::setLig4Victories(int victories){
    lig4Victories = victories;
}

void Player::setLig4Defeats(int defeats){
    lig4Defeats = defeats;
}

void Player::setReversiVictories(int victories){
    reversiVictories = victories;
}

void Player::setReversiDefeats(int defeats){
    reversiDefeats = defeats;
}

void Player::setMinefieldVictories(int victories){
    minefieldVictories = victories;
}

void Player::setMinefieldDefeats(int defeats){
    minefieldDefeats = defeats;
}