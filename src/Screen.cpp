#include "Screen.hpp"
#include "ScreenManager.hpp"

Screen::Screen(Players* players, ScreenManager* screenManager){
    this->players = players;
    this->screenManager = screenManager;

    cursorImage.loadFromFile("assets/Cursor.png");
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), sf::Vector2u(cursorImage.getSize().x, cursorImage.getSize().y), sf::Vector2u(9, 3));
    backgroundColor = sf::Color(181, 145, 148);
    
    icon.loadFromFile("assets/Icon.png");

    backMenuTexture.loadFromFile("assets/Results/MainMenuButton.png");
    hoverBackMenuTexture.loadFromFile("assets/Results/MainMenuButtonH.png");
    playAgainTexture.loadFromFile("assets/Results/PlayAgainButton.png");
    hoverPlayAgainTexture.loadFromFile("assets/Results/PlayAgainButtonH.png");
    cardFont.loadFromFile("assets/font/SuperDream.ttf");
    
}

sf::Color Screen::getBackgroundColor(){
    return backgroundColor;
}

void Screen::setupWindow(sf::RenderWindow &window){
    window.setMouseCursor(cursor);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Screen::process(sf::RenderWindow &window){
    update(window);
    handleEvents(window);
    render(window);
}

bool Screen::isMouseOver(const sf::FloatRect & bounds, const sf::RenderWindow &window){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return bounds.contains(mousePosition.x, mousePosition.y);
}

Players* Screen::getPlayers(){
    return players;
}

ScreenManager* Screen::getScreenManager(){
    return screenManager;
}