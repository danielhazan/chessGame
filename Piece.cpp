//
// Created by daniel hazan on 1/6/2018.
//

#include "Piece.h"
#include "Board.h"

/**
 * Piece constructor, loading it's inital x position, y position, it's color and T/F whether the piece
 * is a king or not.
 * @param xLoc original x pos
 * @param yLoc original y pos
 * @param color piece color
 * @param IsKing T/F
 */
Piece::Piece(int xLoc, int yLoc, string &color, bool IsKing) : _xCord(xLoc), _yCord(yLoc),
                                                                _color(color), _Is_king(IsKing)
{

}

/**
 * returns T/F whether or not a piece can be eaten by this piece in given coords
 */
bool Piece::canEatAt(Board &board, int xCord, int yCord)
{
    if (board.isPieceInPositionNull(xCord, yCord))
    {
        return false;
    }
    else
    {
        return board.getPieceAt(xCord, yCord).getColor() != this->getColor();
    }
}

/**
 * returns x pos
 */
int Piece::getX()
{
    return _xCord;
}

/**
 * returns y pos
 */
int Piece::getY()
{
    return _yCord;
}

/**
 * return piece color
 */
const string Piece::getColor()
{
    return this->_color;
}

/**
 * moves the piece to given coords
 */
void Piece::movePiece(Board &board, int xCord, int yCord)
{
    board.updateBoard(this->getX(), this->getY(), xCord, yCord);
    _xCord = xCord;
    _yCord = yCord;
}

/**
 * returns T/F whether or not this piece is threatening the opponent's king
 */
bool Piece::isKingThreaten(Board &board)
{
    int i, j;
    int ***moves = this->getAllPossibleMoves();
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (moves[i][j][X] == 9)
            {
                continue;
            }
            if (board.isPieceInPositionNull(moves[i][j][X], moves[i][j][Y]))
            {
                continue;
            }
            else if (board.getPieceAt(moves[i][j][X], moves[i][j][Y])._Is_king &&
                     board.getPieceAt(moves[i][j][X], moves[i][j][Y]).getColor() != this->getColor())
            {
                return true;
            }
            else
            {
                break;
            }
        }
    }
    return false;
}

/**
 * returns all the piece's possible moves from it's current coords
 */
int*** Piece::getAllPossibleMoves()
{
    return nullptr;
}
