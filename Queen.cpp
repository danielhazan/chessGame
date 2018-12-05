//
// Created by daniel hazan on 1/7/2018.
//

#include "Queen.h"
#include "Board.h"

/**
* Piece constructor, loading it's inital x position, y position, it's color and T/F whether the piece
* is a king or not.
* @param xLoc original x pos
* @param yLoc original y pos
* @param color piece color
* @param IsKing T/F
*/
Queen::Queen(int xLoc, int yLoc, string color, bool IsKing) : Piece(xLoc, yLoc, color, IsKing)
{

}

/**
 * returns all the piece's possible moves from it's current coords
 */
int*** Queen::getAllPossibleMoves()
{
    return Move::getAllPossibleMoves("straightAndDiagonal", _xCord, _yCord);
}

/**
 * returns T/F whether the given coords are a valid move for this piece
 */
bool Queen::isValidMove(Board &board, int xCord, int yCord)
{
    int i, currentX, currentY;
    Move *move = new Move(this->_xCord, this->_yCord, xCord, yCord);

    if (move->getMoveType() != "straight" && move->getMoveType() != "diagonal")
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

/**
 * returns the unicode for this piece for printing to the screen by the Board class
 */
string Queen::getUniCode()
{
    return "\u265B";
}
