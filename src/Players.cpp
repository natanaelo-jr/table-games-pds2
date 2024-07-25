#include <iostream>
#include "Players.hpp"

Players::Players(){
    
}

Player* Players::search(std::string name, std::string nickname) {
    for(auto player : players){
        if(player->getName() == name && player->getName() == nickname){
            return player;
        }
    }
    return nullptr;
}
Player* Players::searchByNickname(std::string nickname){
    for(auto player : players){
        if(player->getNickname() == nickname){
            return player;
        }
    }
    return nullptr;
}

void Players::signUpPlayer(std::string name, std::string nickname) {
    if (search(name, nickname) != nullptr) {
        std::cout << "ERRO: jogador repetido" << std::endl;
    }else{
        players.insert(new Player(name, nickname));
        std::cout << "Jogador " << nickname << " cadastrado com sucesso" << std::endl;
    }
}

void Players::deletePlayer(std::string nickname) {
    Player* player = searchByNickname(nickname);
    if(player != nullptr) {
        delete player;
        players.erase(player);
        std::cout << "Jogador " << nickname << " removido com sucesso" << std::endl;
        return;
            
        
    }
    std::cout << "ERRO: jogador inexistente" << std::endl;
}

void Players::displayPlayers() {
    for(auto player : players){
        std::cout << player->getNickname() << " " << player->getName() << std::endl;
        //todo: imprimir os status de cada jogo.
    }
  
}

bool ComparePlayer::operator()(const Player* p1,const Player* p2) const{
    return p1->getNickname() < p2->getNickname();
}
int Players::getsize(){
    return players.size();
}
