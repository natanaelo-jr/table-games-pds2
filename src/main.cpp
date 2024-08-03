#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include <iostream>
#include "Utilities.hpp"

int main(){  
    
    cleanTerminal();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Board Games PDS2");
    Screen* currentScreen = new Menu();
    currentScreen->setupWindow(window);
    
    while (window.isOpen()) {
        currentScreen->process(window);
}
    return 0;
}
