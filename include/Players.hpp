#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <string>
#include <set>
#include <list>
#include "Player.hpp"

/**
 * @brief Struct que compara dois jogadores
 * 
 * @param player1
 * @param player2
 * 
 * @return true se o jogador 1 tiver um nickname menor que o do jogador 2, false caso contrário
 */
struct ComparePlayer{
    bool operator()(const Player* player1,const Player* player2) const;
};

/**
 * @brief Struct que compara dois jogadores pelo número de vitórias
 * 
 * @param player1
 * @param player2
 * 
 * @return true se o jogador 1 tiver mais vitórias que o jogador 2, false caso contrário
 */
struct CompareByVictories{
    bool operator()(const Player* player1,const Player* player2) const;
};

/**
 * @brief Classe que gerencia os jogadores
 * 
 * A classe Players gerencia os jogadores cadastrados no jogo, permitindo a busca, cadastro e remoção de jogadores.
 */
class Players{
    private: 
        std::set<Player*, ComparePlayer> players;

    /**
     * @brief Método que carrega os jogadores de um arquivo de dados
     * 
     * O método carrega os jogadores de um arquivo de dados, permitindo que os jogadores cadastrados sejam recuperados
     */
    public:
        Players();
        void loadFromDataFile();
        void saveToDataFile();
        Player* searchByNickname(std::string nickname);
        Player* search(std::string name, std::string nickname);
        std::list<Player*> getPlayers(); 
        std::list<Player*> getPlayersByVictories();
        void signUpPlayer(std::string name, std::string nickname);
        void deletePlayer(std::string nickname);
        void displayPlayers();
        int getsize(); /**<Quantidade de jogadores */
};

#endif