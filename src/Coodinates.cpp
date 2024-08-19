#include "Coordinates.hpp"

/**
 * @file Coordinates.cpp
 * @brief Implementação da classe Coordinates.
 */

/**
 * @brief Construtor padrão da classe Coordinates
 * 
 */
Coordinates::Coordinates() : Coordinates(0, 0){}

/**
 * @brief Construtor da classe Coordinates inicia a posição com o mesmo valor de linha e coluna
 * 
 * @param coord posição da peça
 * 
 */
Coordinates::Coordinates(int coord) : Coordinates(coord, coord){}

/**
 * @brief Construtor da classe Coordinates inicia a posição com valores diferentes de linha e coluna
 * 
 * @param row posição da linha
 * @param col posição da coluna
 * 
 */
Coordinates::Coordinates(int row, int col){
    this->row = row;
    this->col = col;
}

/**
 * @brief Métodos getters para linha e coluna
 * 
 * @return O valor da linha e da coluna
 * 
 */
int Coordinates::getRow(){
    return row;
}
int Coordinates::getCol(){
    return col;
}

/**
 * @brief Métodos setters para linha e coluna
 * 
 * @param row valor a ser atribuído à linha
 * @param col valor a ser atribuído à coluna
 * 
 */
void Coordinates::setRow(int row){
    this->row = row;
}
void Coordinates::setCol(int col){
    this->col = col;
}

bool Coordinates::operator<(const Coordinates& c) const{
    if (row == c.row){
        return col < c.col;
    } else {
        return row < c.row;    
    }
    return true;
}

bool Coordinates::operator==(const Coordinates& c) const{
    return row == c.row && col == c.col;
}
