
//
// Created by daniel hazan on 1/7/2018.
//
#include "Piece.h"
#include "Board.h"

#ifndef CPPEX2NEW_ROOK_H
#define CPPEX2NEW_ROOK_H

/**
 * class Rook defines the fields and methods for the Rook piece on chessboard
 * */
class Rook : public Piece //Soldier hides Piece
{
public:

    /**
     * Piece constructor, loading it's inital x position, y position, it's color and T/F whether the piece
     * is a king or not.
     * @param xLoc original x pos
     * @param yLoc original y pos
     * @param color piece color
     * @param IsKing T/F
     */
    Rook(int xLoc, int yLoc, string color, bool IsKing = false);

    /**
     * returns the unicode for this piece for printing to the screen by the Board class
     */
    string getUniCode() override;

    /**
     * returns all the piece's possible moves from it's current coords
     */
    int ***getAllPossibleMoves() override;

    /**
     * returns T/F whether the given coords are a valid move for this piece
     */
    bool isValidMove(Board &board, int xCord, int yCord) override;
};


#endif //CPPEX2NEW_ROOK_H
