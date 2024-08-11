#include "Coordinates.hpp"

Coordinates::Coordinates() : Coordinates(0, 0){}

Coordinates::Coordinates(int coord) : Coordinates(coord, coord){}

Coordinates::Coordinates(int row, int col){
    this->row = row;
    this->col = col;
}

int Coordinates::getRow(){
    return row;
}

int Coordinates::getCol(){
    return col;
}

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
