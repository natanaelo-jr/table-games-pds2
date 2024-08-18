#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP
#include <stack>
#include <memory>
#include "Screen.hpp"

class Screen;

class ScreenManager{
    public:
        void push(std::shared_ptr<Screen> state);
        void pop();
        void change(std::shared_ptr<Screen> state);
        std::shared_ptr<Screen> getCurrentState();
        void process(sf::RenderWindow &window);
        void setupWindow(sf::RenderWindow &window);

    private:
        std::stack<std::shared_ptr<Screen>> states;
};
#endif