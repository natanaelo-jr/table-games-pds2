#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player{
    private:
        std::string name;
        std::string nickname;
        int tictactoeVictories;
        int tictactoeDefeats;
        int lig4Victories;
        int lig4Defeats;
        int reversiVictories;
        int reversiDefeats;
        int minefieldVictories;
        int minefieldDefeats;

    public:
        Player();
        Player(std::string name, std::string nickname);
        std::string getName() const;
        std::string getNickname() const;
        int getVictories() const;
        int getDefeats() const;
        void setName(std::string name);
        void setNickname(std::string nickname);

        void winTicTacToe();
        void loseTicTacToe();
        void winLig4();
        void loseLig4();
        void winReversi();
        void loseReversi();
        void winMinefield();
        void loseMinefield();

        int getTicTacToeVictories() const;
        int getTicTacToeDefeats() const;
        int getLig4Victories() const;
        int getLig4Defeats() const;
        int getReversiVictories() const;
        int getReversiDefeats() const;
        int getMinefieldVictories() const;
        int getMinefieldDefeats() const;
};

#endif