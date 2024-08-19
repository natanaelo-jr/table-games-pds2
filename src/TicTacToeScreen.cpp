#include "TicTacToeScreen.hpp"
#include <iostream>

TicTacToeScreen::TicTacToeScreen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players):
Screen(players, screenManager){
    tileSize = 100.0f;
    screenOffset = sf::Vector2f(250.0f, 150.0f);
    game = new TicTacToe(player1, player2);

    
    loadTextures();
    board.setTexture(boardTexture);
    board.setPosition(250, 150);
    phantomPiece.setTexture(pieceXTexture);
    phantomPiece.setColor(sf::Color(255, 255, 255, 128));
}

void TicTacToeScreen::loadTextures(){
    pieceOTexture.loadFromFile("assets/TicTacToe/O.png");
    pieceXTexture.loadFromFile("assets/TicTacToe/X.png");
    boardTexture.loadFromFile("assets/TicTacToe/TicTacToeBoard.png");
}

void TicTacToeScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(board);
    window.draw(phantomPiece);
    for(auto piece: pieces){
        window.draw(piece);
    }
    window.display();
}


void TicTacToeScreen::update(sf::RenderWindow &window){
    if(!game->terminalState(game->getBoard()) && isMouseOver(board.getGlobalBounds(), window)){
        phantomPiece.setColor(sf::Color(255, 255, 255, 128));
        updatePhantomPiece(window);
    }else{
        phantomPiece.setColor(sf::Color(255, 255, 255, 0));
    }
    
}
void TicTacToeScreen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                for(auto playTile: getPossiblePlays()){
                    if(isMouseOver(playTile, window)){
                        if(!game->terminalState(game->getBoard()) && 
                        game->makePlay({getTileCoordinates(playTile).getRow() +1, getTileCoordinates(playTile).getCol() +1})
                        ){
                            processPlay(playTile);
                        }
                    }
                }
            }
        }
    }
}

Coordinates TicTacToeScreen::getTileCoordinates(sf::FloatRect &tile){
    Coordinates tileCoordinates;
    tileCoordinates.setRow((tile.top - screenOffset.y) / tileSize);
    tileCoordinates.setCol((tile.left - screenOffset.x) / tileSize);
    return tileCoordinates;
}


std::vector<sf::FloatRect> TicTacToeScreen::getPossiblePlays(){
    std::vector<sf::FloatRect> possiblePlays;
    for(auto coord : game->possiblePlays(game->getBoard())){
        sf::FloatRect tile;
        tile.left = screenOffset.x + (tileSize * coord.getCol());
        tile.top = screenOffset.y + (tileSize * coord.getRow());
        tile.width = tileSize;
        tile.height = tileSize;
        possiblePlays.push_back(tile);
    }
    return possiblePlays;
}

void TicTacToeScreen::processPlay(sf::FloatRect &playTile){
    sf::Sprite piece;
    game->getCurrentPlayer() == game->getPlayer1() ? 
    piece.setTexture(pieceXTexture) : piece.setTexture(pieceOTexture);

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

void TicTacToeScreen::updatePhantomPiece(sf::RenderWindow &window){
    for(auto playTile: getPossiblePlays()){
        if(isMouseOver(playTile, window)){
            phantomPiece.setPosition(
                getTileCoordinates(playTile).getCol() * tileSize + screenOffset.x,
                getTileCoordinates(playTile).getRow() * tileSize + screenOffset.y
            );

            game->getCurrentPlayer() == game->getPlayer1() ?
            phantomPiece.setTexture(pieceXTexture) : phantomPiece.setTexture(pieceOTexture);
            phantomPiece.setColor(sf::Color(255, 255, 255, 128));
        }
    }
}