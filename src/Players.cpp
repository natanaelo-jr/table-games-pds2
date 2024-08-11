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

std::list<Player*> Players::getPlayersByVictories(){
    std::list<Player*> playersByVictories;
    for(auto player : players){
        playersByVictories.push_back(player);
    }
    playersByVictories.sort(CompareByVictories());
    return playersByVictories;
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
        throw std::invalid_argument("Jogador repetido");
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
    throw std::invalid_argument("Jogador inexistente");

}

void Players::displayPlayers() {
    for(auto player : players){
        std::cout << player->getNickname() << " " << player->getName() << std::endl;
        std::cout << "Geral: " << player->getVictories() << "/" << player->getDefeats() << std::endl;
        std::cout << "Jogo da Velha: " << player->getTicTacToeVictories() << "/" << player->getTicTacToeDefeats() << std::endl;
        std::cout << "Lig4: " << player->getLig4Victories() << "/" << player->getLig4Defeats() << std::endl;
        std::cout << "Reversi: " << player->getReversiVictories() << "/" << player->getReversiDefeats() << std::endl;
        std::cout << "Campo Minado: " << player->getMinefieldVictories() << "/" << player->getMinefieldDefeats() << std::endl;
    }
  
}

bool ComparePlayer::operator()(const Player* p1,const Player* p2) const{
    return p1->getNickname() < p2->getNickname();
}

bool CompareByVictories::operator()(const Player* p1,const Player* p2) const{
    return p1->getVictories() > p2->getVictories();
}

int Players::getsize(){
    return players.size();
}
