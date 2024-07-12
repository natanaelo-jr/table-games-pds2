#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player{
    private:
        std::string name;
        std::string nickname;
        int victories;
        int defeats;

    public:
        Player();
        Player(std::string name, std::string nickname);
        std::string getName() const;
        std::string getNickname() const;
        void setName(std::string name);
        void setNickname(std::string nickname);
        void increaseVictories();
        void increaseDefeats();
        
};

#endif