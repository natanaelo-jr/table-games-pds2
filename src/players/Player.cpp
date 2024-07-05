#include <string>
#include "Player.hpp"

Player::Player(){
    name = "undefined";
    nickname = "undefined";
    victories = 0;
    defeats = 0;
}

Player::Player(std::string name, std::string nickname){
    this->name = name;
    this->nickname = nickname;
    victories = 0;
    defeats = 0;
}

std::string Player::getName(){
    return name;
}

std::string Player::getNickname(){
    return nickname;
}

void Player::setName(std::string name){
    this->name = name;
}

void Player::setNickname(std::string nickname){
    this->nickname = nickname;
}

void Player::increaseVictories(){
    victories++;
}

void Player::increaseDefeats(){
    defeats++;
}