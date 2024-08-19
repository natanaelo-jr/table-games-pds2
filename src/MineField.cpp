#include "MineField.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <set>

/**
 * @brief Construtor da classe MineField
 * 
 * Inicializa um jogo de campo minado com um jogador e o tamanho do tabuleiro e número de bombas padrão.
 */
MineField::MineField(Player* player) : MineField(player, 9, 10){}

/**
 * @brief Construtor da classe MineField
 * 
 * Inicializa um jogo de campo minado com um jogador e o tamanho do tabuleiro e número de bombas pré-definido.
 */
MineField::MineField(Player* player, int fieldSize, int bombs) : MineField(player, nullptr, fieldSize, bombs){}

/**
 * @brief Construtor da classe MineField
 * 
 * Inicializa um jogo de campo minado com dois jogadores e o tamanho do tabuleiro e número de bombas padrão.
 */
MineField::MineField(Player* player1, Player* player2) : MineField(player1, player2, 9, 10){}

/**
 * @brief Construtor da classe MineField
 * 
 * Inicializa um jogo de campo minado com dois jogadores e o tamanho do tabuleiro e número de bombas pré-definido.
 * Se o tamanho do lado do tabuleiro for menor ou igual a 5, ou o número de bombas for menor que 1 ou o número de bombas for maior que o número de casas do tabuleiro dividido por 5, uma exceção é lançada.
 * Se um dos jogadores for a CPU, uma exceção é lançada.
 */
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

/**
 * @brief Retorna o tamanho do campo minado.
 * 
 * @return Tamanho do campo minado.
 */
int MineField::getFieldSize(){
    return fieldSize;
}

/**
 * @brief Define o campo de referência do campo minado.
 * 
 * @param firstPlay Coordenadas da primeira jogada.
 */
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

    /**
     * @brief Embaralha as coordenadas das minas.
     */
    std::shuffle(mines.begin(), mines.end(), generator);

    /**
     * @brief Coloca as minas no campo minado.
     * 
     * Se a casa for inválida, ela não recebe uma mina.
     * Se o número de minas for igual ao número de bombas, o loop é interrompido.
     */
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

    /**
     * @brief Conta o número de minas ao redor de cada casa.
     */
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

/**
 * @brief Retorna o valor de uma casa do campo minado.
 * 
 * @param reference Coordenadas da casa de referência.
 * @return Valor da casa.
 */
int MineField::getReference(Coordinates reference){
    if(isValidSquare(reference)){
        return referenceField[reference.row][reference.col];
    }
    throw std::invalid_argument("Coordenadas inválidas");
}

/**
 * @brief Retorna o número de bombas do campo minado.
 * 
 * @return Número de bombas.
 */
int MineField::getNumberOfBombs(){
    return numberOfBombs;
}

/**
 * @brief Abertura recursiva de casas do campo minado.
 * 
 * @param reference Coordenadas da casa de referência.
 */
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

/**
 * @brief Inicia o jogo de campo minado.
 * 
 * Se for um jogo versus, imprime os jogadores.
 * Se for um jogo single player, imprime o jogador.
 * 
 * Faz a jogada inicial e, enquanto o jogo não acabar, pede as coordenadas da jogada e faz a jogada.
 * Se a jogada for inválida, uma exceção é lançada.
 * Se a casa já estiver aberta, uma exceção é lançada.
 * Se a casa tiver uma mina, o jogador perde.
 * Se o jogo acabar, o jogador que ganhou é impresso.
 */
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
                    getCurrentPlayer()->loseMinefield();
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
            p1win ? getPlayer1()->winMinefield() : getPlayer2()->winMinefield(); //NATAAAAAAAAAAAAAAAn
        }
    }
}

/**
 * @brief Faz a jogada no campo minado.
 * 
 * @param move Coordenadas da jogada.
 * @return true se a jogada for válida, false caso contrário.
 */
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

/**
 * @brief Verifica se o jogo é versus.
 * 
 * @return true se o jogo é versus, false caso contrário.
 */
bool MineField::isVersusGame(){
    return versusGame;
}

/**
 * @brief Verifica se o jogo acabou.
 * 
 * @return true se o jogo acabou, false caso contrário.
 */
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

/**
 * @brief Reseta o jogo de campo minado.
 */
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