#include "Reversi.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <iterator>

/**
 * @brief Construtor da classe Reversi. Inicializa o tabuleiro do jogo.
 * 
 * @param player1 Primeiro jogador.
 * @param player2 Segundo jogador.
 */
Reversi::Reversi(Player* player1, Player* player2) : Game(player1, player2, 8, 8) {
    initializeBoard();
}

/**
 * @brief Inicializa o tabuleiro do jogo Reversi, colocando as peças iniciais.
 */
void Reversi::initializeBoard() {
    setSquare({4, 3}, 'O');
    setSquare({3, 3}, 'X');
    setSquare({3, 4}, 'O');
    setSquare({4, 4}, 'X');
}

/**
 * @brief Realiza uma jogada no tabuleiro.
 * 
 * @param row Linha da jogada.
 * @param col Coluna da jogada.
 * @return true Se a jogada foi realizada com sucesso.
 * @return false Se a jogada foi inválida.
 */
bool Reversi::makePlay(int row, int col) {
    char symbol;
    getCurrentPlayer() == getPlayer1() ? symbol = 'X' : symbol = 'O';

    // Verifica se a jogada é válida
    if (!verifyPlay(row, col, symbol))
        return false;

    // Coloca a peça no tabuleiro
    setSquare({row, col}, symbol);

    // Direções para verificar as peças adjacentes
    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
    
    // Percorre todas as direções e tenta virar as peças do oponente
    for (int i = 0; i < 8; i++) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];
        turnPieces(row + dRow, dRow, col + dCol, dCol, symbol, true, getBoard());
    }

    /*if (turnPieces(row + dRow, dRow, col + dCol, dCol, symbol, true, getBoard())) { //false
            int flipRow = row + dRow;
            int flipCol = col + dCol;
            while (getSquare({flipRow, flipCol}, getBoard()) != symbol && getSquare({flipRow, flipCol}, getBoard()) != ' ') {
                setSquare({flipRow, flipCol}, symbol);
                flipRow += dRow;
                flipCol += dCol;
            }
        }*/
    return true;
}

/**
 * @brief Função principal que executa o ciclo do jogo.
 */
void Reversi::play() {
    int row; 
    int col;
    Player* winner = nullptr;
    printBoard(); // Imprime o tabuleiro no início do jogo
    while(true){
        char symbol;
        getCurrentPlayer() == getPlayer1() ? symbol = 'X' : symbol = 'O';
        std::cout << "Vez de " << getCurrentPlayer()->getNickname() << std::endl;

        // Verifica se o jogador tem jogadas válidas
        if(getPossiblePlays(symbol, getBoard()).empty()){
            std::cout << getCurrentPlayer()->getNickname() << " não possui jogadas" << std::endl;
            changePlayer();
        }

        // Exibe as jogadas possíveis e solicita ao jogador que faça uma jogada
        std::cout << "Digite a linha e a coluna da sua jogada: " << std::endl;
        if(getCurrentPlayer() == getPlayer1()){
            std::cout << "Jogadas Possíveis: " << std::endl;
            for(auto play : getPossiblePlays('X', getBoard())){
                std::cout << play.getRow() << " " << play.getCol() << std::endl;
            }
        } else {
            std::cout << "Jogadas Possíveis: " << std::endl;
            for(auto play : getPossiblePlays('O', getBoard())){
                std::cout << play.getRow() << " " << play.getCol() << std::endl;
            }
        }

        std::cin >> row >> col;

        //  Realiza a jogada e verifica se o jogo chegou ao estado terminal
        if(makePlay(row, col)){
            winner = checkWinner();
            if(terminalState(getBoard()) && winner != nullptr){
                printBoard();
                addStats(winner, getWaitingPlayer());
                break;
            } else {
                changePlayer();
                printBoard();
            }
        } else {
            printBoard();
        }
    }
}

/**
 * @brief Busca por jogadas válidas em uma direção específica.
 * 
 * @param row Linha da jogada.
 * @param col Coluna da jogada.
 * @param dRow Direção da linha.
 * @param dCol Direção da coluna.
 * @param symbol Símbolo do jogador atual.
 * @param opposite Símbolo do oponente.
 * @param passedOpponent Indica se a busca já passou por uma peça do oponente.
 * @param board Tabuleiro atual.
 * @return Coordinates Coordenadas da jogada válida ou {-1, -1} se não for válida.
 */
Coordinates Reversi::searcherForPlay(int row, int col, int dRow, int dCol, char symbol, char opposite, bool passedOpponent, const BoardType &board) {
    if (row > 7 || row < 0 || col > 7 || col < 0)
        return {-1, -1};

    if (getSquare({row, col}, board) == ' ' && passedOpponent) {
        Coordinates validPlay(row, col);
        return validPlay;
    }

    if (getSquare({row, col}, board) == ' ')
        return {-1, -1};

    if (getSquare({row, col}, board) == symbol)
        return {-1, -1};

    if (getSquare({row, col}, board) == opposite)
        return searcherForPlay(row + dRow, col + dCol, dRow, dCol, symbol, opposite, true, board);

    return {-1, -1};
}

/**
 * @brief Retorna as jogadas possíveis para o jogador atual.
 * 
 * @param symbol Símbolo do jogador atual.
 * @param board Tabuleiro atual.
 * @return std::vector<Coordinates> Vetor contendo as coordenadas das jogadas possíveis.
 */
std::vector<Coordinates> Reversi::getPossiblePlays(char symbol, const BoardType &board) {
    std::vector<Coordinates> validPlays;
    char opposite = (symbol == 'X') ? 'O' : 'X';

    // Percorre o tabuleiro em busca das jogadas possíveis
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 7; col++) {
            if (getSquare({row, col}, board) == symbol) {
                int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
                for (int i = 0; i < 8; i++) {
                    int dRow = directions[i][0];
                    int dCol = directions[i][1];
                    Coordinates aux = searcherForPlay(row + dRow, col + dCol, dRow, dCol, symbol, opposite, false, board);
                    if (aux.getRow() != -1 && aux.getCol() != -1)
                        validPlays.push_back(aux);
                }
            }
        }
    }
    return validPlays;
}

/**
 * @brief Verifica se a jogada realizada é válida.
 * 
 * @param row Linha da jogada.
 * @param col Coluna da jogada.
 * @param symbol Símbolo do jogador atual.
 * @return true Se a jogada é válida.
 * @return false Se a jogada é inválida.
 */
bool Reversi::verifyPlay(int row, int col, char symbol) {
    std::vector<Coordinates> validPlays = getPossiblePlays(symbol, getBoard());
    if (validPlays.size() == 0) 
        return false;

    for (auto play : validPlays) {
        if (play.getRow() == row && play.getCol() == col) 
            return true;
    }
    return false;
}


//PRECISA COMENTAR ESSA? ELA É INUTILIZADA
/**
 * @brief Reverte os símbolos
 *  
 * @param row Linha da jogada
 * @param col Coluna da joagada
 */

void Reversi::reverseSymbols(int row, int col){
    char symbol = getSquare({row, col}, getBoard());
    if (symbol == 'X')
        setSquare ({row, col}, 'O');
    else if (symbol == 'O')
        setSquare ({row, col}, 'X');
    else 
        setSquare ({row, col}, ' ');
}


/**
 * @brief Conta quantos símbolos de determinado tipo estão presentes no tabuleiro.
 * 
 * @param symbol Símbolo do jogador ('X' ou 'O').
 * @return int Número de peças do símbolo.
 */
int Reversi::countSymbols(char symbol) {
    int counter = 0;
    for(int row = 0; row < getRows(); row++) {
        for(int col = 0; col < getCols(); col++) {
            if(getSquare({row, col}, getBoard()) == symbol)
                counter++;
        }
    }
    return counter;
}

/**
 * @brief Verifica quem é o vencedor da partida, contando as peças no tabuleiro.
 * 
 * @return Player* Ponteiro para o jogador vencedor ou nullptr em caso de empate.
 */
Player* Reversi::checkWinner() {
    int xCount = countSymbols('X');
    int oCount = countSymbols('O');

    if (xCount > oCount) {
        return getPlayer1();
    } else if (oCount > xCount) {
        return getPlayer2();
    } else {
        return nullptr; // Empate
    }
}

/**
 * @brief Função recursiva para virar peças do oponente se possível.
 * 
 * @param row Linha da jogada.
 * @param dRow Direção da linha.
 * @param col Coluna da jogada.
 * @param dCol Direção da coluna.
 * @param symbol Símbolo do jogador atual.
 * @param isOriginalTile Indica se é a peça original jogada pelo jogador.
 * @param board Tabuleiro atual.
 * @return true Se foi possível virar as peças.
 * @return false Se não foi possível virar as peças.
 */
bool Reversi::turnPieces(int row, int dRow, int col, int dCol, char symbol, bool isOriginalTile, const BoardType &board) {
    if (!isValidSquare({row, col})) 
        return false;

    if (getSquare({row, col}, board) == symbol && !isOriginalTile) 
        return true;

    if (getSquare({row, col}, board) == ' ' && !isOriginalTile) 
        return false;

    if (turnPieces(row + dRow, dRow, col + dCol, dCol, symbol, false, board)) {
        setSquare({row, col}, symbol);
        return true;
    }

    return false;
}

/**
 * @brief Atualiza as estatísticas do jogador após uma vitória.
 * 
 * @param winner Jogador vencedor.
 * @param loser Jogador perdedor.
 */
void Reversi::addStats(Player* winner, Player* loser) {
    std::cout << winner->getNickname() << " ganhou a partida!" << std::endl;
    winner->winReversi();
    loser->loseReversi();
}

/**
 * @brief Verifica se o jogo chegou ao estado terminal (sem jogadas possíveis).
 * 
 * @param board Tabuleiro atual.
 * @return true Se o jogo está no estado terminal.
 * @return false Se o jogo ainda não terminou.
 */
bool Reversi::terminalState(const BoardType &board) {
    if (getPossiblePlays('X', board).size() == 0 && getPossiblePlays('O', board).size() == 0)
        return true;

    return false;
}
