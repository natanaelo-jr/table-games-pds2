#ifndef MENU_HPP
#define MENU_HPP
#include "Screen.hpp"

class MenuScreen : public Screen{
    public:
        MenuScreen(ScreenManager* screenManager, Players* players);
        void handleEvents(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window) override;
        void render(sf::RenderWindow &window) override;
        void loadTextures();
    
    private:
        sf::Texture playButtonTexture;
        sf::Texture hoverPlayButtonTexture;
        sf::Texture manageButtonTexture;
        sf::Texture hoverManageButtonTexture;
        sf::Texture rankingButtonTexture;
        sf::Texture hoverRankingButtonTexture;
        sf::Texture creditsButtonTexture;
        sf::Texture hoverCreditsButtonTexture;
        sf::Texture exitButtonTexture;
        sf::Texture hoverExitButtonTexture;

        sf::Sprite playButton; 
        sf::Sprite rankingButton; 
        sf::Sprite creditsButton;
        sf::Sprite manageButton;
        sf::Sprite exitButton;
        };

#endif