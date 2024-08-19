#ifndef COORDINATES_HPP
#define COORDINATES_HPP
#include <functional>
#include <cstddef>

/** 
* @brief Class Coordinates
*
* A classe Coordinates cuida de gerenciar as posições de peças e jogadas
*/

class Coordinates {
    public:
        int row; /** <posição da linha */
        int col; /** <posição da coluna */

        /** 
         * @brief Construtor padrão da classe Coordinates
         */
        Coordinates(); 
        /** 
         * @brief Construtor da classe Coordinates
         * 
         * @param coord posição da peça
         */
        Coordinates(int coord);
        /** 
         * @brief Construtor da classe Coordinates
         * 
         * @param row posição da linha
         * @param col posição da coluna
         */
        Coordinates(int row, int col);
         /**
         * @brief Métodos getters para os atributos da classe Coordinates
         * 
         * Esses métodos retornam o valor dos atributos da classe Coordinates. 
         * 
         * @return O valor do atributo correspondente
         */
        int getRow();
        int getCol();
        /**
         * @brief Métodos setters para os atributos da classe Coordinates
         * 
         * Esses métodos atribuem um valor para os atributos da classe Coordinates. 
         * 
         * @param row valor a ser atribuído à linha
         * @param col valor a ser atribuído à coluna
         */
        void setRow(int row);
        void setCol(int col);

        /**
         * @brief compara se as coordenadas são iguais ou nn para ordenar no set
         * 
         * @param c coordenadas a serem comparadas
         */
        bool operator<(const Coordinates& c) const;
        bool operator==(const Coordinates& c) const;
};




#endif