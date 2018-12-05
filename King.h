//
// Created by daniel hazan on 1/8/2018.
//
#include "Piece.h"
#include "Board.h"

#ifndef CPPEX2NEW_KING_H
#define CPPEX2NEW_KING_H


/**
 * class King defines the fields and methods for the King piece on chessboard
 * */
class King : public Piece //Soldier hides Piece
{

public:
    /**
     * Piece constructor
     */
    King(int xLoc, int yLoc, string color, bool IsKing);

    /**
     * returns the symbol to be printed to the board
     */
    string getUniCode() override;

    /**
     * returns all the piece possible moves from it's current coords.
     */
    int*** getAllPossibleMoves() override;

    /**
     * this method checks if the Soldier can eat another piece on board at the given coordinates.
     * if there is another piece of the enemy's type - removing it from board and returns true.
     * return false otherwise
     */
    bool isKingThreaten(Board &board) override;

    /**
     * this method checks if the piece can move to given coordinates
     */
    bool isValidMove(Board &board, int xCord, int yCord) override;

};


#endif //CPPEX2NEW_KING_H
