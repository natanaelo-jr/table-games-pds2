#include "ScreenManager.hpp"
#include "Screen.hpp"

void ScreenManager::push(std::shared_ptr<Screen> state){
    states.push(state);
}

void ScreenManager::pop(){
    states.pop();
}

void ScreenManager::change(std::shared_ptr<Screen> state){
    states.pop();
    states.push(state);
}

void ScreenManager::process(sf::RenderWindow &window){
    states.top()->process(window);
}

void ScreenManager::setupWindow(sf::RenderWindow &window){
    states.top()->setupWindow(window);
}

std::shared_ptr<Screen> ScreenManager::getCurrentState(){
    if(!states.empty()){
        return states.top();
    }
    return nullptr;
}