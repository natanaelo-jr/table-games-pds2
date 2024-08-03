#include <iostream>
#include <string>
#include <set>
#include "Player.hpp"
#include "Players.hpp"
#include "TicTacToe.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Menu.hpp"
#include <sstream>

void printInstructions(){
    std::cout << "LISTA DE COMANDOS:" << std::endl;
    std::cout << "Cadastro de Jogador: CJ <nome> <apelido>" << std::endl;
    std::cout << "Remoção de Jogador: RJ <apelido>" << std::endl;
    std::cout << "Listagem de Jogadores: LJ" << std::endl;
    std::cout << "Executar Jogo: EJ <apelido1> <apelido2>" << std::endl;
    std::cout << "Finalizar Programa: FIM" << std::endl << std::endl;
}

void cleanTerminal(){
    system("clear || cls");
}

void run(Players players){
    std::string comando;
    while(std::cin >> comando){
        if(comando == "CJ"){ //cadastro de jogadores
            std::string name, nickname;
            std::cin >> name >> nickname;
            players.signUpPlayer(name, nickname);
        }

        if(comando == "RJ"){ //remoção de jogadores
            std::string nickname;
            std::cin >> nickname;
            players.deletePlayer(nickname);
        }

        if(comando == "LJ"){ //listagem de jogadores
            players.displayPlayers();
        }

        if(comando == "EJ"){ //executar jogo
            char playagain;
            if(players.getsize() > 1){ //tratamento de possivel segmentation fault
                std::string nickname1, nickname2;
                std::cin >> nickname1 >> nickname2;
                Player* player1 = players.searchByNickname(nickname1);
                Player* player2 = players.searchByNickname(nickname2);
                Game* game = new TicTacToe(player1, player2);
                game->play();
                delete game;
                while (true){
                    std::cout << "Deseja jogar novamente? (S/N)" << std::endl;
                    std::cin >> playagain;
                    if(playagain == 'S'){
                        game = new TicTacToe(player1, player2);
                        game->play();
                        delete game;
                    }
                    else{ //todo: adicionar mensagem e printar os comandos básicos
                        break;
                    }
                }
            }
            else if (players.getsize() == 1){
                std::cout << "Apenas um jogador cadastrado. Cadastre outro para jogar!" << std::endl;
            }   
            else{
                std::cout << "Nenhum jogador cadastrado. Cadastre jogadores para jogar!" << std::endl;
            }
        }

        if(comando == "FIM"){ //finalizar programa
            break;
        }
    }
}