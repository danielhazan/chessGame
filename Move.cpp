//
// Created by Shai on 13/01/2018.
//

#define X 0
#define Y 1

#include "Move.h"

/**
 * Move constructor, gets original and destination x and y coords and calculates from them the attributes
 * (number of moves, move type and direction)
 */
Move::Move(int fromX, int fromY, int toX, int toY)
{
    _fromX = fromX;
    _toX = toX;
    _fromY = fromY;
    _toY = toY;
    calculateMoveAttributes();
}

/**
 * calcualtes all the moves attributes (number of moves, move type and direction)
 */
void Move::calculateMoveAttributes()
{
    // check if it's straight
    if (_fromY == _toY)
    {
        _moveType = "straight";
        if (_toX - _fromX > 0)
        {
            _moveDirection = "right";
        }
        else
        {
            _moveDirection = "left";
        }
        _numberOfMoves = abs(_toX - _fromX);
    }
    else if (_fromX == _toX)
    {
        _moveType = "straight";
        _numberOfMoves = abs(_toY - _fromY);
        if (_toY - _fromY > 0)
        {
            _moveDirection = "up";
        }
        else
        {
            _moveDirection = "down";
        }
    }
        // check if diagonal
    else if (abs(_toX - _fromX) == abs(_toY - _fromY))
    {
        _moveType = "diagonal";
        _numberOfMoves = abs(_toX - _fromX);
        if (_toY - _fromY > 0 && _toX - _fromX > 0)
        {
            _moveDirection = "upRight";
        }
        else if (_toY - _fromY > 0 && _toX - _fromX < 0)
        {
            _moveDirection = "upLeft";
        }
        else if (_toY - _fromY < 0 && _toX - _fromX > 0)
        {
            _moveDirection = "downRight";
        }
        else if (_toY - _fromY < 0 && _toX - _fromX < 0)
        {
            _moveDirection = "downLeft";
        }
    }
        // check if knight move
    else if ((abs(_toX - _fromX) == 2 && abs(_toY - _fromY) == 1 ) || (abs(_toY - _fromY) == 2 &&
             abs(_toX - _fromX) == 1))
    {
        _moveType = "knightMove";
    }
    else
    {
        _moveType = "invalid";
    }
}

/**
 * returns move type
 */
std::string Move::getMoveType()
{
    return _moveType;
}

int Move::getNumberOfMoves()
{
    return _numberOfMoves;
}

/**
 * calculate all moves between this object's from coords and to coords
 */
void Move::getAllMovesInbetween()
{
    int i, counter;
    movesInBetween = new int *[_numberOfMoves];
    for (i = 0; i < _numberOfMoves; ++i)
    {
        movesInBetween[i] = new int[2];
    }
    if (_moveType == "straight")
    {
        counter = 0;
        if (_moveDirection == "right")
        {
            for (i = _fromX + 1; i <= _numberOfMoves + _fromX; i++)
            {
                movesInBetween[counter][X] = i;
                movesInBetween[counter][Y] = _fromY;
                counter++;
            }
        }
        else if (_moveDirection == "left")
        {
            for (i = _fromX - 1; i >= _fromX - _numberOfMoves; i--)
            {
                movesInBetween[counter][X] = i;
                movesInBetween[counter][Y] = _fromY;
                counter++;
            }
        }
        if (_moveDirection == "up")
        {
            for (i = _fromY + 1; i <= _numberOfMoves + _fromY; i++)
            {
                movesInBetween[counter][X] = _fromX;
                movesInBetween[counter][Y] = i;
                counter++;
            }
        }
        else if (_moveDirection == "down")
        {
            for (i = _fromY - 1; i >= _fromY - _numberOfMoves; i--)
            {
                movesInBetween[counter][X] = _fromX;
                movesInBetween[counter][Y] = i;
                counter++;
            }
        }
    }
    else if (_moveType == "diagonal")
    {
        counter = 0;
        for (i = 1; i <= _numberOfMoves; i++)
        {
            if (_moveDirection == "upRight")
            {
                movesInBetween[counter][X] = _fromX + i;
                movesInBetween[counter][Y] = _fromY + i;
            }
            else if (_moveDirection == "upLeft")
            {
                movesInBetween[counter][X] = _fromX - i;
                movesInBetween[counter][Y] = _fromY + i;
            }
            else if (_moveDirection == "downRight")
            {
                movesInBetween[counter][X] = _fromX + i;
                movesInBetween[counter][Y] = _fromY - i;
            }
            else if (_moveDirection == "downLeft")
            {
                movesInBetween[counter][X] = _fromX - i;
                movesInBetween[counter][Y] = _fromY - i;
            }
            counter++;
        }
    }
}

/**
 * gets the edge possible from moving in a given direction diagonally
 */
int *Move::getDiagonalCoords(int fromX, int fromY, bool up, bool right)
{
    int *coords = new int[2];
    int currentX = fromX, currentY = fromY;
    while (currentX >= 1 && currentX <= 8 && currentY >= 1 && currentY <= 8)
    {
        if (up)
        {
            currentY++;
        }
        else
        {
            currentY--;
        }
        if (right)
        {
            currentX++;
        }
        else
        {
            currentX--;
        }
    }
    if (right)
    {
        coords[0] = currentX - 1;
    }
    else
    {
        coords[0] = currentX + 1;
    }
    if (up)
    {
        coords[1] = currentY - 1;
    }
    else
    {
        coords[1] = currentY + 1;
    }
    return coords;
}

/**
 * gets an array of moves, from a given type and given coords.
 */
int ***Move::getAllPossibleMoves(std::string typeOfMove, int xCord, int yCord)
{
    int counter = 0, i, j;
    auto ***moves = new int **[8];
    for (i = 0; i < 8; i++)
    {
        moves[i] = new int *[8];
        for (j = 0; j < 8; j++)
        {
            moves[i][j] = new int[2];
            moves[i][j][X] = 9;
            moves[i][j][Y] = 9;
        }
    }
    Move *tempMove;
    // straight moves
    if ((typeOfMove == "straight") || (typeOfMove == "straightAndDiagonal"))
    {
        if (xCord != RIGHT_EDGE_X)
        {
            tempMove = new Move(xCord, yCord, RIGHT_EDGE_X, yCord);
            tempMove->getAllMovesInbetween();
            for (i = 0; i < tempMove->getNumberOfMoves(); i++)
            {
                moves[counter][i][X] = tempMove->movesInBetween[i][X];
                moves[counter][i][Y] = tempMove->movesInBetween[i][Y];
            }
            counter++;
        }
        if (xCord != LEFT_EDGE_X)
        {
            tempMove = new Move(xCord, yCord, LEFT_EDGE_X, yCord);
            tempMove->getAllMovesInbetween();
            for (i = 0; i < tempMove->getNumberOfMoves(); i++)
            {
                moves[counter][i][X] = tempMove->movesInBetween[i][X];
                moves[counter][i][Y] = tempMove->movesInBetween[i][Y];
            }
            counter++;
        }
        if (yCord != TOP_EDGE_Y)
        {
            tempMove = new Move(xCord, yCord, xCord, TOP_EDGE_Y);
            tempMove->getAllMovesInbetween();
            for (i = 0; i < tempMove->getNumberOfMoves(); i++)
            {
                moves[counter][i][X] = tempMove->movesInBetween[i][X];
                moves[counter][i][Y] = tempMove->movesInBetween[i][Y];
            }
            counter++;
        }
        if (yCord != LOW_EDGE_Y)
        {
            tempMove = new Move(xCord, yCord, xCord, LOW_EDGE_Y);
            tempMove->getAllMovesInbetween();
            for (i = 0; i < tempMove->getNumberOfMoves(); i++)
            {
                moves[counter][i][X] = tempMove->movesInBetween[i][X];
                moves[counter][i][Y] = tempMove->movesInBetween[i][Y];
            }
            counter++;
        }
    }
    // diagonal moves
    if ((typeOfMove == "diagonal") || (typeOfMove == "straightAndDiagonal"))
    {
        int *coords;
        bool checkUpRight = true, checkUpLeft = true, checkDownRight = true, checkDownLeft = true;
        if (xCord == RIGHT_EDGE_X)
        {
            checkUpRight = false;
            checkDownRight = false;
        }
        if (xCord == LEFT_EDGE_X)
        {
            checkUpLeft = false;
            checkDownLeft = false;
        }
        if (yCord == TOP_EDGE_Y)
        {
            checkUpRight = false;
            checkUpLeft = false;
        }
        if (yCord == LOW_EDGE_Y)
        {
            checkDownLeft = false;
            checkDownRight = false;
        }
        if (checkUpRight)
        {
            coords = getDiagonalCoords(xCord, yCord, true, true);
            tempMove = new Move(xCord, yCord, coords[X], coords[Y]);
            tempMove->getAllMovesInbetween();
            for (i = 0; i < tempMove->getNumberOfMoves(); i++)
            {
                moves[counter][i][X] = tempMove->movesInBetween[i][X];
                moves[counter][i][Y] = tempMove->movesInBetween[i][Y];
            }
            counter++;
        }
        if (checkUpLeft)
        {
            coords = getDiagonalCoords(xCord, yCord, true, false);
            tempMove = new Move(xCord, yCord, coords[X], coords[Y]);
            tempMove->getAllMovesInbetween();
            for (i = 0; i < tempMove->getNumberOfMoves(); i++)
            {
                moves[counter][i][X] = tempMove->movesInBetween[i][X];
                moves[counter][i][Y] = tempMove->movesInBetween[i][Y];
            }
            counter++;
        }
        if (checkDownRight)
        {
            coords = getDiagonalCoords(xCord, yCord, false, true);
            tempMove = new Move(xCord, yCord, coords[X], coords[Y]);
            tempMove->getAllMovesInbetween();
            for (i = 0; i < tempMove->getNumberOfMoves(); i++)
            {
                moves[counter][i][X] = tempMove->movesInBetween[i][X];
                moves[counter][i][Y] = tempMove->movesInBetween[i][Y];
            }
            counter++;
        }
        if (checkDownLeft)
        {
            coords = getDiagonalCoords(xCord, yCord, false, false);
            tempMove = new Move(xCord, yCord, coords[X], coords[Y]);
            tempMove->getAllMovesInbetween();
            for (i = 0; i < tempMove->getNumberOfMoves(); i++)
            {
                moves[counter][i][X] = tempMove->movesInBetween[i][X];
                moves[counter][i][Y] = tempMove->movesInBetween[i][Y];
            }
        }
    }
    if (typeOfMove == "knightMove")
    {
        counter = 0;
        std::cout << "knight moves: ";
        getKnightMove(xCord, yCord, 1, 2, moves[0][counter][X], moves[0][counter][Y], counter);
        std::cout << "; X: " << moves[0][counter][X] << "; Y: " << moves[0][counter][Y];
        getKnightMove(xCord, yCord, -1, 2, moves[0][counter][X], moves[0][counter][Y], counter);
        std::cout << "; X: " << moves[0][counter][X] << "; Y: " << moves[0][counter][Y];
        getKnightMove(xCord, yCord, 1, -2, moves[0][counter][X], moves[0][counter][Y], counter);
        std::cout << "; X: " << moves[0][counter][X] << "; Y: " << moves[0][counter][Y];
        getKnightMove(xCord, yCord, -1, -2, moves[0][counter][X], moves[0][counter][Y], counter);
        std::cout << "; X: " << moves[0][counter][X] << "; Y: " << moves[0][counter][Y];
        getKnightMove(xCord, yCord, 2, 1, moves[0][counter][X], moves[0][counter][Y], counter);
        std::cout << "; X: " << moves[0][counter][X] << "; Y: " << moves[0][counter][Y];
        getKnightMove(xCord, yCord, -2, 1, moves[0][counter][X], moves[0][counter][Y], counter);
        std::cout << "; X: " << moves[0][counter][X] << "; Y: " << moves[0][counter][Y];
        getKnightMove(xCord, yCord, 2, -1, moves[0][counter][X], moves[0][counter][Y], counter);
        std::cout << "; X: " << moves[0][counter][X] << "; Y: " << moves[0][counter][Y];
        getKnightMove(xCord, yCord, -2, -1, moves[0][counter][X], moves[0][counter][Y], counter);
        std::cout << "; X: " << moves[0][counter][X] << "; Y: " << moves[0][counter][Y];
    }
    return moves;
}


/**
 * gets a knight move from the given arguments
 */
void Move::getKnightMove(int fromX, int fromY, int upDown, int rightLeft, int &toX, int &toY, int &counter)
{
    int *coords = new int[2];
    coords[X] = fromX + rightLeft;
    coords[Y] = fromY + upDown;
    if (coords[X] < 1 || coords[X] > 8 || coords[Y] < 1 || coords[Y] > 8)
    {
        return;
    }
    toX = coords[X];
    std::cout << "BLAH:::" << toX;
    toY = coords[Y];
    counter++;
}
