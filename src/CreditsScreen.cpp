#include "CreditsScreen.hpp"
#include "MenuScreen.hpp"
#include <random>
#include <iostream>

CreditsScreen::CreditsScreen(ScreenManager* screenManager, Players* players) : Screen(players, screenManager){
    loadTextures();
    generateBaloes();
}

void CreditsScreen::loadTextures(){
    colaboradoresTexture.loadFromFile("assets/Credits/Colaboradores.png");
    colaboradoresSprite.setTexture(colaboradoresTexture);
    colaboradoresSprite.setPosition(154, 0);

    backButtonTexture.loadFromFile("assets/BackButton.png");
    hoverBackButtonTexture.loadFromFile("assets/BackButtonH.png");
    backButton.setTexture(backButtonTexture);
    backButton.setPosition(15, 15);

    balaoTexture.loadFromFile("assets//Credits/balloon.png");
}

void CreditsScreen::generateBaloes(){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> xdis(80, 720);
    std::uniform_int_distribution<int> ydis(0, 600);
    std::uniform_int_distribution<int> color(0, 255);

    for(int i = 0; i < 10; i++){
        sf::Sprite balao;
        balao.setTexture(balaoTexture);
        balao.setPosition(xdis(gen), ydis(gen));
        balao.setColor(sf::Color(color(gen), color(gen), color(gen), 150));
        baloes.push_back(balao);
    }
}

void CreditsScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    for(auto &balao : baloes){
        window.draw(balao);
    }
    window.draw(backButton);
    window.draw(colaboradoresSprite);
    window.display();
}

void CreditsScreen::update(sf::RenderWindow &window){
    isMouseOver(backButton.getGlobalBounds(), window) ?
    backButton.setTexture(hoverBackButtonTexture) : backButton.setTexture(backButtonTexture);
    float deltaTime = clock.restart().asSeconds();
    if(deltaTime < frameTime){
        sf::sleep(sf::seconds(frameTime - deltaTime));
    }
    for(auto &balao : baloes){
        balao.move(0, -1);
        if(balao.getPosition().y < -100){
            balao.setPosition(rand() % 800, 600);
        }
    }
}

void CreditsScreen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(isMouseOver(backButton.getGlobalBounds(), window)){
                getScreenManager()->change(std::make_shared<MenuScreen>(getScreenManager(), getPlayers()));
            }
        }
    }
}