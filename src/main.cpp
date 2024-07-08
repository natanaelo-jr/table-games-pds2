#include <iostream>
#include <string>
#include "Player.hpp"
#include "Game.hpp"
#include "Players.hpp"
#include "TicTacToe.hpp"

int main() {
    Players players;
    std::string command;
    std::cin >> command;

    while (command != "FS") {
        if (command == "CJ") {
            std::string nome;
            std::string apelido;
            std::cin >> nome >> apelido;
            players.signUpPlayer(nome, apelido); 
        }
        std::cin >> command;
    }

    return 0;
}
