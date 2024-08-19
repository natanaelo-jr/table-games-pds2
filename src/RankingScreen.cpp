#include "RankingScreen.hpp"
#include "MenuScreen.hpp"
#include <iostream>

RankingScreen::RankingScreen(ScreenManager* screenManager, Players *players) : Screen(players, screenManager){
    loadTextures();

    for(auto player : players->getPlayersByVictories()){
        this->playersList.push_back(player);
    }

    playerCard.setTexture(playerCardTexture);
    playerCard.setPosition(150, 150);

    backButton.setTexture(backButtonTexture);
    backButton.setPosition(15, 15);

    Jogador.setTexture(JogadorTexture);
    Jogador.setPosition(316, 72);

    previousButton.setTexture(previousButtonTexture);
    previousButton.setPosition(75, 270);

    nextButton.setTexture(nextButtonTexture);
    nextButton.setPosition(725-60, 270);

    name.setFont(textFont);
    name.setCharacterSize(32);
    name.setFillColor(mainColor);
    name.setPosition(107+150, 10+150);

    nickname.setFont(textFont);
    nickname.setCharacterSize(32);
    nickname.setFillColor(mainColor);
    nickname.setPosition(85+150, 55+150);

    position.setFont(textFont);
    position.setCharacterSize(32);
    position.setFillColor(mainColor);
    position.setPosition(367+150, 10+150);

    TicTacToeWins.setFont(textFont);
    TicTacToeWins.setCharacterSize(16);
    TicTacToeWins.setFillColor(green);
    TicTacToeWins.setPosition(150+71+9, 150+153+53);

    TicTacToeLosses.setFont(textFont);
    TicTacToeLosses.setCharacterSize(16);
    TicTacToeLosses.setFillColor(red);
    TicTacToeLosses.setPosition(150+71+26, 150+153+53);

    Lig4Wins.setFont(textFont);
    Lig4Wins.setCharacterSize(16);
    Lig4Wins.setFillColor(green);
    Lig4Wins.setPosition(150+356+9, 150+153+53);

    Lig4Losses.setFont(textFont);
    Lig4Losses.setCharacterSize(16);
    Lig4Losses.setFillColor(red);
    Lig4Losses.setPosition(150+356+26, 150+153+53);

    MineFieldWins.setFont(textFont);
    MineFieldWins.setCharacterSize(16);
    MineFieldWins.setFillColor(green);
    MineFieldWins.setPosition(150+166+9, 150+153+53);

    MineFieldLosses.setFont(textFont);
    MineFieldLosses.setCharacterSize(16);
    MineFieldLosses.setFillColor(red);
    MineFieldLosses.setPosition(150+166+26, 150+153+53);

    ReversiWins.setFont(textFont);
    ReversiWins.setCharacterSize(16);
    ReversiWins.setFillColor(green);
    ReversiWins.setPosition(150+261+9, 150+153+53);

    ReversiLosses.setFont(textFont);
    ReversiLosses.setCharacterSize(16);
    ReversiLosses.setFillColor(red);
    ReversiLosses.setPosition(150+261+26, 150+153+53);



}

void RankingScreen::loadTextures(){
    backButtonTexture.loadFromFile("assets/BackButton.png");
    hoverBackButtonTexture.loadFromFile("assets/BackButtonH.png");

    nextButtonTexture.loadFromFile("assets/Ranking/NextButton.png");
    previousButtonTexture.loadFromFile("assets/Ranking/PreviousButton.png");

    playerCardTexture.loadFromFile("assets/Ranking/PlayerCard.png");
    textFont.loadFromFile("assets/font/Sniglet-Regular.ttf");

    JogadorTexture.loadFromFile("assets/Ranking/Jogador.png");
    mainColor = sf::Color(16, 20, 25);
    green = sf::Color(103, 172, 92);
    red = sf::Color(240, 65, 65);
}

void RankingScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(playerCard);
    window.draw(backButton);
    window.draw(Jogador);
    window.draw(previousButton);
    window.draw(nextButton);
    window.draw(name);
    window.draw(nickname);
    window.draw(position);
    window.draw(TicTacToeWins);
    window.draw(TicTacToeLosses);
    window.draw(Lig4Wins);
    window.draw(Lig4Losses);
    window.draw(MineFieldWins);
    window.draw(MineFieldLosses);
    window.draw(ReversiWins);
    window.draw(ReversiLosses);
    window.display();
}

void RankingScreen::update(sf::RenderWindow &window){
    isMouseOver(backButton.getGlobalBounds(), window) ? backButton.setTexture(hoverBackButtonTexture) : backButton.setTexture(backButtonTexture);
    name.setString(playersList[currentPlayer]->getName());
    nickname.setString(playersList[currentPlayer]->getNickname());
    position.setString(std::to_string(currentPlayer + 1) + "o Lugar");

    TicTacToeWins.setString(std::to_string(playersList[currentPlayer]->getTicTacToeVictories()));
    TicTacToeLosses.setString(std::to_string(playersList[currentPlayer]->getTicTacToeDefeats()));
    Lig4Wins.setString(std::to_string(playersList[currentPlayer]->getLig4Victories()));
    Lig4Losses.setString(std::to_string(playersList[currentPlayer]->getLig4Defeats()));
    MineFieldWins.setString(std::to_string(playersList[currentPlayer]->getMinefieldVictories()));
    MineFieldLosses.setString(std::to_string(playersList[currentPlayer]->getMinefieldDefeats()));
    ReversiWins.setString(std::to_string(playersList[currentPlayer]->getReversiVictories()));
    ReversiLosses.setString(std::to_string(playersList[currentPlayer]->getReversiDefeats()));

}

void RankingScreen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left){
                if(isMouseOver(backButton.getGlobalBounds(), window)){
                    getScreenManager()->change(std::make_shared<MenuScreen>(getScreenManager(), getPlayers()));
                }
                if(isMouseOver(nextButton.getGlobalBounds(), window)){
                    if (currentPlayer < playersList.size() - 1){
                        currentPlayer++;
                    }
                    else{
                        currentPlayer = 0;
                    }
                }
                if(isMouseOver(previousButton.getGlobalBounds(), window)){
                    if(currentPlayer > 0){
                        currentPlayer--;
                    }
                    else{
                        currentPlayer = playersList.size() - 1;
                    }
                }
            }
        }
    }
}