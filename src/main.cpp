#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include <iostream>

int main(){
    
    sf::Image icon;
    icon.loadFromFile("assets/Icon.png");
    sf::RenderWindow window(sf::VideoMode(800, 600), "BoardGamesPDS2");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    Screen* currentScreen = new Menu();
    
    while (window.isOpen()) {
        currentScreen->update(window);
        currentScreen->handleEvents(window);
        currentScreen->render(window);
    }
    return 0;
}
