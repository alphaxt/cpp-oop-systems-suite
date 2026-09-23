#pragma once
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>

class Board {
private:
    Piece* squares[8][8];

public:
    Board();
    ~Board();
    void printBoard();
    bool movePiece(int startX, int startY, int endX, int endY);
    Piece* getPiece(int x, int y) const {
        if (x < 0 || x >= 8 || y < 0 || y >= 8) return nullptr;
        return squares[y][x];
    }

    bool isPathClear(int startX, int startY, int endX, int endY) const;
    bool isSquareAttacked(int x, int y, bool byWhite) const;
    bool isCheck(bool whiteKing) const;
    bool isMoveSafe(int startX, int startY, int endX, int endY, bool isWhite);
};
