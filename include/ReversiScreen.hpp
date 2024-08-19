#ifndef REVERSISCREEN_HPP
#define REVERSISCREEN_HPP
#include "Screen.hpp"
#include "Reversi.hpp"

class ReversiScreen : public Screen{
    public:
        ReversiScreen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players);
        void handleEvents(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window) override;
        void render(sf::RenderWindow &window) override;
        void updatePieces();
        void updateShadows();

        void updatePhantomPiece(sf::RenderWindow &window);
        void loadTextures();
        Coordinates getTileCoordinates(sf::FloatRect &tile);
        std::vector<sf::FloatRect> getPossiblePlays();
        void processPlay(sf::FloatRect &playTile);


    private:
        float tileSize;
        bool finishGame;
        Reversi* game;
        sf::Vector2f screenOffset;
        sf::Texture pieceBTexture;
        sf::Texture pieceWTexture;
        sf::Texture shadowTexture;
        sf::Texture boardTexture;
        sf::Sprite phantomPiece;
        sf::Font font;

        sf::Text player1Nick;
        sf::Text player2Nick;
        sf::Sprite player1Piece;
        sf::Sprite player2Piece;

        std::vector<sf::Sprite> pieces;
        std::vector<sf::Sprite> possiblePieces;
        sf::Sprite board;

        sf::RectangleShape cardShape;
        sf::Sprite cardButton1;
        sf::Sprite cardButton2;
        sf::Text cardText;
        
};

#endif