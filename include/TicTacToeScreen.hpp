#ifndef TICTACTOESCREEN_HPP
#define TICTACTOESCREEN_HPP
#include "Screen.hpp"
#include "TicTacToe.hpp"

class TicTacToeScreen : public Screen{
    public:
        TicTacToeScreen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players);
        void handleEvents(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window) override;
        void render(sf::RenderWindow &window) override;
        void updatePhantomPiece(sf::RenderWindow &window);
        void loadTextures();
        Coordinates getTileCoordinates(sf::FloatRect &tile);
        std::vector<sf::FloatRect> getPossiblePlays();
        void processPlay(sf::FloatRect &playTile);

    private:
        float tileSize;
        TicTacToe* game;
        sf::Vector2f screenOffset;
        sf::Texture pieceOTexture;
        sf::Texture pieceXTexture;
        sf::Texture boardTexture;
        sf::Sprite phantomPiece;

        std::vector<sf::Sprite> pieces;
        sf::Sprite board;
        
};

#endif