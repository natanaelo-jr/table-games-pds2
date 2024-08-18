#include <SFML/Graphics.hpp>
#include "MenuScreen.hpp"
#include "RankingScreen.hpp"
#include "GameSelectionScreen.hpp"
#include "TicTacToeScreen.hpp"
#include "Lig4Screen.hpp"
#include <iostream>
#include "Utilities.hpp"

int main(){  
    
    Players *players = new Players();

    ScreenManager* screenManager = new ScreenManager();
    screenManager->push(std::make_shared<Lig4Screen>(screenManager,new Player("P1", "p1"), new Player("P2", "p2"), players));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Board Games PDS2");
    screenManager->setupWindow(window);

    while (window.isOpen()) {
        screenManager->getCurrentState()->process(window);
    }

    return 0;
}
