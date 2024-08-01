#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <SFML/Graphics.hpp>

class Screen{
    public:
        virtual void handleEvents(sf::RenderWindow &window) = 0;
        virtual void update(sf::RenderWindow &window) = 0;
        virtual void render(sf::RenderWindow &window) = 0;
        //colocar private e fazer um construtor padrão da screen
        sf::Color backgroundColor = sf::Color(181, 145, 148);
        sf::Cursor cursor;
        sf::Image cursorImage;
};

#endif