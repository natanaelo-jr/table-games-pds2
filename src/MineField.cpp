#include "MineField.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <set>

MineField::MineField(Player* player) : MineField(player, 9, 10){}

MineField::MineField(Player* player, int fieldSize, int bombs) : MineField(player, nullptr, fieldSize, bombs){}

MineField::MineField(Player* player1, Player* player2) : MineField(player1, player2, 9, 10){}

MineField::MineField(Player* player1, Player* player2, int fieldSize, int bombs): Game(player1, player2, fieldSize, fieldSize){
    if(fieldSize <= 5){
        throw std::invalid_argument("Tamanho do campo inválido.");
    }
    if(bombs < 1 || (fieldSize*fieldSize)/bombs < 5){
        throw std::invalid_argument("Número de bombas inválido.");
    }
    if(player2 == nullptr){
        if(getPlayer1()->getName() == "CPU"){
            throw std::invalid_argument("CPU não pode jogar campo minado");
        }
    }
    else{
        if(getPlayer1()->getName() == "CPU" || getPlayer2()->getName() == "CPU"){
            throw std::invalid_argument("CPU não pode jogar campo minado");
        }
    }


    player2 == nullptr ? versusGame = false : versusGame = true;
    this->fieldSize = fieldSize;
    this->numberOfBombs = bombs;
    for(int i = 0; i < fieldSize; i++){
        referenceField = std::vector<std::vector<int>>(fieldSize, std::vector<int>(fieldSize, 0));
    }
}

int MineField::getFieldSize(){
    return fieldSize;
}

void MineField::setReferenceField(Coordinates firstPlay){
    std::set<Coordinates> invalidHouses;

    for(int i : {-1, 0, 1}){
        for(int j : {-1, 0, 1}){
            Coordinates c = {firstPlay.row + i, firstPlay.col + j};
            if(isValidSquare(c)){
                invalidHouses.insert(c);
            }
        }
    }
    std::vector<Coordinates> mines;

    for(int i = 0; i < getFieldSize(); i++){
        for(int j = 0; j < getFieldSize(); j++){
            mines.push_back(Coordinates(i, j));
        }
    }
    
    std::default_random_engine generator(std::time(0));
    std::shuffle(mines.begin(), mines.end(), generator);

    int count = 0;
    for(Coordinates c : mines){
        if(invalidHouses.find(c) == invalidHouses.end()){
            referenceField[c.row][c.col] = 9;
            count++;
        }
        if(count == getNumberOfBombs()){
            break;
        }
    }

    for(int i = 0; i < getFieldSize(); i++){
        for(int j = 0; j < getFieldSize(); j++){
            if(referenceField[i][j] != 9){
                int count = 0;
                for(int x : {-1, 0, 1}){
                    for(int y : {-1, 0, 1}){
                        if(i + x >= 0 && i + x < getFieldSize() && j + y >= 0 && j + y < getFieldSize()){
                            if(referenceField[i + x][j + y] == 9){
                                count++;
                            }
                        }
                    }
                }
                referenceField[i][j] = count;
            }
        }
    }
}

int MineField::getReference(Coordinates reference){
    if(isValidSquare(reference)){
        return referenceField[reference.row][reference.col];
    }
    throw std::invalid_argument("Coordenadas inválidas");
}

int MineField::getNumberOfBombs(){
    return numberOfBombs;
}

void MineField::recursiveOpen(Coordinates reference){
    if(!isValidSquare(reference)){
        return;
    }
    if(getReference(reference) == 9){
        return;
    }
    if(getReference(reference) != 0){
        setSquare(reference, getReference(reference) + '0');
        return;
    }
    if(getSquare(reference, getBoard()) != ' '){
        return;
    }

    setSquare(reference, getReference(reference) + '0');

    for(int i : {-1, 0 ,1}){
        for(int j : {-1, 0, 1}){           
            recursiveOpen({reference.getRow()+i, reference.getCol()+j});  
        }
    }
}

void MineField::play(){
    int row, col;
    bool p1win = false;
    bool p2win = false;
    if(isVersusGame()){
        std::cout << "Esta é uma partida versus de campo minado." << std::endl;
        std::cout << getPlayer1()->getNickname() << " vs " << getPlayer2()->getNickname() << std::endl;
    }else{
        std::cout << "Esta é uma partida single player de campo minado." << std::endl;
        std::cout << getPlayer1()->getNickname() << " jogando." << std::endl;
    }
    for(int player : {1, 2}){
        if(player == 2 && !isVersusGame()){
            break;
        }

        if(isVersusGame()){
            player == 2 ? changePlayer() : void();
            std::cout << "Vez do jogador " << getCurrentPlayer()->getNickname() << std::endl;
        }

        printBoard();
        std::cout << "Faça a jogada inicial: " << std::endl;
        std::cin >> row >> col;
        setReferenceField({row-1, col-1});
        makePlay({row, col});

        while(true){
            printBoard();
            Coordinates move;
            std::cout << "Digite a linha e a coluna da jogada: " << std::endl;
            std::cin >> row >> col;
            move = {row, col};
            try{
                if(!makePlay(move)){
                    std::cout << getCurrentPlayer()->getNickname() <<" perdeu!" << std::endl;
                    break;
                }
                if(isGameOver()){
                    player == 1 ? p1win = true : p1win = false;
                    player == 2 ? p2win = true : p2win = false;
                    std::cout << getCurrentPlayer()->getNickname() << " ganhou!" << std::endl;
                    break;
                }         
            }catch(const std::exception& e){
                std::cout << e.what() << std::endl;
            }
        }
    }

    if(!isVersusGame()){
        //todo addstatus p1
        p1win ? void() : void();
    }else{
        if(p1win == p2win){
            std::cout << "Empate!" << std::endl;
            //todo addstatus
        }else{
            std::cout << "Vitória de " << (p1win ? getPlayer1()->getNickname() : getPlayer2()->getNickname()) << std::endl;
            //todo addstatus
        }
    }
}

bool MineField::makePlay(Coordinates move){
    move.setRow(move.getRow() - 1);
    move.setCol(move.getCol() - 1);

    if(!isValidSquare(move)){
        throw std::invalid_argument("Coordenadas inválidas na jogada do campo minado.");
    }
    if(getSquare(move, getBoard()) != ' '){
        throw std::invalid_argument("Casa já aberta.");
    }
    if(getReference(move) == 9){
        return false;
    }
    recursiveOpen(move);
    return true;
}

bool MineField::isVersusGame(){
    return versusGame;
}

bool MineField::isGameOver(){
    int counter = 0;
    for(int i = 0; i < getFieldSize(); i++){
        for(int j = 0; j < getFieldSize(); j++){
            if(getSquare({i, j}, getBoard()) == ' '){
                counter++;
            }
        }
    }
    if(counter == getNumberOfBombs()){
        return true;
    }
    return false;
}

void MineField::resetGame(){
    for(int i = 0; i < getFieldSize(); i++){
        for(int j = 0; j < getFieldSize(); j++){
            setSquare({i, j}, ' ');
        }
    }
    for(int i = 0; i < getFieldSize(); i++){
        for(int j = 0; j < getFieldSize(); j++){
            referenceField[i][j] = 0;
        }
    }
}