#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

/**
 * @brief Class Player
 * 
 * A classe Player é responsável por gerenciar os cada um dos jogadores armazenados.
 */

class Player{
    private:
        std::string name; /** <nome do jogador */
        std::string nickname; /** <apelido do jogador que aparece ao jogar */
        int tictactoeVictories; /** <núm. de vitórias em TicTacToe */
        int tictactoeDefeats; /** <núm. de derrotas em TicTacToe */
        int lig4Victories; /** <núm. de vitórias em lig4 */
        int lig4Defeats; /** <núm. de derrotas em lig4 */
        int reversiVictories; /** <núm. de vitórias em Reversi */
        int reversiDefeats; /** <núm. de derrotas em Reversi */
        int minefieldVictories; /** <núm. de vitórias em Minefield */
        int minefieldDefeats; /** <núm. de derrotas em MineField */

    public:
        /** 
         * @brief Construtor padrão da classe Player
         */
        Player();
        /**
         * @brief Construtor da classe Player
         * 
         * @param name nome do jogador
         * @param nickname apelido do jogador
         */
        Player(std::string name, std::string nickname);
        /**
         * @brief Métodos getters para os atributos da classe Player
         * 
         * Esses métodos retornam o nome e apelido do jogador da classe Player. 
         * 
         * @return O valor do atributo correspondente
         */
        std::string getName() const;
        std::string getNickname() const;

        /**
         * @brief Métodos getters para vitórias e derrotas da classe Player
         * 
         * Esses métodos retornam o número de vitórias e derrotas do jogador da classe Player. 
         * usados para ordenar os jogadores no ranking
         * 
         * @return O valor do atributo correspondente
         */
        int getVictories() const;
        int getDefeats() const;
        /**
         * @brief Métodos setters para nome e apelido da classe Player
         */
        void setName(std::string name);
        void setNickname(std::string nickname);

        /** 
         * @brief Métodos para getters vitórias e derrotas de cada jogo específico
         */
        void winTicTacToe();
        void loseTicTacToe();
        void winLig4();
        void loseLig4();
        void winReversi();
        void loseReversi();
        void winMinefield();
        void loseMinefield();

        /** 
         * @brief Métodos para getters vitórias e derrotas de cada jogo específico
         */
        int getTicTacToeVictories() const;
        int getTicTacToeDefeats() const;
        int getLig4Victories() const;
        int getLig4Defeats() const;
        int getReversiVictories() const;
        int getReversiDefeats() const;
        int getMinefieldVictories() const;
        int getMinefieldDefeats() const;
};

#endif