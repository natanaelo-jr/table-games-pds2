/*#include "MineFieldScreen.hpp"
#include "MenuScreen.hpp"
#include <iostream>

MineFieldScreen::TicTacToeScreen(ScreenManager* screenManager, Player* player1, Player* player2, Players* players):
Screen(players, screenManager){
    tileSize = 100.0f;
    screenOffset = sf::Vector2f(250.0f, 150.0f);
    game = new TicTacToe(player1, player2);
    loadTextures();

    board.setTexture(boardTexture);
    board.setPosition(250, 150);
    phantomPiece.setTexture(pieceXTexture);
    phantomPiece.setColor(sf::Color(255, 255, 255, 128));

//
    finishGame = false;
    cardShape.setFillColor(sf::Color(204, 221, 211));
    cardShape.setSize(sf::Vector2f(500, 200));
    cardShape.setPosition(166, 204);

    cardText.setFont(cardFont);
    cardText.setCharacterSize(40);
    cardText.setFillColor(sf::Color(22, 69, 54));

    cardButton1.setTexture(playAgainTexture);
    cardButton1.setPosition(296, 290);
    cardButton2.setTexture(backMenuTexture);
    cardButton2.setPosition(296, 337);
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
    if(finishGame){
        window.draw(cardShape);
        window.draw(cardButton1);
        window.draw(cardButton2);
        window.draw(cardText);
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

    if(finishGame){
        isMouseOver(cardButton1.getGlobalBounds(), window) ? cardButton1.setTexture(hoverPlayAgainTexture) : cardButton1.setTexture(playAgainTexture);
        isMouseOver(cardButton2.getGlobalBounds(), window) ? cardButton2.setTexture(hoverBackMenuTexture) : cardButton2.setTexture(backMenuTexture);
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
                if(finishGame){
                    if(isMouseOver(cardButton1.getGlobalBounds(), window)){
                        getScreenManager()->change(std::make_shared<TicTacToeScreen>(getScreenManager(), game->getPlayer1(), game->getPlayer2(), getPlayers()));
                    }
                    if(isMouseOver(cardButton2.getGlobalBounds(), window)){
                        getScreenManager()->change(std::make_shared<MenuScreen>(getScreenManager(), getPlayers()));
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
        finishGame = true;
        Player* winner;
        winner = game->checkWinner(game->getBoard());
        if(winner != nullptr){
            cardText.setString(game->checkWinner(game->getBoard())->getNickname() + " Ganhou!");
            cardText.setOrigin(cardText.getLocalBounds().width / 2, 0);
            cardText.setPosition(416, 222);
        }else{
            cardText.setString("Empate!");
            cardText.setOrigin(cardText.getLocalBounds().width / 2, 0);
            cardText.setPosition(416, 222);
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
}*/