#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <string>
#include <set>
#include "Player.hpp"

struct ComparePlayer{
    bool operator()(const Player* player1,const Player* player2) const;
};

class Players{
    private: 
        std::set<Player*, ComparePlayer> players;

    public:
        Players();
        Player* searchByNickname(std::string nickname);
        Player* search(std::string name, std::string nickname);
        void signUpPlayer(std::string name, std::string nickname);
        void deletePlayer(std::string nickname);
        void displayPlayers();
};

#endif