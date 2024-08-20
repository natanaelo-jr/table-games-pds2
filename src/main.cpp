#include <SFML/Graphics.hpp>
#include "MenuScreen.hpp"
#include "RankingScreen.hpp"
#include "GameSelectionScreen.hpp"
#include "TicTacToeScreen.hpp"
#include "Lig4Screen.hpp"
#include "MineFieldScreen.hpp"
#include "ReversiScreen.hpp"
#include <iostream>


int main(){  
    Players* players = new Players();
    players->loadFromDataFile();
    ScreenManager* screenManager = new ScreenManager();
    screenManager->push(std::make_shared<MenuScreen>(screenManager, players));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Board Games PDS2");
    screenManager->setupWindow(window);

    while (window.isOpen()) {
        screenManager->getCurrentState()->process(window);
    }
    delete players;
    delete screenManager;
    return 0;
}
