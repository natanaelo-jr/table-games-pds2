#ifndef MINEFIELDSCREEN_HPP
#define MINEFIELDSCREEN_HPP
#include "Screen.hpp"
#include "MineField.hpp"

class MineFieldScreen : public Screen{
    public:
        MineFieldScreen(ScreenManager* screenManager, Player* player, Players* players);
        void handleEvents(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window) override;
        void render(sf::RenderWindow &window) override;

        void loadTextures();
        void updatePieces();
        Coordinates getTileCoordinates(sf::FloatRect &tile);
        std::vector<sf::FloatRect> getPossiblePlays();
        void processPlay(sf::FloatRect &playTile);
        void placeFlag(Coordinates coord);
        void removeFlag(Coordinates coord);
        bool isFlagOnTile(Coordinates coord);


    private:
        bool isNewGame;
        float tileSize;
        MineField* game;
        sf::Vector2f screenOffset;
        sf::Texture BombTexture;
        sf::Texture BandTexture;
        sf::Texture QuadTexture;
        sf::Texture boardTexture;
        sf::Font font;
        sf::Font numberFont;

        sf::Text playerNick;
        sf::Sprite playerPiece;

        std::vector<sf::Sprite> pieces;
        std::vector<sf::Sprite> flags;
        std::vector<sf::Text> numbers;
        sf::Sprite board;

        sf::RectangleShape cardShape;
        sf::Sprite cardButton1;
        sf::Sprite cardButton2;
        sf::Text cardText;

        bool finishGame;
};

#endif