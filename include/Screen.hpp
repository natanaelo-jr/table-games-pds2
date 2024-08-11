#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <SFML/Graphics.hpp>
#include "ScreenManager.hpp"
#include <list>
#include "Players.hpp"

class ScreenManager;

class Screen{
    public:
        Screen(Players* players, ScreenManager* screenManager);
        virtual void handleEvents(sf::RenderWindow &window) = 0;
        virtual void update(sf::RenderWindow &window) = 0;
        virtual void render(sf::RenderWindow &window) = 0;
        virtual void loadTextures() = 0;
        void process(sf::RenderWindow &window);
        void setupWindow(sf::RenderWindow &window);
        sf::Color getBackgroundColor();
        bool isMouseOver(sf::Sprite& button, sf::RenderWindow &window);
        Players* getPlayers();
        ScreenManager* getScreenManager();


    private:
        sf::Color backgroundColor;
        sf::Cursor cursor;
        sf::Image cursorImage;
        sf::Image icon;
        Players* players;
        ScreenManager* screenManager;
};

#endif