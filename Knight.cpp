//
// Created by daniel hazan on 1/7/2018.
//
#include "Knight.h"

/**
 * Piece constructor, loading it's inital x position, y position, it's color and T/F whether the piece
 * is a king or not.
 * @param xLoc original x pos
 * @param yLoc original y pos
 * @param color piece color
 * @param IsKing T/F
 */
Knight::Knight(int xLoc, int yLoc, string color, bool IsKing) : Piece(xLoc, yLoc, color, IsKing)
{

}

/**
 * returns T/F whether the given coords are a valid move for this piece
 */
bool Knight::isValidMove(Board &board, int xCord, int yCord)
{
    Move *move = new Move(this->_xCord, this->_yCord, xCord, yCord);

    if (move->getMoveType() != "knightMove")
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

/**
 * returns the unicode for this piece for printing to the screen by the Board class
 */
string Knight::getUniCode()
{
    return "\u265E";
}

/**
 * returns T/F whether or not this piece is threatening the opponent's king
 */
bool Knight::isKingThreaten(Board &board)
{
    //search up right
    int newY;
    int newX;
    newY = this->getY() + 2;
    newX = (this->getX() + 1);
    if (0 < newY && newY <= board.getHeight() && 0 < newX && newX <= board.getLength())
    {
        Piece &piece = board.getPieceAt(newX, newY);
        //if (&piece != nullptr)
        if(!board.isPieceInPositionNull(newX, newY))
        {

            if (piece._Is_king && piece.getColor() != this->getColor())
            {

                return true;
            }
        }
    }
    //search right up
    newY = this->getY() + 1;
    newX = (this->getX() + 2);
    if (0 < newY && newY <= board.getHeight() && 0 < newX && newX <= board.getLength())
    {
        Piece &piece = board.getPieceAt(newX, newY);
        if(!board.isPieceInPositionNull(newX, newY))
        //if (&piece != nullptr)
        {

            if (piece._Is_king && piece.getColor() != this->getColor())
            {

                return true;
            }
        }
    }

    //search up left

    newY = this->getY() + 2;
    newX = (this->getX() - 1);
    if (0 < newY && newY <= board.getHeight() && board.getLength() > newX && newX >= 1)
    {
        Piece &piece = board.getPieceAt(newX, newY);
        //if (&piece != nullptr)
        if(!board.isPieceInPositionNull(newX, newY))
        {

            if (piece._Is_king && piece.getColor() != this->getColor())
            {

                return true;
            }
        }
    }
    //search left up
    newY = this->getY() + 1;
    newX = (this->getX() - 2);
    if (newY <= board.getHeight() && newY > 0 && 0 < newX && newX <= board.getLength())
    {
        Piece &piece = board.getPieceAt(newX, newY);
        //if (&piece != nullptr)
        if(!board.isPieceInPositionNull(newX, newY))
        {

            if (piece._Is_king && piece.getColor() != this->getColor())
            {

                return true;
            }
        }
    }

    //search down left
    newY = this->getY() - 2;
    newX = (this->getX() - 1);
    if (board.getHeight() > newY && newY >= 1 && board.getLength() > newX &&
        newX >= 1)//check if its inside board's limits
    {
        Piece &piece = board.getPieceAt(newX, newY);
        //if (&piece != nullptr)
        if(!board.isPieceInPositionNull(newX, newY))
        {

            if (piece._Is_king && piece.getColor() != this->getColor())
            {

                return true;
            }
        }
    }
    //search left down
    newY = this->getY() - 1;
    newX = (this->getX() - 2);
    if (0 < newY && newY <= board.getHeight() && 0 < newX && newX <= board.getLength())
    {
        Piece &piece = board.getPieceAt(newX, newY);
        //if (&piece != nullptr)
        if(!board.isPieceInPositionNull(newX, newY))
        {

            if (piece._Is_king && piece.getColor() != this->getColor())
            {

                return true;
            }
        }
    }

    //search down right
    newY = this->getY() - 2;
    newX = (this->getX() + 1);
    if (newY <= board.getHeight() && newY >= 1 && 0 < newX && newX <= board.getLength())
    {
        Piece &piece = board.getPieceAt(newX, newY);
        //if (&piece != nullptr)
        if(!board.isPieceInPositionNull(newX, newY))
        {

            if (piece._Is_king && piece.getColor() != this->getColor())
            {

                return true;
            }

        }
    }
    //search right down
    newY = this->getY() - 1;
    newX = (this->getX() + 2);
    if (0 < newY && newY <= board.getHeight() && 0 < newX && newX <= board.getLength())
    {
        Piece &piece = board.getPieceAt(newX, newY);
        //if (&piece != nullptr)
        if(!board.isPieceInPositionNull(newX, newY))
        {

            if (piece._Is_king && piece.getColor() != this->getColor())
            {

                return true;
            }
        }
    }
    return false;
}

/**
 * returns all the piece's possible moves from it's current coords
 */
int ***Knight::getAllPossibleMoves()
{
    return Move::getAllPossibleMoves("knightMove", _xCord, _yCord);
}
