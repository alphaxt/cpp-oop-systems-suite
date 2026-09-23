#include "Board.h"
#include <cmath>
#include <cctype>

Board::Board() {
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            squares[y][x] = nullptr;

    // Pawns
    for (int x = 0; x < 8; x++) {
        squares[1][x] = new Pawn(true);
        squares[6][x] = new Pawn(false);
    }

    // Rooks
    squares[0][0] = new Rook(true);
    squares[0][7] = new Rook(true);
    squares[7][0] = new Rook(false);
    squares[7][7] = new Rook(false);

    // Knights
    squares[0][1] = new Knight(true);
    squares[0][6] = new Knight(true);
    squares[7][1] = new Knight(false);
    squares[7][6] = new Knight(false);

    // Bishops
    squares[0][2] = new Bishop(true);
    squares[0][5] = new Bishop(true);
    squares[7][2] = new Bishop(false);
    squares[7][5] = new Bishop(false);

    // Queens
    squares[0][3] = new Queen(true);
    squares[7][3] = new Queen(false);

    // Kings
    squares[0][4] = new King(true);
    squares[7][4] = new King(false);
}

Board::~Board() {
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 8; x++)
            delete squares[y][x];
}

void Board::printBoard() {
    for (int y = 7; y >= 0; y--) {
        std::cout << y + 1 << " ";
        for (int x = 0; x < 8; x++) {
            if (squares[y][x] == nullptr) std::cout << ". ";
            else {
                if (squares[y][x]->getColor()) // White
                    std::cout << squares[y][x]->getName();
                else
                    std::cout << (char)tolower(squares[y][x]->getName()[0]);
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}

bool Board::isPathClear(int startX, int startY, int endX, int endY) const {
    int dx = endX - startX;
    int dy = endY - startY;
    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    int currX = startX + stepX;
    int currY = startY + stepY;

    while (currX != endX || currY != endY) {
        if (squares[currY][currX] != nullptr) return false;
        currX += stepX;
        currY += stepY;
    }
    return true;
}

bool Board::isSquareAttacked(int targetX, int targetY, bool byWhite) const {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece* p = squares[y][x];
            if (!p || p->getColor() != byWhite) continue;

            std::string name = p->getName();
            int dx = targetX - x;
            int dy = targetY - y;
            int adx = std::abs(dx);
            int ady = std::abs(dy);

            if (name == "P") {
                int dir = byWhite ? 1 : -1;
                if (dy == dir && adx == 1) return true;
            } else if (name == "N") {
                if ((adx == 1 && ady == 2) || (adx == 2 && ady == 1)) return true;
            } else if (name == "B") {
                if (adx == ady && adx > 0 && isPathClear(x, y, targetX, targetY)) return true;
            } else if (name == "R") {
                if ((dx == 0 || dy == 0) && (dx != 0 || dy != 0) && isPathClear(x, y, targetX, targetY)) return true;
            } else if (name == "Q") {
                bool diag = (adx == ady && adx > 0);
                bool straight = ((dx == 0 || dy == 0) && (dx != 0 || dy != 0));
                if ((diag || straight) && isPathClear(x, y, targetX, targetY)) return true;
            } else if (name == "K") {
                if (adx <= 1 && ady <= 1 && (adx != 0 || ady != 0)) return true;
            }
        }
    }
    return false;
}

bool Board::isCheck(bool whiteKing) const {
    int kingX = -1, kingY = -1;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            Piece* p = squares[y][x];
            if (p && p->getName() == "K" && p->getColor() == whiteKing) {
                kingX = x;
                kingY = y;
                break;
            }
        }
        if (kingX != -1) break;
    }
    if (kingX == -1) return false;
    return isSquareAttacked(kingX, kingY, !whiteKing);
}

bool Board::isMoveSafe(int startX, int startY, int endX, int endY, bool isWhite) {
    Piece* moving = squares[startY][startX];
    Piece* target = squares[endY][endX];

    // Temporarily apply move
    squares[endY][endX] = moving;
    squares[startY][startX] = nullptr;

    bool check = isCheck(isWhite);

    // Revert move
    squares[startY][startX] = moving;
    squares[endY][endX] = target;

    return !check;
}

bool Board::movePiece(int startX, int startY, int endX, int endY) {
    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
        endX < 0 || endX >= 8 || endY < 0 || endY >= 8)
        return false;

    Piece* p = squares[startY][startX];
    if (p == nullptr) return false;

    Piece* target = squares[endY][endX];

    // Cannot capture own piece
    if (target != nullptr && target->getColor() == p->getColor())
        return false;

    // King can NEVER be captured in chess
    if (target != nullptr && target->getName() == "K")
        return false;

    // Movement validation
    std::string name = p->getName();
    int dx = endX - startX;
    int dy = endY - startY;
    int adx = std::abs(dx);
    int ady = std::abs(dy);

    if (name == "P") {
        int dir = p->getColor() ? 1 : -1;
        int startRank = p->getColor() ? 1 : 6;
        if (dx == 0) {
            // Forward 1
            if (dy == dir && target == nullptr) { /* valid */ }
            // Forward 2 from start
            else if (startY == startRank && dy == 2 * dir && target == nullptr && squares[startY + dir][startX] == nullptr) { /* valid */ }
            else return false;
        } else if (adx == 1 && dy == dir) {
            // Diagonal capture
            if (target == nullptr) return false;
        } else {
            return false;
        }
    } else if (name == "R") {
        if (!((dx == 0 || dy == 0) && (dx != 0 || dy != 0))) return false;
        if (!isPathClear(startX, startY, endX, endY)) return false;
    } else if (name == "B") {
        if (adx != ady || adx == 0) return false;
        if (!isPathClear(startX, startY, endX, endY)) return false;
    } else if (name == "Q") {
        bool diag = (adx == ady && adx > 0);
        bool straight = ((dx == 0 || dy == 0) && (dx != 0 || dy != 0));
        if (!diag && !straight) return false;
        if (!isPathClear(startX, startY, endX, endY)) return false;
    } else if (name == "N") {
        if (!((adx == 1 && ady == 2) || (adx == 2 && ady == 1))) return false;
    } else if (name == "K") {
        if (adx > 1 || ady > 1 || (adx == 0 && ady == 0)) return false;
    }

    // King safety check: Move cannot leave own King in Check
    if (!isMoveSafe(startX, startY, endX, endY, p->getColor()))
        return false;

    // Execute Move
    delete squares[endY][endX];
    squares[endY][endX] = p;
    squares[startY][startX] = nullptr;
    return true;
}
