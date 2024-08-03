#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <SFML/Graphics.hpp>

class Screen{
    public:
        Screen();
        virtual void handleEvents(sf::RenderWindow &window) = 0;
        virtual void update(sf::RenderWindow &window) = 0;
        virtual void render(sf::RenderWindow &window) = 0;
        void process(sf::RenderWindow &window);
        void setupWindow(sf::RenderWindow &window);
        sf::Color getBackgroundColor();

    private:
        sf::Color backgroundColor;
        sf::Cursor cursor;
        sf::Image cursorImage;
        sf::Image icon;
};

#endif