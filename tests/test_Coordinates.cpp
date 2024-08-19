#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Coordinates.hpp"
#include "doctest.h"

TEST_CASE("Testando a classe Coordinates"){
    Coordinates* coord = new Coordinates(1, 2);
    CHECK(coord->getRow() == 1);
    CHECK(coord->getCol() == 2);
    coord->setRow(3);
    CHECK(coord->getRow() == 3);
    coord->setCol(4);
    CHECK(coord->getCol() == 4);
    delete coord;
}