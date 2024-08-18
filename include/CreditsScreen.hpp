#ifndef CREDITSSCREEN_HPP
#define CREDITSSCREEN_HPP
#include "Screen.hpp"

class CreditsScreen : public Screen{
    public:
        CreditsScreen(ScreenManager* screenManager, Players* players);
        void render(sf::RenderWindow &window) override;
        void handleEvents(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window) override;
        void loadTextures() override;
        void generateBaloes();

    private:
        sf::Clock clock;
        const float frameTime = 1.0f / 60.0f;
        sf::Texture colaboradoresTexture;
        sf::Sprite colaboradoresSprite;

        sf::Texture backButtonTexture;
        sf::Texture hoverBackButtonTexture;
        sf::Sprite backButton;

        sf::Texture balaoTexture;
        std::vector<sf::Sprite> baloes;

};

#endif