#include "MineFieldScreen.hpp"
#include "MenuScreen.hpp"
#include <iostream>

MineFieldScreen::MineFieldScreen(ScreenManager* screenManager, Player* player, Players* players) :
Screen(players, screenManager){
    tileSize = 40.0f;
    screenOffset = sf::Vector2f(193.0f + 6.0f, 134.0f + 6.0f);
    game = new MineField(player, 10, 12);
    loadTextures();

    board.setTexture(boardTexture);
    board.setPosition(193, 134);
    isNewGame = true;
    finishGame = false;

    playerNick.setString(player->getNickname());
    playerNick.setFont(font);
    playerNick.setCharacterSize(60);
    playerNick.setFillColor(sf::Color(77, 14, 70));
    playerNick.setOrigin(playerNick.getLocalBounds().width / 2, 0);
    playerNick.setPosition(400, 20);

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

void MineFieldScreen::loadTextures(){
    BandTexture.loadFromFile("assets/MineField/BandeiraCM.png");
    BombTexture.loadFromFile("assets/MineField/BombaCM.png");
    QuadTexture.loadFromFile("assets/MineField/QuadAberto.png");
    boardTexture.loadFromFile("assets/MineField/MineFieldBoard.png");
    font.loadFromFile("assets/font/SuperDream.ttf");
}

void MineFieldScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(board);
    for(auto piece: pieces){
        window.draw(piece);
    }
    for(auto flag: flags){
        window.draw(flag);
    }
    for(auto number: numbers){
        window.draw(number);
    }
    if(finishGame){
        window.draw(cardShape);
        window.draw(cardButton1);
        window.draw(cardButton2);
        window.draw(cardText);
    }
    window.draw(playerNick);

    window.display();
}


void MineFieldScreen::update(sf::RenderWindow &window){
    if(finishGame){
        isMouseOver(cardButton1.getGlobalBounds(), window) ? cardButton1.setTexture(hoverPlayAgainTexture) : cardButton1.setTexture(playAgainTexture);
        isMouseOver(cardButton2.getGlobalBounds(), window) ? cardButton2.setTexture(hoverBackMenuTexture) : cardButton2.setTexture(backMenuTexture);
        if(isMouseOver(cardShape.getGlobalBounds(), window)){
            cardShape.setFillColor(sf::Color(204, 221, 211, 255));
            cardText.setFillColor(sf::Color(22, 69, 54, 255));
            cardButton1.setColor(sf::Color(255, 255, 255, 255));
            cardButton2.setColor(sf::Color(255, 255, 255, 255));
        }else{
            cardShape.setFillColor(sf::Color(204, 221, 211, 50));
            cardText.setFillColor(sf::Color(22, 69, 54, 50));
            cardButton1.setColor(sf::Color(255, 255, 255, 50));
            cardButton2.setColor(sf::Color(255, 255, 255, 50));
        }
    }
}

void MineFieldScreen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.setMouseCursor(sf::Cursor());
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            if(finishGame){
                if(isMouseOver(cardButton1.getGlobalBounds(), window)){
                    getScreenManager()->change(std::make_shared<MineFieldScreen>(getScreenManager(), game->getPlayer1(), getPlayers()));
                }
                if(isMouseOver(cardButton2.getGlobalBounds(), window)){
                    getScreenManager()->change(std::make_shared<MenuScreen>(getScreenManager(), getPlayers()));
                }
            } else {
                for(auto playTile : getPossiblePlays()) {
                    if(isMouseOver(playTile, window)) {
                        Coordinates coord = getTileCoordinates(playTile);
                        if(isFlagOnTile(coord)){
                            removeFlag(coord);
                        } else{
                            processPlay(playTile);
                        }
                    }
                }
            }
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
            if(!finishGame) {
                for(auto &playTile : getPossiblePlays()){
                    if(isMouseOver(playTile, window)) {
                        Coordinates coord = getTileCoordinates(playTile);
                        if(isFlagOnTile(coord)) {
                            removeFlag(coord);
                        } else {
                            placeFlag(coord);
                        }
                    }           
                }
            }
        }
    }
}   
Coordinates MineFieldScreen::getTileCoordinates(sf::FloatRect &tile){
    Coordinates tileCoordinates;
    tileCoordinates.setRow((tile.top - screenOffset.y) / tileSize);
    tileCoordinates.setCol((tile.left - screenOffset.x) / tileSize);
    return tileCoordinates;
}


std::vector<sf::FloatRect> MineFieldScreen::getPossiblePlays(){
    std::vector<sf::FloatRect> possiblePlays;
    for(auto coord : game->getPossiblePlays()){
        sf::FloatRect tile;
        tile.left = screenOffset.x + (tileSize * coord.getCol());
        tile.top = screenOffset.y + (tileSize * coord.getRow());
        tile.width = tileSize;
        tile.height = tileSize;
        possiblePlays.push_back(tile);
    }
    return possiblePlays;
}

void MineFieldScreen::processPlay(sf::FloatRect &playTile){
    Coordinates coord = getTileCoordinates (playTile);
    
    if(isNewGame){
        game->setReferenceField(coord);
        isNewGame = false;
    }
    
    sf::Sprite piece;
    if (!game->makePlay({coord.getRow()+1, coord.getCol()+1})){
        game->revealBoard();
        updatePieces();
        cardText.setString(game->getPlayer1()->getNickname() + " perdeu!");
        cardText.setOrigin(cardText.getLocalBounds().width / 2, 0);
        cardText.setPosition(416, 222);
        game->getPlayer1()->loseMinefield();
        finishGame = true;
    }
    else {
        updatePieces();
        if(game->isGameOver()){
            cardText.setString(game->getPlayer1()->getNickname() + " ganhou!");
            cardText.setOrigin(cardText.getLocalBounds().width / 2, 0);
            cardText.setPosition(416, 222);
            game->getPlayer1()->winMinefield();
            finishGame = true;
        }
    }
}


void MineFieldScreen::placeFlag(Coordinates coord) {
    sf::Sprite flag;
    flag.setTexture(BandTexture);
    flag.setPosition(screenOffset.x + (coord.getCol() * tileSize), screenOffset.y + coord.getRow() * tileSize);
    flags.push_back(flag);
}


void MineFieldScreen::removeFlag(Coordinates coord) {
    for(auto it = flags.begin(); it != flags.end(); ) {
        sf::FloatRect flagBounds = it->getGlobalBounds();
        Coordinates flagCoord = getTileCoordinates(flagBounds);

        if(flagCoord.getRow() == coord.getRow() && flagCoord.getCol() == coord.getCol()) {
            it = flags.erase(it);
        } else {
            ++it;
        }
    }
}

bool MineFieldScreen::isFlagOnTile(Coordinates coord){
    for(auto flag : flags){
        sf::FloatRect flagBounds = flag.getGlobalBounds();
        Coordinates tilePosition = getTileCoordinates(flagBounds);
        if(tilePosition.getRow() == coord.getRow() && tilePosition.getCol() == coord.getCol()){
            return true;
        }
    }
    return false;
}

void MineFieldScreen::updatePieces(){
    pieces.clear();
    numbers.clear();
    for(int row = 0; row < game->getRows(); row++){
        for(int col = 0; col < game->getCols(); col++){
            char symbol = game->getSquare({row, col}, game->getBoard());
            if(symbol == ' '){
                continue;
            }
            sf::Sprite piece;
            if(symbol == '9'){
                piece.setTexture(BombTexture);
            } else {
                piece.setTexture(QuadTexture);
            }
            piece.setPosition(screenOffset.x + (col * tileSize), screenOffset.y + row * tileSize);
            pieces.push_back(piece);
            if(symbol != ' ' && symbol != '9' && symbol != '0'){
                sf::Text number;
                number.setFont(font);
                number.setCharacterSize(32);
                number.setFillColor(sf::Color(77, 14, 70));
                number.setPosition(screenOffset.x + (col * tileSize) + 10, screenOffset.y + row * tileSize);
                number.setString(symbol);
                numbers.push_back(number);
            }
        }
    }
}