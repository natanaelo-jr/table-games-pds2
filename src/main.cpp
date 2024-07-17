#include <iostream>
#include <string>
#include "Player.hpp"
#include "Players.hpp"
#include "TicTacToe.hpp"

int main(){
    
    std::string comando;
    Players players;

    //instruções de execução
    std::cout << "TRABALHO DOS JOGOS" << std::endl << std::endl << std::endl;
    std::cout << "LISTA DE COMANDOS:" << std::endl;
    std::cout << "Cadastro de Jogador: CJ <nome> <apelido>" << std::endl;
    std::cout << "Remoção de Jogador: RJ <apelido>" << std::endl;
    std::cout << "Listagem de Jogadores: LJ" << std::endl;
    std::cout << "Executar Jogo: EJ <apelido1> <apelido2>" << std::endl;
    std::cout << "Finalizar Programa: FIM" << std::endl << std::endl;

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
            std::string nickname1, nickname2;
            std::cin >> nickname1 >> nickname2;
            Player* player1 = players.searchByNickname(nickname1);
            Player* player2 = players.searchByNickname(nickname2);
            TicTacToe game(player1, player2);
            game.play();
        }

        if(comando == "FIM"){ //finalizar programa
            break;
        }
    }

    return 0;
}
