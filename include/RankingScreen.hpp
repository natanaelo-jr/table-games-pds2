#ifndef RANKINGSCREEN_HPP
#define RANKINGSCREEN_HPP

#include <Players.hpp>
#include "Screen.hpp"

class RankingScreen : public Screen{
    public:
        RankingScreen(ScreenManager* screenManager, Players *players);
        void handleEvents(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window) override;
        void render(sf::RenderWindow &window) override;
        void loadTextures() override;
    
    private:
        unsigned currentPlayer = 0;

        std::vector<Player*> playersList;

        sf::Texture playerCardTexture;
        sf::Sprite playerCard;

        sf::Texture backButtonTexture;
        sf::Texture hoverBackButtonTexture;
        sf::Sprite backButton;

        sf::Texture nextButtonTexture;
        sf::Sprite nextButton;

        sf::Texture previousButtonTexture;
        sf::Sprite previousButton;

        sf::Texture JogadorTexture;
        sf::Sprite Jogador;

        sf::Texture versusTexture;
        sf::Sprite versus;

        sf::Text name;
        sf::Text nickname;
        sf::Text position;

        sf::Text TicTacToeWins;
        sf::Text TicTacToeLosses;
        sf::Text Lig4Wins;
        sf::Text Lig4Losses;
        sf::Text MineFieldWins;
        sf::Text MineFieldLosses;
        sf::Text ReversiWins;
        sf::Text ReversiLosses;

        sf::Color mainColor;
        sf::Color green;
        sf::Color red;

        sf::Font textFont;

};

#endif