#include "ReversiScreen.hpp"
#include <iostream>

ReversiScreen::ReversiScreen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players):
Screen(players, screenManager){
    tileSize = 56.0f;
    screenOffset = sf::Vector2f(176.0f, 132.0f);
    game = new Reversi(player1, player2);
    loadTextures();

    player1Piece.setTexture(pieceWTexture);
    player1Piece.setPosition(0, 0);

    player2Piece.setTexture(pieceBTexture);
    player2Piece.setPosition(744, 0);

    player1Nick.setFont(font);
    player1Nick.setCharacterSize(48);
    player1Nick.setFillColor(sf::Color::White);
    player1Nick.setString(game->getPlayer1()->getNickname());
    player1Nick.setPosition(66, 0);

    player2Nick.setFont(font);
    player2Nick.setCharacterSize(48);
    player2Nick.setFillColor(sf::Color::White);
    player2Nick.setString(game->getPlayer2()->getNickname());
    player2Nick.setOrigin(player2Nick.getLocalBounds().width, 0);
    player2Nick.setPosition(734, 0);


    board.setTexture(boardTexture);
    board.setPosition(176, 132);
    phantomPiece.setTexture(pieceWTexture);
    phantomPiece.setColor(sf::Color(255, 255, 255, 0));

    cardText.setFont(cardFont);

    cardButton1.setTexture(playAgainTexture);
    cardButton1.setPosition(296, 290);
    cardButton2.setTexture(backMenuTexture);
    cardButton2.setPosition(296, 337);

    updatePieces();
    updateShadows();

}

void ReversiScreen::loadTextures(){
    pieceBTexture.loadFromFile("assets/Reversi/BlackPiece.png");
    pieceWTexture.loadFromFile("assets/Reversi/WhitePiece.png");
    boardTexture.loadFromFile("assets/Reversi/ReversiBoard.png");
    shadowTexture.loadFromFile("assets/Reversi/Sombra.png");
    font.loadFromFile("assets/font/Sniglet-Regular.ttf");
}

void ReversiScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(board);
    window.draw(player1Nick);
    window.draw(player1Piece);
    window.draw(player2Nick);
    window.draw(player2Piece);
    window.draw(phantomPiece);
    for(auto shadowPiece: possiblePieces){
        window.draw(shadowPiece);
    }
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

     if(game->getCurrentPlayer() == game->getPlayer1()){
        player1Nick.setFillColor(sf::Color(255,255,255,255));
        player1Piece.setColor(sf::Color(255,255,255,255));
        player2Nick.setFillColor(sf::Color(255,255,255,155));
        player2Piece.setColor(sf::Color(255,255,255,155));
    }else{
        player1Nick.setFillColor(sf::Color(255,255,255,155));
        player1Piece.setColor(sf::Color(255,255,255,155));
        player2Nick.setFillColor(sf::Color(255,255,255,255));
        player2Piece.setColor(sf::Color(255,255,255,255));
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
    char symbol = game -> getCurrentPlayer() == game -> getPlayer1() ? 'X' : 'O';
    for(auto coord : game->getPossiblePlays(symbol, game->getBoard())){
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
    game->makePlay(getTileCoordinates(playTile).getRow(), getTileCoordinates(playTile).getCol());
    updatePieces();

    if(game->terminalState(game->getBoard())){
        std::cout << "Terminal State" << std::endl;
        if(game->checkWinner() != nullptr){
        }
    }
    game->changePlayer();
    updateShadows();
    game->printBoard();
}

void ReversiScreen::updatePhantomPiece(sf::RenderWindow &window){
    for(auto playTile: getPossiblePlays()){
        if(isMouseOver(playTile, window)){
            if (game -> getCurrentPlayer() == game -> getPlayer1()){
                phantomPiece.setTexture(pieceWTexture);
            }
            else {
                phantomPiece.setTexture(pieceBTexture);
            }
            phantomPiece.setPosition(
                getTileCoordinates(playTile).getCol() * tileSize + screenOffset.x,
                getTileCoordinates(playTile).getRow() * tileSize + screenOffset.y
            );

            //game->getCurrentPlayer() == game->getPlayer1() ?
            //phantomPiece.setTexture(pieceWTexture) : phantomPiece.setTexture(pieceBTexture);
            phantomPiece.setColor(sf::Color(255, 255, 255, 128));
        }
    }
}

void ReversiScreen::updatePieces(){
    pieces.clear();

    for(int row = 0; row < game->getRows(); row++){
        for(int col = 0; col < game->getCols(); col++){
            if(game->getSquare({row, col}, game->getBoard()) == 'X'){
                sf::Sprite piece;
                piece.setTexture(pieceWTexture);
                piece.setPosition(
                    (col * tileSize) + screenOffset.x,
                    (row * tileSize) + screenOffset.y
                );
                pieces.push_back(piece);
            }

            if(game->getSquare({row, col}, game->getBoard()) == 'O'){
                sf::Sprite piece;
                piece.setTexture(pieceBTexture);
                piece.setPosition(
                    (col * tileSize) + screenOffset.x,
                    (row * tileSize) + screenOffset.y
                );
                pieces.push_back(piece);
            }
        }
    }


}

void ReversiScreen::updateShadows(){
    possiblePieces.clear();
    for(auto tile : getPossiblePlays()){
        sf::Sprite shadowPiece;
        shadowPiece.setPosition(tile.left, tile.top);
        shadowPiece.setTexture(shadowTexture);
        shadowPiece.setColor(sf::Color(255,255,255,100));
        possiblePieces.push_back(shadowPiece);
    }
}