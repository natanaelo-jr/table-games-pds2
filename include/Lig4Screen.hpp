#ifndef LIG4SCREEN_HPP
#define LIG4SCREEN_HPP
#include "Screen.hpp"
#include "Lig4.hpp"

class Lig4Screen : public Screen{
    public:
        Lig4Screen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players);
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
        Lig4* game;
        sf::Vector2f screenOffset;
        sf::Texture pieceVTexture;
        sf::Texture pieceATexture;
        sf::Texture boardTexture;
        sf::Sprite phantomPiece;
        sf::Font font;

        sf::Text player1Nick;
        sf::Text player2Nick;
        sf::Sprite player1Piece;
        sf::Sprite player2Piece;

        std::vector<sf::Sprite> pieces;
        sf::Sprite board;

        sf::RectangleShape cardShape;
        sf::Sprite cardButton1;
        sf::Sprite cardButton2;
        sf::Text cardText;

        bool finishGame;
};

#endif