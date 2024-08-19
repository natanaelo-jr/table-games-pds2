#include "GameSelectionScreen.hpp"
#include "MenuScreen.hpp"
#include "TicTacToeScreen.hpp"
#include "Lig4Screen.hpp"
#include "ReversiScreen.hpp"
#include "MineFieldScreen.hpp"
#include <iostream>

GameSelectionScreen::GameSelectionScreen(ScreenManager* screenManager, Players* players) : Screen(players, screenManager){
    loadTextures();
    playerList.push_back(new Player("CPU", "CPU"));
    for(auto player : players->getPlayers()){
        playerList.push_back(player);
    }
    player1Index = 1;
    player2Index = 0;

    SelectedGame = "TicTacToe";

    startButton.setTexture(startButtonTexture);
    startButton.setPosition(250, 105);

    backButton.setTexture(backButtonTexture);
    backButton.setPosition(15, 15);

    ticTacToeButton.setTexture(selectedTicTacToeButtonTexture);
    ticTacToeButton.setPosition(120, 327);

    lig4Button.setTexture(lig4ButtonTexture);
    lig4Button.setPosition(280, 327);

    mineFieldButton.setTexture(mineFieldButtonTexture);
    mineFieldButton.setPosition(600, 327);

    reversiButton.setTexture(reversiButtonTexture);
    reversiButton.setPosition(440, 327);

    selectedGame.setFont(textFont);
    selectedGame.setCharacterSize(48);
    selectedGame.setFillColor(mainColor);
    selectedGame.setOrigin(selectedGame.getLocalBounds().width/2, selectedGame.getLocalBounds().height/2);
    selectedGame.setPosition(293, 218);

    player1.setFont(textFont);
    player1.setCharacterSize(40);
    player1.setFillColor(mainColor);
    player1.setOrigin(player1.getLocalBounds().width/2, player1.getLocalBounds().height/2);
    player1.setPosition(15+67, 466+0);

    player2.setFont(textFont);
    player2.setCharacterSize(40);
    player2.setFillColor(mainColor);
    player2.setOrigin(player2.getLocalBounds().width/2, player2.getLocalBounds().height/2);
    player2.setPosition(486+67, 466+0);

    nextPlayer1.setTexture(nextPlayerTexture);
    nextPlayer1.setPosition(15+298-34, 466+8);

    previousPlayer1.setTexture(previousPlayerTexture);
    previousPlayer1.setPosition(15+0, 466+8);

    nextPlayer2.setTexture(nextPlayerTexture);
    nextPlayer2.setPosition(486+298-34, 466+8);

    previousPlayer2.setTexture(previousPlayerTexture);
    previousPlayer2.setPosition(486+0, 466+8);

    versus.setTexture(versusTexture);
    versus.setPosition(370, 456);

}


void GameSelectionScreen::loadTextures(){
    textFont.loadFromFile("assets/font/Sniglet-Regular.ttf");

    lig4ButtonTexture.loadFromFile("assets/GameSelection/Lig4Button.png");
    selectedLig4ButtonTexture.loadFromFile("assets/GameSelection/Lig4ButtonS.png");

    ticTacToeButtonTexture.loadFromFile("assets/GameSelection/TicTacToeButton.png");
    selectedTicTacToeButtonTexture.loadFromFile("assets/GameSelection/TicTacToeButtonS.png");

    mineFieldButtonTexture.loadFromFile("assets/GameSelection/MineFieldButton.png");
    selectedMineFieldButtonTexture.loadFromFile("assets/GameSelection/MineFieldButtonS.png");

    reversiButtonTexture.loadFromFile("assets/GameSelection/ReversiButton.png");
    selectedReversiButtonTexture.loadFromFile("assets/GameSelection/ReversiButtonS.png");

    startButtonTexture.loadFromFile("assets/GameSelection/StartButton.png");
    hoverStartButtonTexture.loadFromFile("assets/GameSelection/StartButtonH.png");

    nextPlayerTexture.loadFromFile("assets/GameSelection/NextButtonSelect.png");
    previousPlayerTexture.loadFromFile("assets/GameSelection/PreviousButtonSelect.png");

    backButtonTexture.loadFromFile("assets/BackButton.png");
    hoverBackButtonTexture.loadFromFile("assets/BackButtonH.png");

    versusTexture.loadFromFile("assets/GameSelection/VersusImg.png");

    mainColor = sf::Color(16, 20, 25);

}

void GameSelectionScreen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            if(isMouseOver(ticTacToeButton.getGlobalBounds(), window)){
                SelectedGame = "TicTacToe";
            }
            if(isMouseOver(lig4Button.getGlobalBounds(), window)){
                SelectedGame = "Lig4";
            }
            if(isMouseOver(mineFieldButton.getGlobalBounds(), window)){
                SelectedGame = "MineField";
                player2Index = 0;
            }
            if(isMouseOver(reversiButton.getGlobalBounds(), window)){
                SelectedGame = "Reversi";
            }
            if(isMouseOver(startButton.getGlobalBounds(), window)){
                if(selectedGame.getString() == "TicTacToe"){
                    std::cout << playerList[player1Index]->getNickname() << " vs " << playerList[player2Index]->getNickname() << std::endl;
                    getScreenManager()->change(std::make_shared<TicTacToeScreen>(
                        getScreenManager(),
                        playerList[player1Index],
                        playerList[player2Index],
                        getPlayers()
                    ));
                }
                if(selectedGame.getString() == "Reversi"){
                    getScreenManager()->change(std::make_shared<ReversiScreen>(
                        getScreenManager(), 
                        playerList[player1Index],
                        playerList[player2Index],
                        getPlayers()
                    ));

                }
                if(selectedGame.getString() == "Lig4"){
                    getScreenManager()->change(std::make_shared<Lig4Screen>(
                        getScreenManager(), 
                        playerList[player1Index],
                        playerList[player2Index],
                        getPlayers()
                    ));
                }
                if(selectedGame.getString() == "Minefield"){
                    getScreenManager()->change(std::make_shared<MineFieldScreen>(
                        getScreenManager(),
                        playerList[player1Index],
                        getPlayers()
                    ));
                }
            }
            if(isMouseOver(backButton.getGlobalBounds(), window)){
                getScreenManager()->change(std::make_shared<MenuScreen>(getScreenManager(), getPlayers()));
            }
            if(isMouseOver(nextPlayer1.getGlobalBounds(), window)){
                player1Index == playerList.size() - 1 ? player1Index = 1 : player1Index++;
                if(player1Index == player2Index){
                    player1Index == playerList.size() - 1 ? player1Index = 1 : player1Index++;
                }
            }
            if(isMouseOver(previousPlayer1.getGlobalBounds(), window)){
                player1Index == 1 ? player1Index = playerList.size() - 1 : player1Index--;
                if(player1Index == player2Index){
                    player1Index == 1 ? player1Index = playerList.size() - 1 : player1Index--;
                }
            }
            if(isMouseOver(nextPlayer2.getGlobalBounds(), window)){
                if(SelectedGame != "MineField"){
                    player2Index == playerList.size() - 1 ? player2Index = 0 : player2Index++;
                    if(player2Index == player1Index){
                        player2Index == playerList.size() - 1 ? player2Index = 0 : player2Index++;
                    }
                }
            }
            if(isMouseOver(previousPlayer2.getGlobalBounds(), window)){
                    if(SelectedGame != "MineField"){
                    player2Index == 0 ? player2Index = playerList.size() - 1 : player2Index--;
                    if(player2Index == player1Index){
                        player2Index == 0 ? player2Index = playerList.size() - 1 : player2Index--;
                    }
                }
            }
        }
    }
}

void GameSelectionScreen::update(sf::RenderWindow &window){
    updateSelectedGame();
    isMouseOver(startButton.getGlobalBounds(), window) ? 
    startButton.setTexture(hoverStartButtonTexture) : startButton.setTexture(startButtonTexture);

    isMouseOver(backButton.getGlobalBounds(), window) ?
    backButton.setTexture(hoverBackButtonTexture) : backButton.setTexture(backButtonTexture);
    updateTexts();

}

void GameSelectionScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(ticTacToeButton);
    window.draw(lig4Button);
    window.draw(mineFieldButton);
    window.draw(reversiButton);
    window.draw(startButton);
    window.draw(backButton);
    window.draw(selectedGame);
    window.draw(player1);
    window.draw(player2);
    window.draw(nextPlayer1);
    window.draw(previousPlayer1);
    if(SelectedGame != "MineField"){
        window.draw(nextPlayer2);
        window.draw(previousPlayer2);
    }
    window.draw(versus);
    window.display();
}

void GameSelectionScreen::updateSelectedGame(){
    if(SelectedGame == "TicTacToe"){
        ticTacToeButton.setTexture(selectedTicTacToeButtonTexture);
        lig4Button.setTexture(lig4ButtonTexture);
        mineFieldButton.setTexture(mineFieldButtonTexture);
        reversiButton.setTexture(reversiButtonTexture);
    }else if(SelectedGame == "Lig4"){
        ticTacToeButton.setTexture(ticTacToeButtonTexture);
        lig4Button.setTexture(selectedLig4ButtonTexture);
        mineFieldButton.setTexture(mineFieldButtonTexture);
        reversiButton.setTexture(reversiButtonTexture);
    }else if(SelectedGame == "MineField"){
        ticTacToeButton.setTexture(ticTacToeButtonTexture);
        lig4Button.setTexture(lig4ButtonTexture);
        mineFieldButton.setTexture(selectedMineFieldButtonTexture);
        reversiButton.setTexture(reversiButtonTexture);
    }else if(SelectedGame == "Reversi"){
        ticTacToeButton.setTexture(ticTacToeButtonTexture);
        lig4Button.setTexture(lig4ButtonTexture);
        mineFieldButton.setTexture(mineFieldButtonTexture);
        reversiButton.setTexture(selectedReversiButtonTexture);
    }
}

void GameSelectionScreen::updateTexts(){
    player1.setString(playerList[player1Index]->getNickname());
    player2.setString(playerList[player2Index]->getNickname());
    selectedGame.setString(SelectedGame);

    selectedGame.setOrigin(selectedGame.getLocalBounds().width/2, 0);
    selectedGame.setPosition(143+253, 218);

    player1.setOrigin(player1.getLocalBounds().width/2, 0);
    player1.setPosition(15+150, 466);

    player2.setOrigin(player2.getLocalBounds().width/2, 0);
    player2.setPosition(486+150, 466);
}