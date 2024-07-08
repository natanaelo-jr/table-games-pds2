#include <iostream>
#include "Players.hpp"

Players::Players(){
    
}

bool Players::playerExists(std::string name, std::string apelido) {
    for (auto& player : players) {
        if (player.getName() == name && player.getNickname() == apelido) {
            return true;
        }
    }
    return false; 
}


Player Players::searchPlayer(std::string name, std::string apelido) {
    for (auto& player : players) {
        if (player.getName() == name && player.getNickname() == apelido) {
            return player;
        }
    }
    return Player();
}

void Players::signUpPlayer(std::string name, std::string apelido) {
    if (playerExists(name, apelido)) {
        std::cout << "ERRO: jogador repetido" << std::endl;
    } else {
        players.push_back(Player(name, apelido));
        std::cout << "Jogador " << apelido << " cadastrado com sucesso" << std::endl;
    }
}

void Players::deletePlayer(std::string name, std::string apelido) {
    if (playerExists(name, apelido)) {
        for (auto iterator = players.begin(); iterator != players.end(); ++iterator) {
            if (iterator->getName() == name && iterator->getNickname() == apelido) {
                players.erase(iterator);
                std::cout << "Jogador " << apelido << " removido com sucesso" << std::endl;
                return;
            }
        }
    }
    else
    std::cout << "ERRO: jogador inexistente" << std::endl;
}

void Players::displayPlayers() {
  
}
