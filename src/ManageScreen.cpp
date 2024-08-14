#include "ManageScreen.hpp"
#include "MenuScreen.hpp"

ManageScreen::ManageScreen(ScreenManager* screenManager, Players *players) : Screen(players, screenManager){ 
    loadTextures();
    textFont.loadFromFile("assets/font/Sniglet-Regular.ttf");

    textColor = sf::Color::Black;

    isNickCaseSelected = false;
    isNameCaseSelected = false;
    currentPlayerExists = false;

    pushDataButton.setTexture(addButtonTexture);
    pushDataButton.setPosition(296, 374);
    backButton.setTexture(backButtonTexture);
    backButton.setPosition(15, 15);

    setupStrings();
}

void ManageScreen::loadTextures(){
    addButtonTexture.loadFromFile("assets/Manage/AddButton.png");
    hoverAddButtonTexture.loadFromFile("assets/Manage/AddButtonH.png");
    removeButtonTexture.loadFromFile("assets/Manage/RemoveButton.png");
    hoverRemoveButtonTexture.loadFromFile("assets/Manage/RemoveButtonH.png");
    backButtonTexture.loadFromFile("assets/BackButton.png");
    hoverBackButtonTexture.loadFromFile("assets/BackButtonH.png");
}

void ManageScreen::setupStrings(){
    nicknameTitle.setFont(textFont);
    nicknameTitle.setFillColor(textColor);
    nicknameTitle.setString("Apelido");
    nicknameTitle.setCharacterSize(20);
    nicknameTitle.setPosition(366, 125);

    nameTitle.setFont(textFont);
    nameTitle.setFillColor(textColor);
    nameTitle.setString("Nome");
    nameTitle.setCharacterSize(20);
    nameTitle.setPosition(373, 245);

    nicknameCase.setSize(sf::Vector2f(220, 60));
    nicknameCase.setFillColor(sf::Color(217, 217, 217));
    nicknameCase.setOutlineColor(textColor);
    nicknameCase.setPosition(286, 150);

    nameCase.setSize(sf::Vector2f(220, 60));
    nameCase.setFillColor(sf::Color(217, 217, 217));
    nameCase.setOutlineColor(textColor);
    nameCase.setPosition(286, 270);

    nameString.setFont(textFont);
    nameString.setCharacterSize(32);
    nameString.setFillColor(textColor);
    nicknameString.setFont(textFont);
    nicknameString.setCharacterSize(32);
    nicknameString.setFillColor(textColor);
}

void ManageScreen::render(sf::RenderWindow &window){
    window.clear(getBackgroundColor());
    window.draw(backButton);
    window.draw(nicknameCase);
    window.draw(nameCase);
    window.draw(nicknameTitle);
    window.draw(nameTitle);
    window.draw(nicknameString);
    window.draw(nameString);
    window.draw(pushDataButton);
    window.display();
    
}

void ManageScreen::update(sf::RenderWindow &window){
    isMouseOver(backButton.getGlobalBounds(), window) ? backButton.setTexture(hoverBackButtonTexture) : backButton.setTexture(backButtonTexture);
    isNameCaseSelected ? nameCase.setOutlineThickness(1) : nameCase.setOutlineThickness(0);
    isNickCaseSelected ? nicknameCase.setOutlineThickness(1) : nicknameCase.setOutlineThickness(0);
    updateTexts();
    if(currentPlayerExists){
        isMouseOver(pushDataButton.getGlobalBounds(), window) ? pushDataButton.setTexture(hoverRemoveButtonTexture) : pushDataButton.setTexture(removeButtonTexture);
    }
    else{
        if(validateName() && validateNickname()){
            isMouseOver(pushDataButton.getGlobalBounds(), window) ? pushDataButton.setTexture(hoverAddButtonTexture) : pushDataButton.setTexture(addButtonTexture);
        }else{
            pushDataButton.setTexture(addButtonTexture);
        }
    }
}

void ManageScreen::handleEvents(sf::RenderWindow &window){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            if(isMouseOver(backButton.getGlobalBounds(), window)){
                getScreenManager()->change(std::make_shared<MenuScreen>(getScreenManager(), getPlayers()));
            }

            if(isMouseOver(pushDataButton.getGlobalBounds(), window)){
                if(!currentPlayerExists && validateName() && validateNickname()){
                    getPlayers()->signUpPlayer(nameString.getString(), nicknameString.getString());
                    currentPlayerExists = false;
                    nicknameString.setString("");
                    nameString.setString("");
                }else
                if(currentPlayerExists && validateNickname()){
                    getPlayers()->deletePlayer(nicknameString.getString());
                    currentPlayerExists = false;
                    nicknameString.setString("");
                    nameString.setString("");
                }

            }

            isMouseOver(nameCase.getGlobalBounds(), window) ? isNameCaseSelected = true : isNameCaseSelected = false;
            isMouseOver(nicknameCase.getGlobalBounds(), window) ? isNickCaseSelected = true : isNickCaseSelected = false;

        }
        handleTextInput(event);
    }
}

void ManageScreen::handleTextInput(sf::Event &event){
    if(event.type == sf::Event::TextEntered){
        if(isNickCaseSelected){
            if(event.text.unicode == '\b'){
                if(!nicknameString.getString().isEmpty()){
                    std::string str = nicknameString.getString();
                    str.pop_back();
                    nicknameString.setString(str);

                }
            }else
            if(nicknameString.getString().getSize() <= 10 && event.text.unicode < 128  && event.text.unicode != 13){
                nicknameString.setString(nicknameString.getString() + static_cast<char>(event.text.unicode));
            }

            if(getPlayers()->searchByNickname(nicknameString.getString()) == nullptr){
                currentPlayerExists = false;
            }else{
                currentPlayerExists = true;
            }
        }
        if(isNameCaseSelected){
            if(event.text.unicode == '\b'){
                if(!nameString.getString().isEmpty()){
                    std::string str = nameString.getString();
                    str.pop_back();
                    nameString.setString(str);
                }
            }else
            if(nameString.getString().getSize() <= 10 && event.text.unicode < 128 && event.text.unicode != 13){
                nameString.setString(nameString.getString() + static_cast<char>(event.text.unicode));
            }
        }
    }
}

bool ManageScreen::validateNickname(){
    return nicknameString.getString().getSize() > 0 && nicknameString.getString().getSize() <= 10;
}

bool ManageScreen::validateName(){
    return nameString.getString().getSize() > 0 && nameString.getString().getSize() <= 10;
}

void ManageScreen::updateTexts(){
    nicknameString.setOrigin(nicknameString.getLocalBounds().width/2, 0);
    nicknameString.setPosition(316+(167/2), 160);
    nameString.setOrigin(nameString.getLocalBounds().width/2, 0);
    nameString.setPosition(316+(167/2), 280);
}