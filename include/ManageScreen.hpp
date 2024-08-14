#ifndef MANAGESCREEN_HPP
#define MANAGESCREEN_HPP
#include "Screen.hpp"

class ManageScreen : public Screen{
    public: 
        ManageScreen(ScreenManager* screenManager, Players *players);
        void handleEvents(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window) override;
        void render(sf::RenderWindow &window) override;
        void handleTextInput(sf::Event &event);
        void loadTextures() override;
        bool validateNickname();
        bool validateName();
        void setupStrings();
        void updateTexts();

    private:
        sf::RectangleShape nicknameCase;
        sf::RectangleShape nameCase;
        sf::Text nicknameTitle;
        sf::Text nicknameString;
        sf::Text nameTitle;
        sf::Text nameString;
        bool isNickCaseSelected;
        bool isNameCaseSelected;
        bool currentPlayerExists;

        sf::Texture addButtonTexture;
        sf::Texture hoverAddButtonTexture;
        sf::Texture removeButtonTexture;
        sf::Texture hoverRemoveButtonTexture;

        sf::Sprite pushDataButton;

        sf::Texture backButtonTexture;
        sf::Texture hoverBackButtonTexture;
        sf::Sprite backButton;
        sf::Font textFont;
        sf::Color textColor;
};

#endif