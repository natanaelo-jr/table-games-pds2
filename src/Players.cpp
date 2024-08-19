#include <iostream>
#include <fstream>
#include <sstream>
#include "Players.hpp"

/**
 * @brief Construtor padrão da classe Players.
 */
Players::Players() {
}

/**
 * @brief Busca um jogador pela combinação de nome e apelido.
 * 
 * @param name Nome do jogador a ser buscado.
 * @param nickname Apelido do jogador a ser buscado.
 * @return Player* Ponteiro para o jogador encontrado ou nullptr se não encontrado.
 */
Player* Players::search(std::string name, std::string nickname) {
    for(auto player : players){
        if(player->getName() == name && player->getNickname() == nickname){
            return player;
        }
    }
    return nullptr;
}

/**
 * @brief Obtém uma lista de jogadores ordenada pelo número de vitórias.
 * 
 * @return std::list<Player*> Lista de jogadores ordenada por vitórias.
 */
std::list<Player*> Players::getPlayersByVictories() {
    std::list<Player*> playersByVictories;
    for(auto player : players){
        playersByVictories.push_back(player);
    }
    playersByVictories.sort(CompareByVictories());
    return playersByVictories;
}

/**
 * @brief Obtém uma lista de todos os jogadores.
 * 
 * @return std::list<Player*> Lista de todos os jogadores.
 */
std::list<Player*> Players::getPlayers() {
    std::list<Player*> playersList;
    for(auto player : players){
        playersList.push_back(player);
    }
    return playersList;
}

/**
 * @brief Busca um jogador pelo apelido.
 * 
 * @param nickname Apelido do jogador a ser buscado.
 * @return Player* Ponteiro para o jogador encontrado ou nullptr se não encontrado.
 */
Player* Players::searchByNickname(std::string nickname) {
    for(auto player : players){
        if(player->getNickname() == nickname){
            return player;
        }
    }
    return nullptr;
}

/**
 * @brief Cadastra um novo jogador com nome e apelido fornecidos.
 * 
 * @param name Nome do novo jogador.
 * @param nickname Apelido do novo jogador.
 * @throws std::invalid_argument Se o jogador já existir.
 */
void Players::signUpPlayer(std::string name, std::string nickname) {
    if (search(name, nickname) != nullptr) {
        std::cout << "ERRO: jogador repetido" << std::endl;
        throw std::invalid_argument("Jogador repetido");
    } else {
        players.insert(new Player(name, nickname));
        std::cout << "Jogador " << nickname << " cadastrado com sucesso" << std::endl;
    }
}

/**
 * @brief Remove um jogador pelo apelido.
 * 
 * @param nickname Apelido do jogador a ser removido.
 * @throws std::invalid_argument Se o jogador não existir.
 */
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

/**
 * @brief Exibe informações sobre todos os jogadores cadastrados.
 */
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

/**
 * @brief Functor para comparar jogadores pelo apelido.
 */
bool ComparePlayer::operator()(const Player* p1, const Player* p2) const {
    return p1->getNickname() < p2->getNickname();
}

/**
 * @brief Functor para comparar jogadores pelo número de vitórias.
 */
bool CompareByVictories::operator()(const Player* p1, const Player* p2) const {
    return p1->getVictories() > p2->getVictories();
}

/**
 * @brief Obtém o número de jogadores cadastrados.
 * 
 * @return int Número de jogadores.
 */
int Players::getsize() {
    return players.size();
}

/**
 * @brief Carrega os dados dos jogadores a partir de um arquivo.
 * 
 * O arquivo deve estar no formato: nome apelido vitórias derrotas.
 */
void Players::loadFromDataFile() {
    std::ifstream file("Data.txt", std::ios::in | std::ios::binary);
    if(file.is_open()){
        std::string line;
        std::stringstream linestream;

        while(getline(file, line)){
            std::stringstream linestream;
            linestream << line;
            std::string name, nickname;
            linestream >> name >> nickname;
            Player* player = new Player(name, nickname);
            int victories, defeats;
            linestream >> victories >> defeats;
            // player->setVictories(victories);
            // player->setDefeats(defeats);
            players.insert(player);
        }
        file.close();
    }
}

/**
 * @brief Salva os dados dos jogadores em um arquivo.
 * 
 * O arquivo será salvo no formato: nome apelido vitórias derrotas.
 */
void Players::saveToDataFile() {
    std::ofstream file("Data.txt", std::ios::out | std::ios::binary);
    if(file.is_open()){
        for(auto player : players){
            file << player->getName() << " " << player->getNickname() << " " << player->getVictories() << " " << player->getDefeats();
            if(player != *players.rbegin()){
                file << std::endl;
            }
        }
        file.close();
    }
}
