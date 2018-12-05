//
// Created by daniel hazan on 1/8/2018.
//
#include "King.h"

/**
 * Piece constructor
 */
King::King(int xLoc, int yLoc, string color, bool IsKing) : Piece(xLoc, yLoc, color, IsKing)
{

}

/**
 * returns the symbol to be printed to the board
 */
string King::getUniCode()
{
    return "\u265A";
}

/**
 * this method checks if the Soldier can eat another piece on board at the given coordinates.
 * if there is another piece of the enemy's type - removing it from board and returns true.
 * return false otherwise
 */
bool King::isKingThreaten(Board &board)
{
    (void) board;
    return false;
}

/**
 * returns all the piece possible moves from it's current coords.
 */
int ***King::getAllPossibleMoves()
{
    int i;
    auto ***moves = new int **[1];
    moves[0] = new int *[8];
    for (i = 0; i < 8; i++)
    {
        moves[0][i] = new int[2];
    }
    moves[0][0][X] = this->_xCord;
    moves[0][0][Y] = this->_yCord + 1;

    moves[0][1][X] = this->_xCord + 1;
    moves[0][1][Y] = this->_yCord + 1;

    moves[0][2][X] = this->_xCord + 1;
    moves[0][2][Y] = this->_yCord;

    moves[0][3][X] = this->_xCord + 1;
    moves[0][3][Y] = this->_yCord - 1;

    moves[0][4][X] = this->_xCord;
    moves[0][4][Y] = this->_yCord - 1;

    moves[0][5][X] = this->_xCord - 1;
    moves[0][5][Y] = this->_yCord - 1;

    moves[0][6][X] = this->_xCord - 1;
    moves[0][6][Y] = this->_yCord;

    moves[0][7][X] = this->_xCord - 1;
    moves[0][7][Y] = this->_yCord + 1;

    return moves;
}

/**
 * this method checks if the piece can move to given coordinates
 */
bool King::isValidMove(Board &board, int xCord, int yCord)
{
    Move *move = new Move(this->_xCord, this->_yCord, xCord, yCord);

    if ((move->getMoveType() != "straight" && move->getMoveType() != "diagonal") ||
        move->getNumberOfMoves() != 1)
    {
        delete move;
        return false;
    }
    else if (board.isPieceInPositionNull(xCord, yCord))
    {
        delete move;
        return true;
    }
    else
    {
        delete move;
        return canEatAt(board, xCord, yCord);
    }
}
