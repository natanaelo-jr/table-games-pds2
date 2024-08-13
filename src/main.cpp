#include <SFML/Graphics.hpp>
#include "MenuScreen.hpp"
#include "RankingScreen.hpp"
#include "GameSelectionScreen.hpp"
#include <iostream>
#include "Utilities.hpp"

int main(){  
    
    Players *players = new Players();
    players->signUpPlayer("Joao", "joao");
    players->signUpPlayer("Maria", "maria");
    players->signUpPlayer("Pedro", "pedro");
    players->signUpPlayer("Ana", "ana");
    players->searchByNickname("joao")->winTicTacToe();
    players->searchByNickname("joao")->winTicTacToe();
    players->searchByNickname("joao")->winLig4();
    players->searchByNickname("maria")->winTicTacToe();
    players->searchByNickname("maria")->winLig4();
    players->searchByNickname("pedro")->loseReversi();

    ScreenManager* screenManager = new ScreenManager();
    screenManager->push(std::make_shared<MenuScreen>(screenManager, players));

    cleanTerminal();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Board Games PDS2");
    screenManager->setupWindow(window);

    while (window.isOpen()) {
        screenManager->getCurrentState()->process(window);
    }

    return 0;
}
