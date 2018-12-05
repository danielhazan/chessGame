//
// Created by daniel hazan on 1/6/2018.
//
#include "Board.h"
#include "Soldier.h"

/**
 * Piece constructor, loading it's inital x position, y position, it's color and T/F whether the piece
 * is a king or not.
 * @param xLoc original x pos
 * @param yLoc original y pos
 * @param color piece color
 * @param IsKing T/F
 */
Soldier::Soldier(int xLoc, int yLoc, string color, bool IsKing) : Piece(xLoc, yLoc, color, IsKing)
{

}

/**
 * returns the unicode for this piece for printing to the screen by the Board class
 */
string Soldier::getUniCode()
{
    return "\u265F";
}

/**
 * returns T/F whether or not this piece is threatening the opponent's king
 */
bool Soldier::isKingThreaten(Board &board)
{
    int colorFactor;
    if (this->_color == "white")
    {
        colorFactor = 1;
    }
    else
    {
        colorFactor = -1;
    }
    // check right
    if (!board.isPieceInPositionNull(this->_xCord + 1, this->_yCord + colorFactor))
    {
        Piece &tempPiece = board.getPieceAt(this->_xCord + 1, this->_yCord + colorFactor);
        return (tempPiece.getColor() != this->getColor() && tempPiece._Is_king);
    }
        // check left
    else if (!board.isPieceInPositionNull(this->_xCord - 1, this->_yCord + colorFactor))
    {
        Piece &tempPiece = board.getPieceAt(this->_xCord - 1, this->_yCord + colorFactor);
        return (tempPiece.getColor() != this->getColor() && tempPiece._Is_king);
    }
    else
    {
        return false;
    }
}

void Soldier::movePiece(Board &board, int xCord, int yCord)
{
    board.updateBoard(this->getX(), this->getY(), xCord, yCord);
    _xCord = xCord;
    _yCord = yCord;
    if ((this->_color == "white" && this->_yCord == 8) ||
        (this->_color == "black" && this->_yCord == 1))
    {
        board.removeFromBoard(*this);
        board.setQueenAt(this->_xCord, this->_yCord, this->_color);
    }
}

/**
 * moves the piece to given coords
 */
bool Soldier::isValidMove(Board &board, int xCord, int yCord)
{
    int colorFactor;
    if (this->_color == "white")
    {
        colorFactor = 1;
    }
    else
    {
        colorFactor = -1;
    }

    // straight moves
    if (this->_xCord == xCord)
    {
        // 2 steps forward
        if (yCord == this->_yCord + 2 * colorFactor)
        {
            return board.isPieceInPositionNull(this->_xCord, this->_yCord + colorFactor) && board
                    .isPieceInPositionNull(this->_xCord, this->_yCord + 2 * colorFactor) && !this->hasMoved;
        }
            // 1 step forward
        else if (yCord == this->_yCord + colorFactor)
        {
            return board.isPieceInPositionNull(this->_xCord, this->_yCord + colorFactor);
        }
        else
        {
            return false;
        }
    }
        // diagonal move
    else if (abs(this->_xCord - xCord) == 1 && yCord == this->_yCord + colorFactor)
    {
        return (canEatAt(board, xCord, yCord));
    }
    else
    {
        return false;
    }
}
