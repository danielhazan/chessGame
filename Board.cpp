//
// Created by daniel hazan on 1/7/2018.
//

#include "Board.h"

/**
 * initializes the board, with its size and pieces
 */
Board::Board(int cols, int rows, Piece **white, Piece **black) : len_x(cols), len_y(rows),
             black(black), white(white), NumOfBlacks(16), NumOfWhites(16), whiteKing(white[5]),
             blackKing(black[5])
{
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            if (i == 1)
            {
                this->board[i][j] = this->white[j];
            }
            if (i == 2)
            {
                this->board[i][j] = this->white[j + 8];
            }
            if (i > 2 && i <= 6)
            {
                this->board[i][j] = nullptr;
            }
            if (i == 7)
            {
                this->board[i][j] = this->black[j + 8];
            }
            if (i == 8)
            {
                this->board[i][j] = this->black[j];
            }
        }
    }
};

/**
 * checking if there is a piece in a position
 * @param xCord x coordinate
 * @param yCord y coordinate
 * @return  T / F
 */
bool Board::isPieceInPositionNull(int xCord, int yCord)
{
    if (xCord < 1 || xCord > 8 || yCord < 1 || yCord > 8)
    {
        return true;
    }
    return this->board[yCord][xCord] == nullptr;
}

/**
     * checking if a move is creating chess for the current player, to see if it's legal or not
     * @param playerColor current player color
     * @param fromX original x position
     * @param fromY original y position
     * @param toX destination x position
     * @param toY destination y position
     * @return
     */
bool Board::isMoveCreatingCheck(string playerColor, int fromX, int fromY, int toX, int toY)
{
    bool isEating = false;
    Piece &eatenPiece = this->getPieceAt(toX, toY);
    Piece &movedPiece = this->getPieceAt(fromX, fromY);
    if (this->isPieceInPositionNull(toX, toY))
    {
        board[toY][toX] = nullptr;
        isEating = true;
    }
    if (movedPiece.canEatAt(*this, toX, toY))
    {
        this->removeFromBoard(eatenPiece);
    }
    movedPiece.movePiece(*this, toX, toY);
    if (isChessFor(playerColor))
    {
        movedPiece.movePiece(*this, fromX, fromY);
        if (isEating)
        {
            board[toY][toX] = &eatenPiece;
        }
        return true;
    }
    return false;
}

/**
 * updating board whenever moving a piece from an original location to a source location
 */
void Board::updateBoard(int xCordOrg, int yCordOrg, int xCordTarget, int yCordTarget)
{
    Piece &pieceToMove = this->getPieceAt(xCordOrg, yCordOrg);
    this->board[yCordOrg][xCordOrg] = nullptr;
    this->board[yCordTarget][xCordTarget] = &pieceToMove; // a pointer to the piece (gets its address)
}

/**
* removing a piece from the board
* @param piece
*/
void Board::removeFromBoard(Piece &piece)
{
    this->board[piece.getY()][piece.getX()] = nullptr;
    if (piece.getColor() == "white")
    {
        this->NumOfWhites--;
    }
    else
    {
        this->NumOfBlacks--;
    }
    piece.stillInPlay = false;

}

/**
* returns the piece in the given coordinates
*/
Piece &Board::getPieceAt(int xCord, int yCord)
{
    return *(this->board[yCord][xCord]);
}

/**
* returns true if the player's king within the given color is threatened by any
* of the oponent's pieces
* */
bool Board::isChessFor(std::string const color)
{
    for (int i = 1; i <= this->len_y; i++)
    {
        for (int j = 1; j <= this->len_x; ++j)
        {
            if (this->board[i][j] != nullptr)
            {
                if (this->board[i][j]->stillInPlay && this->board[i][j]->isKingThreaten(*this) &&
                    this->board[i][j]->getColor() != color)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * this method set a new Queen in a certain location - called when a Soldier piece get to the
 * end of board
 */
void Board::setQueenAt(int xCord, int yCord, std::string color)
{
    Queen *tempQueen = new Queen(xCord, yCord, color);
    this->board[yCord][xCord] = tempQueen;
    if (color == "white")
    {
        white[NumOfWhites + 1] = tempQueen;
        NumOfWhites++;
    }
    else
    {
        black[NumOfBlacks + 1] = tempQueen;
        NumOfBlacks++;
    }
}

/**
 * helper for handlingCastling (to avoid too complicated code)/
 */
bool Board::handleCastlingHelper(Piece** pieces, int i, int yCord)
{
    int j;
    for (j = 0; j <= 16; j++)
    {
        if (pieces[j] != nullptr)
        {
            if (pieces[j]->stillInPlay)
            {
                if (pieces[j]->isValidMove(*this, i, yCord))
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
    }
    return true;
}

/**
 * attempting to do a castling for a given player
 * @param playerColor current player color
 * @param smallCastling T / F
 * @return T / F
 */
bool Board::handleCastling(string playerColor, bool smallCastling)
{
    int yCord, i;
    if (playerColor == "white")
    {
        yCord = 1;
    }
    else
    {
        yCord = 8;
    }
    if (!smallCastling)
    {
        // check if the king and the rook is in the right place, and hasn't moved
        for (i = 1; i <= 5; i += 4)
        {
            if (isPieceInPositionNull(i, yCord))
            {
                return false;
            }
            else if (getPieceAt(i, yCord).hasMoved)
            {
                return false;
            }
        }
    }
    else
    {
        for (i = 5; i <= 8; i += 3)
        {
            if (isPieceInPositionNull(i, yCord))
            {
                return false;
            }
            else if (getPieceAt(i, yCord).hasMoved)
            {
                return false;
            }
        }
    }
    // check if there are no pieces between the king and rook
    if (smallCastling)
    {
        for (i = 6; i <= 7; i++)
        {
            if (!isPieceInPositionNull(i, yCord))
            {
                return false;
            }
        }
    }
    else
    {
        for (i = 2; i <= 4; i++)
        {
            if (!isPieceInPositionNull(i, yCord))
            {
                return false;
            }
        }
    }
    // check that no oponent piece is threatening any square in between
    Piece **pieces;
    if (playerColor == "white")
    {
        pieces = black;
    }
    else
    {
        pieces = white;
    }
    if (smallCastling)
    {
        for (i = 5; i <= 8; i++)
        {
            if (handleCastlingHelper(pieces, i, yCord) == false)
            {
                return false;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        for (i = 1; i <= 4; i++)
        {
            if (handleCastlingHelper(pieces, i, yCord) == false)
            {
                return false;
            }
            else
            {
                continue;
            }
        }
    }
    Piece &king = *board[yCord][5];
    if (smallCastling)
    {
        // move king
        king.hasMoved = true;
        king.movePiece(*this, 7, yCord);
        board[yCord][8]->hasMoved = true;
        board[yCord][8]->movePiece(*this, 6, yCord);
    }
    else
    {
        king.hasMoved = true;
        king.movePiece(*this, 3, yCord);
        board[yCord][1]->hasMoved = true;
        board[yCord][1]->movePiece(*this, 4, yCord);
    }
    return true;
}


/**
 * checking if the game has ended by checking if the current player's king has moves that won't put him
 * in chess.
 * @param playerColor current player color
 * @return T / F whether it was succesful or not
 */
bool Board::isEndOfGame(string playerColor)
{
    if (!isChessFor(playerColor))
    {
        return false;
    }
    int i;
    int ***possibleMoves;
    Piece *currentKing;
    Piece **pieces;
    if (playerColor == "white")
    {
        currentKing = whiteKing;
        pieces = black;
    }
    else
    {
        currentKing = blackKing;
        pieces = white;
    }
    possibleMoves = currentKing->getAllPossibleMoves();
    for (i = 0; i < 8; i++)
    {
        bool flag = false;
        // making sure we're inside the board
        if (possibleMoves[0][i][X] < 1 || possibleMoves[0][i][X] > 8 ||
            possibleMoves[0][i][Y] < 1 ||
            possibleMoves[0][i][Y] > 8)
        {
            continue;
        }
        // check if there is a legal move to those coordinates
        if (this->isPieceInPositionNull(possibleMoves[0][i][X], possibleMoves[0][i][Y]) ||
            (!this->isPieceInPositionNull(possibleMoves[0][i][X], possibleMoves[0][i][Y]) &&
            this->getPieceAt(possibleMoves[0][i][X], possibleMoves[0][i][Y]).getColor() !=
            playerColor))
        {
            isEndOfGameHelper(pieces, flag, possibleMoves, i);
        }
        if (flag)
        {
            return false;
        }
    }
    return true;
}

/**
 * helper for isEndOfGame (to avoid too complicated code)
 */
void Board::isEndOfGameHelper(Piece** pieces, bool &flag, int*** possibleMoves, int i)
{
    int j;
    for (j = 1; j < 17; j++)
    {
        if (pieces[j] != nullptr)
        {
            if (pieces[j]->stillInPlay)
            {
                if (pieces[j]->isValidMove(
                        *this, possibleMoves[0][i][X],
                        possibleMoves[0][i][Y]))
                {
                    flag = false;
                    break;
                }

                else if (possibleMoves[0][i][X] >= 1 && possibleMoves[0][i][X] <= 8 &&
                         possibleMoves[0][i][Y] >= 1 && possibleMoves[0][i][Y] <= 8)
                {
                    flag = true;
                    continue;
                }
            }
        }
    }
}

/**
 * prints the board
 */
void Board::printBoard()
{
    cout << "  ABCDEFGH  " << endl;
    cout << endl;
    for (int i = 8; i >= 1; i--)
    {
        cout << i << " ";
        for (int j = 1; j <= this->len_x; ++j)
        {
            if (this->board[i][j] == nullptr)
            {
                if ((j + i) % 2 == 0) // print white layer without piece
                {
                    cout << "\33[0;46m \33[0m";
                }
                else // print green layer without piece
                {
                    cout << "\33[0;42m \33[0m";
                }
            }

            else if ((j + i) % 2 == 0)
            {
                if (this->board[i][j]->getColor() == "black")//print black piece with white layer
                {
                    string Unicode = "\33[30;46m" + this->board[i][j]->getUniCode() + "\33[0m";
                    cout << Unicode;
                }
                else if (this->board[i][j]->getColor() == "white")//print white piece with white
                    // layer
                {
                    string Unicode = "\33[37;46m" + this->board[i][j]->getUniCode() + "\33[0m";
                    cout << Unicode;
                }
            }
            else
            {
                if (this->board[i][j]->getColor() == "black")//print black piece with green
                    // layer
                {
                    string Unicode = "\33[30;42m" + this->board[i][j]->getUniCode() + "\33[0m";
                    cout << Unicode;
                }
                else if (this->board[i][j]->getColor() == "white")//print white piece with green
                    // layer
                {
                    string Unicode = "\33[37;42m" + this->board[i][j]->getUniCode() + "\33[0m";
                    cout << Unicode;
                }
            }
        }
        cout << " " << i << endl;
    }
    cout << endl;
    cout << "  ABCDEFGH  " << endl << endl;
}

/**
* get board length
*/
int Board::getLength()
{
    return 8;
}

/**
* get board height
*/
int Board::getHeight()
{
    return 8;
}

/**
* destructor -> free all the pieces remained on board at the end of game
* */
Board::~Board()
{
    int i, j;
    for (i = 1; i <= 8; i++)
    {
        for (j = 1; j <= 8; j++)
        {
            delete board[i][j];
        }
    }
}
