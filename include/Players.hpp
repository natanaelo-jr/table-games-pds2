#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <string>
#include <vector>
#include "Player.hpp"

class Players{
    private: 
    std::vector<Player> players;

    public: 
    Players();
    Player searchPlayer(std::string name, std::string apelido);
    bool playerExists(std::string name, std::string apelido);
    void signUpPlayer(std::string name, std::string apelido);
    void deletePlayer(std::string name, std::string apelido);
    void displayPlayers();
};

#endif
