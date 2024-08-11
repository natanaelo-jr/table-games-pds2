#include <iostream>
#include <string>
#include "Player.hpp"

Player::Player() : Player("undefined", "undefined"){}

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

std::string Player::getName() const{
    return name;
}

std::string Player::getNickname() const{
    return nickname;
}

void Player::setName(std::string name){
    if(name.length() == 0){
        throw std::invalid_argument("Nome vazio");
    }
    this->name = name;
}

void Player::setNickname(std::string nickname){
    if(nickname.length() > 10){
        throw std::invalid_argument("Apelido maior que 10 caracteres");
    }
    if(nickname.length() == 0){
        throw std::invalid_argument("Apelido vazio");
    }
    this->nickname = nickname;
}

int Player::getVictories() const{
    return tictactoeVictories + lig4Victories + reversiVictories + minefieldVictories;
}

int Player::getDefeats() const{
    return tictactoeDefeats + lig4Defeats + reversiDefeats + minefieldDefeats;
}

void Player::winTicTacToe(){
    tictactoeVictories++;
}

void Player::loseTicTacToe(){
    tictactoeDefeats++;
}

void Player::winLig4(){
    lig4Victories++;
}

void Player::loseLig4(){
    lig4Defeats++;
}

void Player::winReversi(){
    reversiVictories++;
}

void Player::loseReversi(){
    reversiDefeats++;
}

void Player::winMinefield(){
    minefieldVictories++;
}

void Player::loseMinefield(){
    minefieldDefeats++;
}

int Player::getTicTacToeVictories() const{
    return tictactoeVictories;
}

int Player::getTicTacToeDefeats() const{
    return tictactoeDefeats;
}

int Player::getLig4Victories() const{
    return lig4Victories;
}

int Player::getLig4Defeats() const{
    return lig4Defeats;
}

int Player::getReversiVictories() const{
    return reversiVictories;
}

int Player::getReversiDefeats() const{
    return reversiDefeats;
}

int Player::getMinefieldVictories() const{
    return minefieldVictories;
}

int Player::getMinefieldDefeats() const{
    return minefieldDefeats;
}