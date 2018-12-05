
//
// Created by daniel hazan on 1/7/2018.
//

#include "Piece.h"

#ifndef CPPEX2NEW_BISHOP_H
#define CPPEX2NEW_BISHOP_H


/**
 * class Bishop defines the fields and methods for the Bishop piece on chessboard
 * */
class Bishop : public Piece
{
public:
    /**
     * Piece constructor
     */
    Bishop(int xLoc, int yLoc, string color, bool IsKing = false);

    /**
     * returns the symbol to be printed to the board
     */
    string getUniCode() override;

    /**
     * returns all the piece possible moves from it's current coords.
     */
    int ***getAllPossibleMoves() override;

    /**
     * this method checks if the piece can move to given coordinates
     */
    bool isValidMove(Board &board, int xCord, int yCord) override;

};


#endif //CPPEX2NEW_BISHOP_H
