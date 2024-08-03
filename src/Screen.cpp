#include "Screen.hpp"

Screen::Screen(){
    cursorImage.loadFromFile("assets/Cursor.png");
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), sf::Vector2u(cursorImage.getSize().x, cursorImage.getSize().y), sf::Vector2u(9, 3));
    backgroundColor = sf::Color(181, 145, 148);
    icon.loadFromFile("assets/Icon.png");
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