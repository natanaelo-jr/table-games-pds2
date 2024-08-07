#ifndef COORDINATES_HPP
#define COORDINATES_HPP
#include <functional>
#include <cstddef>

class Coordinates {
    public:
        int row;
        int col;
        Coordinates();
        Coordinates(int coord);
        Coordinates(int row, int col);
        int getRow();
        int getCol();
        void setRow(int row);
        void setCol(int col);
        bool operator<(const Coordinates& c) const;
        bool operator==(const Coordinates& c) const;
};




#endif