#include "Lig4Screen.hpp"
#include <iostream>

Lig4Screen::Lig4Screen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players):
Screen(players, screenManager){
    loadTextures();
    tileSize = 76.0f;
    screenOffset = sf::Vector2f(172.0f, 60.0f);
    game = new Lig4(player1, player2);

    player1Piece.setTexture(pieceVTexture);
    player1Piece.setPosition(0, 0);

    player2Piece.setTexture(pieceATexture);
    player2Piece.setPosition(724, 0);

    player1Nick.setFont(font);
    player1Nick.setFillColor(sf::Color::White);
    player1Nick.setString(game->getPlayer1()->getNickname());
    player1Nick.setPosition(76, 16);

    player2Nick.setFont(font);
    player2Nick.setFillColor(sf::Color::White);
    player2Nick.setString(game->getPlayer2()->getNickname());
    player2Nick.setOrigin(player2Nick.getLocalBounds().width, 0);
    player2Nick.setPosition(724, 16);

    board.setTexture(boardTexture);
    board.setPosition(172, 60);
    phantomPiece.setTexture(pieceVTexture);
    phantomPiece.setColor(sf::Color(255, 255, 255, 128));
}

void Lig4Screen::loadTextures(){
    pieceATexture.loadFromFile("assets/Lig4/PeçaA.png");
    pieceVTexture.loadFromFile("assets/Lig4/PeçaV.png");
    boardTexture.loadFromFile("assets/Lig4/Lig4Board.png");
    font.loadFromFile("assets/font/Sniglet-Regular.ttf");
}

void Lig4Screen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(board);
    window.draw(player1Nick);
    window.draw(player1Piece);
    window.draw(player2Nick);
    window.draw(player2Piece);
    window.draw(phantomPiece);
    for(auto piece: pieces){
        window.draw(piece);
    }
    window.display();
}

void Lig4Screen::update(sf::RenderWindow &window){
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

void Lig4Screen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                for(auto playTile: getPossiblePlays()){
                    if(isMouseOver(playTile, window)){
                        if(!game->terminalState(game->getBoard())){
                            processPlay(playTile);
                        }
                    }
                }
            }
        }
    }
}

Coordinates Lig4Screen::getTileCoordinates(sf::FloatRect &tile){
    Coordinates tileCoordinates;
    tileCoordinates.setRow((tile.top - screenOffset.y) / tileSize);
    tileCoordinates.setCol((tile.left - screenOffset.x) / tileSize);
    return tileCoordinates;
}

std::vector<sf::FloatRect> Lig4Screen::getPossiblePlays(){
    std::vector<sf::FloatRect> possiblePlays;
    for(int col : game->possiblePlays(game->getBoard())){
        sf::FloatRect tile;
        tile.left = screenOffset.x + (tileSize * col);
        tile.top = screenOffset.y;
        tile.width = tileSize;
        tile.height = game->getRows() * tileSize;
        possiblePlays.push_back(tile);
    }
    return possiblePlays;
}

void Lig4Screen::processPlay(sf::FloatRect &playTile){
    sf::Sprite piece;
    game->getCurrentPlayer() == game->getPlayer1() ? 
    piece.setTexture(pieceATexture) : piece.setTexture(pieceVTexture);

    int col = getTileCoordinates(playTile).getCol();
    for(int row = game->getRows() - 1; row >= 0; row--){
        if(game->getSquare({row, col}, game->getBoard()) == ' '){
            piece.setPosition(col * tileSize + screenOffset.x,
                              row * tileSize + screenOffset.y);
            break;
        }
    }
    pieces.push_back(piece);
    game->makePlay(getTileCoordinates(playTile).getCol() + 1);
    game->changePlayer();

    if(game->terminalState(game->getBoard())){
        std::cout << "Terminal State" << std::endl;
        if(game->checkWinner(game->getBoard()) != nullptr){
        }
    }
    game->printBoard();
}

void Lig4Screen::updatePhantomPiece(sf::RenderWindow &window){
    for(auto playTile: getPossiblePlays()){
        if(isMouseOver(playTile, window)){
            int col = getTileCoordinates(playTile).getCol();
            int row = game->getRows()-1;
            while(game->getSquare({row, col}, game->getBoard()) != ' '){
                row--;
            }
            
            phantomPiece.setPosition(
                col * tileSize + screenOffset.x,
                row * tileSize + screenOffset.y
            );

            game->getCurrentPlayer() == game->getPlayer1() ?
            phantomPiece.setTexture(pieceATexture) : phantomPiece.setTexture(pieceVTexture);
            phantomPiece.setColor(sf::Color(255, 255, 255, 128));
        }
    }
}