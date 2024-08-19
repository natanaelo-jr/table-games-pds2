#include <SFML/Graphics.hpp>
#include "MenuScreen.hpp"
#include "RankingScreen.hpp"
#include "GameSelectionScreen.hpp"
#include "TicTacToeScreen.hpp"
#include "Lig4Screen.hpp"
#include "MineFieldScreen.hpp"
#include "ReversiScreen.hpp"
#include <iostream>
#include "Utilities.hpp"

int main(){  
    Players* players = new Players();
    ScreenManager* screenManager = new ScreenManager();
    Player* p1 = new Player ("p1", "Player 1");
    Player* p2 = new Player ("p2", "Player 2");

    screenManager->push(std::make_shared<MenuScreen>(screenManager, players));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Board Games PDS2");
    screenManager->setupWindow(window);

    while (window.isOpen()) {
        screenManager->getCurrentState()->process(window);
    }
    return 0;
}
