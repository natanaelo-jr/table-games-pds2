#include "MenuScreen.hpp"
#include "RankingScreen.hpp"
#include "GameSelectionScreen.hpp"
#include "ManageScreen.hpp"
#include <iostream>

void MenuScreen::loadTextures(){
    playButtonTexture.loadFromFile("assets/Menu/PlayButton.png");
    hoverPlayButtonTexture.loadFromFile("assets/Menu/PlayButtonH.png");

    manageButtonTexture.loadFromFile("assets/Menu/ManageButton.png");
    hoverManageButtonTexture.loadFromFile("assets/Menu/ManageButtonH.png");

    rankingButtonTexture.loadFromFile("assets/Menu/RankingButton.png");
    hoverRankingButtonTexture.loadFromFile("assets/Menu/RankingButtonH.png");

    creditsButtonTexture.loadFromFile("assets/Menu/CreditsButton.png");
    hoverCreditsButtonTexture.loadFromFile("assets/Menu/CreditsButtonH.png");

    exitButtonTexture.loadFromFile("assets/Menu/ExitButton.png");
    hoverExitButtonTexture.loadFromFile("assets/Menu/ExitButtonH.png");
}

MenuScreen::MenuScreen(ScreenManager* screenManager, Players* players) : Screen(players, screenManager){
    loadTextures();

    playButton.setTexture(playButtonTexture);
    playButton.setPosition(247, 124);

    manageButton.setTexture(manageButtonTexture);
    manageButton.setPosition(247, 221);
 
    rankingButton.setTexture(rankingButtonTexture);
    rankingButton.setPosition(247, 318);

    creditsButton.setTexture(creditsButtonTexture);
    creditsButton.setPosition(197, 415);

    exitButton.setTexture(exitButtonTexture);
    exitButton.setPosition(402, 415);
}

void MenuScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(playButton);
    window.draw(manageButton);
    window.draw(rankingButton);
    window.draw(creditsButton);
    window.draw(exitButton);
    window.display();
}

void MenuScreen::update(sf::RenderWindow &window){
    isMouseOver(playButton.getGlobalBounds(), window) && getPlayers()->getsize() > 0 ?
        playButton.setTexture(hoverPlayButtonTexture) : playButton.setTexture(playButtonTexture);

    isMouseOver(manageButton.getGlobalBounds(), window) ? manageButton.setTexture(hoverManageButtonTexture) : manageButton.setTexture(manageButtonTexture);
    isMouseOver(rankingButton.getGlobalBounds(), window) && getPlayers()->getsize() > 0 ?
        rankingButton.setTexture(hoverRankingButtonTexture) : rankingButton.setTexture(rankingButtonTexture);

    isMouseOver(creditsButton.getGlobalBounds(), window) ? creditsButton.setTexture(hoverCreditsButtonTexture) : creditsButton.setTexture(creditsButtonTexture);
    isMouseOver(exitButton.getGlobalBounds(), window) ? exitButton.setTexture(hoverExitButtonTexture) : exitButton.setTexture(exitButtonTexture);
}

void MenuScreen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                if(isMouseOver(playButton.getGlobalBounds(), window)){
                    if(getPlayers()->getsize() > 0){
                        getScreenManager()->change(std::make_shared<GameSelectionScreen>(getScreenManager(), getPlayers()));
                    }
                }
                if(isMouseOver(manageButton.getGlobalBounds(), window)){
                    getScreenManager()->change(std::make_shared<ManageScreen>(getScreenManager(), getPlayers()));
                }
                if(isMouseOver(rankingButton.getGlobalBounds(), window)){
                    if(getPlayers()->getsize() > 0){
                        getScreenManager()->change(std::make_shared<RankingScreen>(getScreenManager(), getPlayers()));
                    }
                }
                if(isMouseOver(creditsButton.getGlobalBounds(), window)){
                    std::cout << "Credits button clicked" << std::endl;
                }
                if(isMouseOver(exitButton.getGlobalBounds(), window)){
                    window.close();
                }
            }
        }
    }
}