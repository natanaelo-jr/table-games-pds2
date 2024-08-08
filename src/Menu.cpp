#include "Menu.hpp"
#include "Sounds.hpp"
#include <iostream>
sf::Color backgroundColor = sf::Color::White;

void Menu::loadTextures(){
    playButtonTexture.loadFromFile("assets/PlayButton.png");
    hoverPlayButtonTexture.loadFromFile("assets/PlayButtonH.png");

    manageButtonTexture.loadFromFile("assets/ManageButton.png");
    hoverManageButtonTexture.loadFromFile("assets/ManageButtonH.png");

    rankingButtonTexture.loadFromFile("assets/RankingButton.png");
    hoverRankingButtonTexture.loadFromFile("assets/RankingButtonH.png");

    creditsButtonTexture.loadFromFile("assets/CreditsButton.png");
    hoverCreditsButtonTexture.loadFromFile("assets/CreditsButtonH.png");

    exitButtonTexture.loadFromFile("assets/ExitButton.png");
    hoverExitButtonTexture.loadFromFile("assets/ExitButtonH.png");
}

Menu::Menu(){
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

void Menu::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(playButton);
    window.draw(manageButton);
    window.draw(rankingButton);
    window.draw(creditsButton);
    window.draw(exitButton);
    window.display();
}


bool Menu::isMouseOver(sf::Sprite& button, sf::RenderWindow &window){
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    buttonBounds.width -=8;
    buttonBounds.height -=8;
    buttonBounds.left +=4;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return buttonBounds.contains(mousePosition.x, mousePosition.y);
}


void Menu::update(sf::RenderWindow &window){
    isMouseOver(playButton, window) ? playButton.setTexture(hoverPlayButtonTexture) : playButton.setTexture(playButtonTexture);
    isMouseOver(manageButton, window) ? manageButton.setTexture(hoverManageButtonTexture) : manageButton.setTexture(manageButtonTexture);
    isMouseOver(rankingButton, window) ? rankingButton.setTexture(hoverRankingButtonTexture) : rankingButton.setTexture(rankingButtonTexture);
    isMouseOver(creditsButton, window) ? creditsButton.setTexture(hoverCreditsButtonTexture) : creditsButton.setTexture(creditsButtonTexture);
    isMouseOver(exitButton, window) ? exitButton.setTexture(hoverExitButtonTexture) : exitButton.setTexture(exitButtonTexture);
}

void Menu::handleEvents(sf::RenderWindow &window){
    Sounds effects;
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                if(isMouseOver(playButton, window)){
                    std::cout << "Play button clicked" << std::endl;
                    effects.play();                }
                if(isMouseOver(manageButton, window)){
                    std::cout << "Manage button clicked" << std::endl;
                    effects.soundClick();
                }
                if(isMouseOver(rankingButton, window)){
                    std::cout << "Ranking button clicked" << std::endl;
                    effects.soundClick();
                }
                if(isMouseOver(creditsButton, window)){
                    std::cout << "Credits button clicked" << std::endl;
                    effects.soundClick();
                }
                if(isMouseOver(exitButton, window)){
                    effects.soundLost();
                    window.close();
                }
            }
        }
    }
}