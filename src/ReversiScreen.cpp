/*#include "ReversiScreen.hpp"
#include <iostream>

ReversiScreen::ReversiScreen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players):
Screen(players, screenManager){
    tileSize = 100.0f;
    screenOffset = sf::Vector2f(176.0f, 132.0f);
    game = new Reversi(player1, player2);

    
    loadTextures();
    board.setTexture(boardTexture);
    board.setPosition(176, 132);
    phantomPiece.setTexture(pieceBTexture);
    phantomPiece.setColor(sf::Color(255, 255, 255, 128));

    cardText.setFont(cardFont);

    cardButton1.setTexture(playAgainTexture);
    cardButton1.setPosition(296, 290);
    cardButton2.setTexture(backMenuTexture);
    cardButton2.setPosition(296, 337);

}

void ReversiScreen::loadTextures(){
    pieceBTexture.loadFromFile("assets/Reversi/BlackPiece.png");
    pieceWTexture.loadFromFile("assets/Reversi/WhitePiece.png");
    boardTexture.loadFromFile("assets/Reversi/ReversiBoard.png");
}

void ReversiScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(board);
    window.draw(phantomPiece);
    for(auto piece: pieces){
        window.draw(piece);
    }
    window.display();
}


void ReversiScreen::update(sf::RenderWindow &window){
    if(!game->terminalState(game->getBoard()) && isMouseOver(board.getGlobalBounds(), window)){
        phantomPiece.setColor(sf::Color(255, 255, 255, 128));
        updatePhantomPiece(window);
    }else{
        phantomPiece.setColor(sf::Color(255, 255, 255, 0));
    }
    
}

void ReversiScreen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                for(auto playTile: getPossiblePlays()){
                    if(isMouseOver(playTile, window)){
                        if(!game->terminalState(game->getBoard())) {
                            processPlay(playTile);
                        }
                    }
                }
            }
        }
    }
}

Coordinates ReversiScreen::getTileCoordinates(sf::FloatRect &tile){
    Coordinates tileCoordinates;
    tileCoordinates.setRow((tile.top - screenOffset.y) / tileSize);
    tileCoordinates.setCol((tile.left - screenOffset.x) / tileSize);
    return tileCoordinates;
}


std::vector<sf::FloatRect> ReversiScreen::getPossiblePlays(){
    std::vector<sf::FloatRect> possiblePlays;
    for(auto coord : game->getPossiblePlays(game->getBoard())){
        sf::FloatRect tile;
        tile.left = screenOffset.x + (tileSize * coord.getCol());
        tile.top = screenOffset.y + (tileSize * coord.getRow());
        tile.width = tileSize;
        tile.height = tileSize;
        possiblePlays.push_back(tile);
    }
    return possiblePlays;
}

void ReversiScreen::processPlay(sf::FloatRect &playTile){
    sf::Sprite piece;
    game->getCurrentPlayer() == game->getPlayer1() ? 
    piece.setTexture(pieceBTexture) : piece.setTexture(pieceWTexture);

    piece.setPosition(
        getTileCoordinates(playTile).getCol() * tileSize + screenOffset.x,
        getTileCoordinates(playTile).getRow() * tileSize + screenOffset.y
    );

    pieces.push_back(piece);
    game->changePlayer();

    if(game->terminalState(game->getBoard())){
        std::cout << "Terminal State" << std::endl;
        if(game->checkWinner(game->getBoard()) != nullptr){
        }
    }
    game->printBoard();
}

void ReversiScreen::updatePhantomPiece(sf::RenderWindow &window){
    for(auto playTile: getPossiblePlays()){
        if(isMouseOver(playTile, window)){
            phantomPiece.setPosition(
                getTileCoordinates(playTile).getCol() * tileSize + screenOffset.x,
                getTileCoordinates(playTile).getRow() * tileSize + screenOffset.y
            );

            game->getCurrentPlayer() == game->getPlayer1() ?
            phantomPiece.setTexture(pieceBTexture) : phantomPiece.setTexture(pieceBTexture);
            phantomPiece.setColor(sf::Color(255, 255, 255, 128));
        }
    }
}*/