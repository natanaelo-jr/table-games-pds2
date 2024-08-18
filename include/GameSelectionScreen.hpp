#ifndef SELECTIONSCREEN_HPP
#define SELECTIONSCREEN_HPP
#include "Screen.hpp"

class GameSelectionScreen : public Screen{

    public:
        GameSelectionScreen(ScreenManager* screenManager, Players* players);
        void handleEvents(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window) override;
        void render(sf::RenderWindow &window) override;
        void loadTextures() override;
        void updateSelectedGame();
        void updateTexts();

    private:
        std::string SelectedGame;
        std::vector<Player*> playerList;
        unsigned player1Index;
        unsigned player2Index;

        sf::Texture startButtonTexture;
        sf::Texture hoverStartButtonTexture;
        sf::Sprite startButton;

        sf::Texture backButtonTexture;
        sf::Texture hoverBackButtonTexture;
        sf::Sprite backButton;

        sf::Texture ticTacToeButtonTexture;
        sf::Texture selectedTicTacToeButtonTexture;
        sf::Sprite ticTacToeButton;

        sf::Texture lig4ButtonTexture;
        sf::Texture selectedLig4ButtonTexture;
        sf::Sprite lig4Button;

        sf::Texture mineFieldButtonTexture;
        sf::Texture selectedMineFieldButtonTexture;
        sf::Sprite mineFieldButton;

        sf::Texture reversiButtonTexture;
        sf::Texture selectedReversiButtonTexture;
        sf::Sprite reversiButton;

        sf::Text selectedGame;
        sf::Text player1;
        sf::Text player2;
        sf::Vector2f selectedGamePosition;
        sf::Vector2f player1Position;
        sf::Vector2f player2Position;

        sf::Font textFont;
        sf::Color mainColor;

        sf::Texture nextPlayerTexture;
        sf::Texture previousPlayerTexture;
        sf::Sprite nextPlayer1;
        sf::Sprite previousPlayer1;
        sf::Sprite nextPlayer2;
        sf::Sprite previousPlayer2;

        sf::Texture versusTexture;
        sf::Sprite versus;

};

#endif