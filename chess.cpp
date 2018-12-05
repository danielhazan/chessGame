//
// Created by daniel hazan on 1/5/2018.
//
#include <cstring>
#include <iostream>
#include "Board.h"
#include "Soldier.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"

#define WHITE_NUM 0
#define BLACK_NUM 1

string const WHITE = "white", BLACK = "black";

/**
 * this functions get a move command from user and checks if the input is valid
 * @return the 4 x,y valuess of the source location and the x,y values of the target locations
 */
void getMoveFrom(std::string basic_string, char &x_player1, int &y_player1, char &toX_player1,
                 int &toY_player1);

/**
 * helper for the main loop, attempts to move piece, after making sure the move is legal
 */
void movePiece(Board &board, std::string playerName, std::string playerColor, char fromX, int
               fromY, char toX, int toY);

/**
 * making sure the input is in the right format. i.e <CAPITAL_LETTER><NUMBER><CAPITAL_LETTER><NUMBER>
 * @param input input to check
 * @return T / F
 */
bool inputCheck(std::string input);

/**this function get the names of the two players from user**/
void getUsersName(std::string &nameWhite, std::string &nameBlack);

/**
 * main function
 * @return 0 / else
 */
int main()
{
    int playerCheck = WHITE_NUM, i;
    char currentFromX = 0;
    int currentFromY = 0;
    char currentToX = 0;
    int currentToY = 0;
    std::string nameBlack;
    std::string nameWhite;
    std::string currentPlayerName;
    std::string currentPlayerColor = "white";
    std::string WinnerColor;
    std::string WinnerName;
    Board *board;
    Piece *whitePieces[25];
    Piece *blackPieces[25];

    // initializing board
    for (i = 1; i <= 8; i++)
    {
        whitePieces[i + 8] = new Soldier(i, 2, WHITE);
        blackPieces[i + 8] = new Soldier(i, 7, BLACK);
    }
    whitePieces[1] = new Rook(1, 1, WHITE);
    whitePieces[8] = new Rook(8, 1, WHITE);
    blackPieces[1] = new Rook(1, 8, BLACK);
    blackPieces[8] = new Rook(8, 8, BLACK);
    whitePieces[2] = new Knight(2, 1, WHITE);
    whitePieces[7] = new Knight(7, 1, WHITE);
    blackPieces[2] = new Knight(2, 8, BLACK);
    blackPieces[7] = new Knight(7, 8, BLACK);
    whitePieces[3] = new Bishop(3, 1, WHITE);
    whitePieces[6] = new Bishop(6, 1, WHITE);
    blackPieces[3] = new Bishop(3, 8, BLACK);
    blackPieces[6] = new Bishop(6, 8, BLACK);
    whitePieces[5] = new King(5, 1, WHITE, true);
    whitePieces[4] = new Queen(4, 1, WHITE);
    blackPieces[5] = new King(5, 8, BLACK, true);
    blackPieces[4] = new Queen(4, 8, BLACK);
    board = new Board(8, 8, whitePieces, blackPieces);
    //

    getUsersName(nameWhite, nameBlack);
    currentPlayerName = nameWhite;
    board->printBoard();

    // MAIN LOOP
    while (!board->isEndOfGame(currentPlayerColor))
    {
        if (board->isChessFor(currentPlayerColor))
        {
            std::cout << "\33[37;41mCheck!\33[0m" << std::endl;
        }
        movePiece(*board, currentPlayerName, currentPlayerColor, currentFromX, currentFromY,
                  currentToX,
                  currentToY);
        playerCheck++;
        board->printBoard();
        if (playerCheck % 2 == WHITE_NUM)
        {
            currentPlayerName = nameWhite;
            currentPlayerColor = WHITE;
        }
        else
        {
            currentPlayerName = nameBlack;
            currentPlayerColor = BLACK;
        }
    }

    // handle end of game
    if (currentPlayerColor == WHITE)
    {
        WinnerColor = BLACK;
    }
    else
    {
        WinnerColor = WHITE;
    }

    if (WinnerColor == WHITE)
    {
        WinnerName = nameWhite;
    }
    else
    {
        WinnerName = nameBlack;
    }
    std::cout << WinnerName + " won!" << std::endl;

    // deleting pieces
    delete board;
}

/**
 * this function get the names of the two players from user
 */
void getUsersName(std::string &nameWhite, std::string &nameBlack)
{
    std::cout << "Enter white player name:\n";
    std::cin >> nameWhite;
    std::cout << "Enter black player name:\n";
    std::cin >> nameBlack;
}

/**
 * this helper function moves the pieces on board and run the main loop of the game according to user input
 * */
void movePiece(Board &board, std::string const playerName, std::string const playerColor, char
               fromX, int fromY, char toX, int toY)
{
    getMoveFrom(playerName, fromX, fromY, toX, toY);
    bool inputCheck = false;
    int fromXint, toXint;

    // translating x_axis coordinates to numbers
    fromXint = fromX - 'A' + 1;
    toXint = toX - 'A' + 1;

    while (!inputCheck)
    {
        // handle castling
        if (fromXint == 9)
        {
            // "big" castling
            if (toXint == 9)
            {
                if (board.handleCastling(playerColor, false))
                {
                    break;
                }
                else
                {
                    std::cout << "\33[37;41millegal move\33[0m" << std::endl;
                    getMoveFrom(playerName, fromX, fromY, toX, toY);
                    fromXint = fromX - 'A' + 1;
                    toXint = toX - 'A' + 1;
                    continue;
                }
            }
                // "small" castling
            else
            {
                if (board.handleCastling(playerColor, true))
                {
                    break;
                }
                else
                {
                    std::cout << "\33[37;41millegal move\33[0m" << std::endl;
                    getMoveFrom(playerName, fromX, fromY, toX, toY);
                    fromXint = fromX - 'A' + 1;
                    toXint = toX - 'A' + 1;
                    continue;
                }
            }
        }

        // check if the from cordinates have a piece
        if (board.isPieceInPositionNull(fromXint, fromY))
        {
            std::cout << "\33[37;41millegal move\33[0m" << std::endl;
            getMoveFrom(playerName, fromX, fromY, toX, toY);
            fromXint = fromX - 'A' + 1;
            toXint = toX - 'A' + 1;
            continue;
        }
        Piece &currentPiece = board.getPieceAt(fromXint, fromY);
        // check if the piece is in the same color as the current player
        if (currentPiece.getColor() != playerColor)
        {
            std::cout << "\33[37;41millegal move\33[0m" << std::endl;
            getMoveFrom(playerName, fromX, fromY, toX, toY);
            fromXint = fromX - 'A' + 1;
            toXint = toX - 'A' + 1;
            continue;
        }
        // check if the move is valid
        if (!currentPiece.isValidMove(board, toXint, toY))
        {
            std::cout << "\33[37;41millegal move\33[0m" << std::endl;
            getMoveFrom(playerName, fromX, fromY, toX, toY);
            fromXint = fromX - 'A' + 1;
            toXint = toX - 'A' + 1;
            continue;
        }
        // check if move will create check, and move it if it doesn't
        if (board.isMoveCreatingCheck(playerColor, fromXint, fromY, toXint, toY))
        {
            std::cout << "\33[37;41millegal move\33[0m" << std::endl;
            getMoveFrom(playerName, fromX, fromY, toX, toY);
            fromXint = fromX - 'A' + 1;
            toXint = toX - 'A' + 1;
            continue;
        }
        inputCheck = true;
        //
        if (!currentPiece.hasMoved)
        {
            currentPiece.hasMoved = true;
        }
    }
}

/**
 * this functions get a move command from user and checks if the input is valid
 * @return the 4 x,y valuess of the source location and the x,y values of the target locations
 */
void getMoveFrom(std::string const basic_string, char &x_player1, int &y_player1, char &toX_player1,
                 int &toY_player1)
{
    std::string input;
    std::cout << basic_string + ": Please enter your move:\n";
    std::cin >> input;

    if (input == "o-o")
    {
        x_player1 = 'I';
        y_player1 = 9;
        toX_player1 = 'A';
        toY_player1 = 1;
        return;
    }
    if (input == "o-o-o")
    {
        x_player1 = 'I';
        y_player1 = 9;
        toX_player1 = 'I';
        toY_player1 = 1;
        return;
    }

    while (cin.fail() || !inputCheck(input))
    {
        std::cout << "\33[37;41millegal move\33[0m" << std::endl;
        std::cout << basic_string + ": Please enter your move:\n";
        std::cin >> input;
        if (input == "o-o")
        {
            x_player1 = 0;
            y_player1 = 0;
            toX_player1 = 1;
            toY_player1 = 1;
            return;
        }
        if (input == "o-o-o")
        {
            x_player1 = 0;
            y_player1 = 0;
            toX_player1 = 0;
            toY_player1 = 1;
            return;
        }
    }
    x_player1 = input.at(0);
    y_player1 = (int) input.at(1) - '0';
    toX_player1 = input.at(2);
    toY_player1 = (int) input.at(3) - '0';
}

/**
 * making sure the input is in the right format. i.e <CAPITAL_LETTER><NUMBER><CAPITAL_LETTER><NUMBER>
 * @param input input to check
 * @return T / F
 */
bool inputCheck(std::string input)
{
    int numToCheck;
    unsigned int i;
    char letterToCheck;

    // making sure the input has the right amount of chars
    if (input.length() != 4)
    {
        return false;
    }
    // making sure the first and third chars in the input are capital letters between A and H
    for (i = 0; i <= 2; i += 2)
    {
        letterToCheck = input.at(i);
        if (letterToCheck < 'A' || letterToCheck > 'H')
        {
            return false;
        }
    }
    // making sure the second and fourth chars in the input are numbers between 1 and 8
    for (i = 1; i <= 3; i += 2)
    {
        if (!isdigit(input.at(i)))
        {
            return false;
        }
        numToCheck = (int) input.at(i) - '0';
        if (numToCheck < 1 || numToCheck > 8)
        {
            return false;
        }
    }
    return true;
}
