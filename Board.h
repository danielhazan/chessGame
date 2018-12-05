//
// Created by daniel hazan on 1/6/2018.
//

#ifndef CPPEX2NEW_BOARD_H
#define CPPEX2NEW_BOARD_H

#include <iostream>
#include "Queen.h"

/**
 * class Board represents and constructs the GUI board chess on screen
 */
class Board
{
private:

    const int len_x;
    const int len_y;
    Piece *board[9][9];
    Piece **black;
    Piece **white;
    int NumOfBlacks;
    int NumOfWhites;
    Piece *whiteKing;
    Piece *blackKing;


public:

    /**
     * initializes the board, with its size and pieces
     */
    Board(int cols, int rows, Piece **white, Piece **black);

    /**
     * destructor -> free all the pieces remained on board at the end of game
     * */
    ~Board();

    /**
     * prints the board
     */
    void printBoard();

    /**
     * checking if there is a piece in a position
     * @param xCord x coordinate
     * @param yCord y coordinate
     * @return  T / F
     */
    bool isPieceInPositionNull(int xCord, int yCord);

    /**
     * checking if a move is creating chess for the current player, to see if it's legal or not
     * @param playerColor current player color
     * @param fromX original x position
     * @param fromY original y position
     * @param toX destination x position
     * @param toY destination y position
     * @return T / F
     */
    bool isMoveCreatingCheck(string playerColor, int fromX, int fromY, int toX, int toY);

    /**
     * updating board whenever moving a piece from an original location to a source location
     */
    void updateBoard(int xCordOrg, int yCordOrg, int xCordTarget, int yCordTarget);

    /**
     * removing a piece from the board
     * @param piece
     */
    void removeFromBoard(Piece &piece);

    /**
     * returns the piece in the given coordinates
     */
    Piece &getPieceAt(int xCord, int yCord);
    /**
     * returns true if the player's king within the given color is threatened by any
     * of the oponent's pieces
     * */
    bool isChessFor(std::string const color);

    /**
     * this method set a new Queen in a certain location - called when a Soldier piece get to the
     * end of board
     */
    void setQueenAt(int xCord, int yCord, std::string color);

    /**
     * attempting to do a castling for a given player
     * @param playerColor current player color
     * @param smallCastling T / F
     * @return T / F
     */
    bool handleCastling(string playerColor, bool smallCastling);

    /**
     * checking if the game has ended by checking if the current player's king has moves that won't put him
     * in chess.
     * @param playerColor current player color
     * @return T / F whether it was succesful or not
     */
    bool isEndOfGame(string playerColor);

    /**
     * helper for handlingCastling (to avoid too complicated code)/
     */
    bool handleCastlingHelper(Piece** pieces, int i, int yCord);

    /**
     * helper for isEndOfGame (to avoid too complicated code)
     */
    void isEndOfGameHelper(Piece** pieces, bool &flag, int*** possibleMoves, int i);

    /**
     * get board length
     */
    int getLength();

    /**
     * get board height
     */
    int getHeight();
};

#endif //CPPEX2_BOARD_H
