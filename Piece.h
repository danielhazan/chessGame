//
// Created by daniel hazan on 1/6/2018.
//

#define X 0
#define Y 1
#define RIGHT_EDGE_X 8
#define LEFT_EDGE_X 1
#define TOP_EDGE_Y 8
#define LOW_EDGE_Y 1

using namespace std;

#ifndef CPPEX2NEW_PIECE_H
#define CPPEX2NEW_PIECE_H

#include <string>
#include "Move.h"

class Board;

/**
 * class Piece -> an abstract base class of all pieces types on chess board game
 */
class Piece
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
    Piece(int xLoc, int yLoc, string &color, bool IsKing = false);

    /**
     * destructor
     */
    virtual ~Piece() = default;

    /**
     * returns x pos
     */
    virtual int getX();

    /**
     * returns y pos
     */
    virtual  int getY();

    /**
     * return piece color
     */
    virtual const string getColor();

    /**
     * returns T/F whether or not a piece can be eaten by this piece in given coords
     */
    virtual bool canEatAt(Board &board, int xCord, int yCord);

    /**
     * returns T/F whether or not this piece is threatening the opponent's king
     */
    virtual bool isKingThreaten(Board &board);

    /**
     * moves the piece to given coords
     */
    virtual void movePiece(Board &board, int xCord, int yCord);

    /**
     * returns T/F whether the given coords are a valid move for this piece
     */
    virtual bool isValidMove(Board &board, int xCord, int yCord) = 0;

    /**
     * returns the unicode for this piece for printing to the screen by the Board class
     */
    virtual string getUniCode() = 0;

    /**
     * returns all the piece's possible moves from it's current coords
     */
    virtual int*** getAllPossibleMoves() ;

    int _xCord;
    int _yCord;
    string _color;
    bool _Is_king = false; //??? regular or king
    bool stillInPlay = true;
    bool hasMoved = false;
};

#endif //CPPEX2NEW_PIECE_H
