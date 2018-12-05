//
// Created by Shai on 13/01/2018.
//

#ifndef EX2_MOVE_H
#define EX2_MOVE_H

#define RIGHT_EDGE_X 8
#define LEFT_EDGE_X 1
#define TOP_EDGE_Y 8
#define LOW_EDGE_Y 1

#include <iostream>


/**
 * class Move - this class consists methods for calculating and defining legal
 * locations and movevements for each piece on chessboard
 * */
class Move
{
private:
    int _fromX, _toX, _fromY, _toY, _numberOfMoves;
    std::string _moveType, _moveDirection;

public:
    /**
     * Move constructor, gets original and destination x and y coords and calculates from them the attributes
     * (number of moves, move type and direction)
     */
    Move(int fromX, int fromY, int toX, int toY);

    /**
     * gets a knight move from the given arguments
     */
    static void getKnightMove(int fromX, int fromY, int upDown, int rightLeft, int &toX, int &toY, int &counter);

    /**
     * gets the edge possible from moving in a given direction diagonally
     */
    static int* getDiagonalCoords(int fromX, int fromY, bool up, bool right);

    /**
     * gets an array of moves, from a given type and given coords.
     */
    static int ***getAllPossibleMoves(std::string typeOfMove, int xCord, int yCord);

    /**
     * calculate all moves between this object's from coords and to coords
     */
    void getAllMovesInbetween();

    /**
     * returns move type
     */
    std::string getMoveType();

    /**
     * returns number of moves
     */
    int getNumberOfMoves();

    /**
     * calcualtes all the moves attributes (number of moves, move type and direction)
     */
    void calculateMoveAttributes();

    /**
     * an array that keeps all the moves between the from coords and to coords
     */
    int** movesInBetween;
};

#endif //EX2_MOVE_H
