//
// Created by daniel hazan on 1/7/2018.
//
#include "Bishop.h"
#include "Board.h"

/**
 * Piece constructor
 */
Bishop::Bishop(int xLoc, int yLoc, string color, bool IsKing) : Piece(xLoc, yLoc, color, IsKing)
{

}

/**
 * returns all the piece possible moves from it's current coords.
 */
int ***Bishop::getAllPossibleMoves()
{
    return Move::getAllPossibleMoves("diagonal", _xCord, _yCord);
}

/**
 * returns the symbol to be printed to the board
 */
string Bishop::getUniCode()
{
    return "\u265D";
}

/**
 * this method checks if the piece can move to given coordinates
 */
bool Bishop::isValidMove(Board &board, int xCord, int yCord)
{
    int i, currentX, currentY;
    Move *move = new Move(this->_xCord, this->_yCord, xCord, yCord);

    if (move->getMoveType() != "diagonal")
    {
        delete move;
        return false;
    }
    move->getAllMovesInbetween();
    for (i = 0; i < move->getNumberOfMoves(); i++)
    {
        currentX = move->movesInBetween[i][X];
        currentY = move->movesInBetween[i][Y];
        if (board.isPieceInPositionNull(currentX, currentY))
        {
            continue;
        }
        else if (i == move->getNumberOfMoves() - 1)
        {
            delete move;
            return this->canEatAt(board, currentX, currentY);
        }
        else
        {
            delete move;
            return false;
        }
    }
    delete move;
    return true;
}
