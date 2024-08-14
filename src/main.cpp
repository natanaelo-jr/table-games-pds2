#include <SFML/Graphics.hpp>
#include "MenuScreen.hpp"
#include "RankingScreen.hpp"
#include "GameSelectionScreen.hpp"
#include <iostream>
#include "Utilities.hpp"

int main(){  
    
    Players *players = new Players();

    ScreenManager* screenManager = new ScreenManager();
    screenManager->push(std::make_shared<MenuScreen>(screenManager, players));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Board Games PDS2");
    screenManager->setupWindow(window);

    while (window.isOpen()) {
        screenManager->getCurrentState()->process(window);
    }

    return 0;
}
